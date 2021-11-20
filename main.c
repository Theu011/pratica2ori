#include <stdio.h>
#include <stdlib.h>

#define MAX 4
#define MIN 2

typedef struct btreeNo{
    int val[MAX + 1], contador;
    struct btreeNo* link[MAX + 1];
} btreeNo;

btreeNo *root;

void insere(int val);
void procura(int val, int *pos, btreeNo *meuNo);
int setValorNo(int val, int *pval, btreeNo *node, btreeNo **child);
void addValorNo(int val, int pos, btreeNo *node, btreeNo *child);
void separaNo(int val, int *pval, int pos, btreeNo *node, btreeNo *child, btreeNo **novoNo);

/* creating new node */
btreeNo * criaNo(int val, btreeNo *child){
    btreeNo *novoNo = (btreeNo *) malloc(sizeof(btreeNo));
    novoNo->val[1] = val;
    novoNo->contador = 1;
    novoNo->link[0] = root;
    novoNo->link[1] = child;

    return novoNo;
}

/*insert val in b-tree */
void insere(int val){
    int flag, i;
    btreeNo *child;
    flag = setValorNo(val, &i, root, &child);
    if(flag)
        root = criaNo(i, child);
}

/* search val in b-tree */
void procura(int val, int *pos, btreeNo *meuNo){
    if(!meuNo)
        return;
    if(val < meuNo->val[1])
        *pos = 0;
    else{
        for(*pos = meuNo->contador; (val < meuNo->val[*pos] && *pos > 1); (*pos)--);
        if(val == meuNo->val[*pos]){
            printf("%d\n", *pos);
            printf("CHAVE ENCONTRADA!\n");
            return;
        }
        else
            printf("CHAVE NÃO ENCONTRADA!");
    }
    procura(val, pos, meuNo->link[*pos]);
    return;
}

int setValorNo(int val, int *pval, btreeNo *node, btreeNo **child){
    int pos;
    if(!node){
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1]){
        pos = 0;
    }
    else{
        for(pos = node->contador; (val < node->val[pos] && pos > 1); pos--);
        if(val == node->val[pos]){
            printf("Duplicates not allowed\n");
            return 0;
        }
    }
    if(setValorNo(val, pval, node->link[pos], child)){
        if(node->contador < MAX){
            addValorNo(*pval, pos, node, *child);
        }
        else{
            separaNo(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

/* places the value in appropriate position */
void addValorNo(int val, int pos, btreeNo *node, btreeNo *child){
    int j = node->contador;
    while(j > pos){
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->contador++;
}

/* split the node */
void separaNo(int val, int *pval, int pos, btreeNo *node, btreeNo *child, btreeNo **novoNo){
    int media, j;
    if(pos > MIN)
        media = MIN + 1;
    else
        media = MIN;
    
    *novoNo = (btreeNo *) malloc(sizeof(btreeNo));
    j = media + 1;
    while(j <= MAX){
        (*novoNo)->val[j - media] = node->val[j];
        (*novoNo)->link[j - media] = node->link[j];
        j++;
    }
    node->contador = media;
    (*novoNo)->contador = MAX - media;
    if(pos <= MIN)
        addValorNo(val, pos, node, child);
    else
        addValorNo(val, pos-media, *novoNo, child);
    *pval = node->val[node->contador];
    (*novoNo)->link[0] = node->link[node->contador];
    node->contador--;
}

int main(){
    int val, opt;
    while(1){
        printf("1. Insere\t 2. Procurar\t 3. Sair\n");
        scanf("%d", &opt);
        switch(opt){
            case 1: 
                printf("Insira o valor:\n");
                scanf("%d", &val);
                insere(val);
                break;
            case 2:
                printf("Entre o elemento para procurar:\n");
                scanf("%d", &val);
                procura(val, &opt, root);
                break;
            case 3:
                exit(0);
        }
    }
    return 0;
}