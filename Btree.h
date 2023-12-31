#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define ORDEM 7

struct btree{
    int TotalChaves;
    int EhFolha;
    int index[ORDEM];
    int Chaves[ORDEM];
    struct btree* Filhos[ORDEM+1];
    struct btree* Pai;
};
typedef struct btree BTree;

BTree* NovaBTree();
BTree* InsereBTree(BTree* No, int index,int Chave);
BTree* BuscaBTree(BTree* No, int Chave);
void Imprime(BTree *raiz);
int Altura(BTree *raiz);
int MenorChave(BTree *raiz);
void Executar_Btree();
BTree* IndexarBTree(BTree* No);
BTree *BuscarID(BTree *No);
int AcessoBinaria(int v[], int n, int x);
int AcessoBinariaQuant(int id);

#endif // BTREE_H_INCLUDED
