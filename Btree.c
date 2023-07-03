#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BTree.h"
#include "interface.h"
#include "arquivos.h"


Dados D;

BTree* NovoNo(BTree* Pai){
    BTree *Novo = (BTree*) malloc(sizeof(BTree));
    Novo -> Pai = Pai;
    Novo -> EhFolha = 1;
    Novo -> TotalChaves = 0;
    return Novo;
}

BTree* NovaBTree(){
    return NovoNo(NULL);
}

void InserenoNo(BTree* No, int Chave, int index, BTree* NoFilho){
    int i;
    for(i = No-> TotalChaves; i > 0; i--){
        if(No->Chaves[i-1] > Chave) {
            No -> Chaves[i] = No -> Chaves[i-1];
            if(!No->EhFolha) No->Filhos[i+1] = No->Filhos[i];
        }
        else break;
    }
    No -> Chaves[i] = Chave;
    No -> index[i] = index;
    if(!No->EhFolha) No->Filhos[i+1] = NoFilho;
    No -> TotalChaves++;
}

BTree* DivideNo(BTree* No){
    int i, j, mediana = (No->TotalChaves) / 2;
    BTree* Novo = NovoNo(No->Pai);
    Novo -> TotalChaves = mediana;
    Novo -> EhFolha = No -> EhFolha;
    // transfere metade para novo no
    for(i = mediana+1, j = 0; i < No->TotalChaves; i++, j++){
        Novo -> index[j] = No -> index[i];
        Novo -> Chaves[j] = No -> Chaves[i];
        Novo -> Filhos[j] = No -> Filhos[i];
        if(!Novo->EhFolha) Novo -> Filhos[j]->Pai = Novo;
    }
    Novo->Filhos[j] = No->Filhos[i];
    if(!Novo->EhFolha) Novo->Filhos[j]->Pai = Novo;
    No->TotalChaves = mediana;

    if (No->Pai == NULL)
    {
        No->Pai = NovoNo(NULL);
        No->Pai->EhFolha = 0;
        No->Pai->Chaves[0] = No -> Chaves[mediana];
        No->Pai->index[0] = No -> index[mediana];
        No->Pai->Filhos[0] = No;
        No->Pai->Filhos[1] = Novo;
        No->Pai->TotalChaves++;
    }
    else
    {
        /*for(i = No->Pai->TotalChaves; i > 0; i--)
        {
            if(No->Pai->Chaves[i-1] > No->Chaves[mediana])
            {
                No->Pai->Chaves[i] = No->Pai->Chaves[i-1];
                No->Pai->Filhos[i+1] = No->Pai->Filhos[i];
            }
            else break;
        }
        No->Pai->Chaves[i] = No->Chaves[mediana];
        No ->Pai->index[i] = No -> index[mediana];
        No->Pai->Filhos[i+1] = Novo;
        No->Pai->TotalChaves++;*/
        InserenoNo(No -> Pai, No->Chaves[mediana], No->index[mediana], Novo);
    }

    //No->Pai = No->Pai;
    Novo->Pai = No->Pai;

    if (No->Pai->TotalChaves >= ORDEM)
    {
        return DivideNo(No->Pai);
    }
    return No->Pai;
}

BTree* InsereBTree(BTree* No, int index, int Chave){
    int i;
    if(No->EhFolha){
        //if(No->TotalChaves < ORDEM)
        //{
            InserenoNo(No, Chave, index, NULL);
        //}
        if(No->TotalChaves >= ORDEM)
        {
            return DivideNo(No);
        }
    }else{
        //Escolhe Filho e Chama Recursivo
        int Tot = No->TotalChaves;
        for(i = 0; i < Tot; i++)
        {
            if(No -> Chaves[i] > Chave)
            {
                InsereBTree(No->Filhos[i], index, Chave);
                break;
            }
        }
        if(i >= Tot)
        {
            InsereBTree(No->Filhos[i], index, Chave);
        }
    }
    if(No->Pai != NULL) return No->Pai;
    return No;
}

void Imprime(BTree *raiz){
    int i;
    static int nivel = 0, contpag = 0;
    if(raiz->Pai == NULL){
        nivel = 0; contpag =0;
    }
    else nivel++;
    //printf("\nraiz->TotalChaves = %d\n", raiz->TotalChaves);
    for(i = 0; i < nivel; i++) printf("\t");
    for(i = 0; i < raiz->TotalChaves; i++){
        printf("%d ", raiz->Chaves[i]);
    }
    printf("\n");
    contpag++;
    if(contpag > 23){
        system("pause"); contpag = 0;
    }
    if(!raiz->EhFolha)
        for(i = 0; i <= raiz->TotalChaves; i++){
            if(raiz->Filhos[i] != NULL) Imprime(raiz->Filhos[i]);
        }
    nivel--;
}

int BuscaindexnaBTree(BTree* No, int Chave){
    int i;
    int Tot = No -> TotalChaves;
    for(i = 0; i < Tot; i++){
        if(No -> Chaves[i] == Chave) return No -> index[i]; //retorna o índice
        if(No -> Chaves[i] > Chave){
            if(!No -> EhFolha)
                return BuscaindexnaBTree(No -> Filhos[i], Chave);
            break;
        }
    }
    //if(i >= Tot){
        if(!No->EhFolha)
            return BuscaindexnaBTree(No->Filhos[i], Chave);
    //}
    return -1; // Se não encontrar retorna -1
}

int BuscaBTreeCont(BTree* No, int Chave){
    int i;
    int Tot = No-> TotalChaves;
    for(i = 0; i < Tot; i++){
        if(No->Chaves[i] == Chave)
            return 1;
        if(No->Chaves[i] > Chave){
            if(!No->EhFolha)
                return BuscaBTreeCont(No->Filhos[i], Chave) + 1;
            break;
        }
    }
    if(!No->EhFolha)
        return BuscaBTreeCont(No->Filhos[i], Chave) + 1;
    return NULL;
}

BTree* IndexarBTree(BTree* No){
    int posicao;
    FILE *fp = fopen("DadosPizzaria.txt","rb");
    fseek(fp, 0, SEEK_SET);
    while(fread(&D, sizeof(Dados), 1, fp)){
        posicao = ftell(fp) - sizeof(Dados);
        No = InsereBTree(No, posicao, D.order_details_id);
    }
    fclose(fp);
    return No;
}

int AcessoBinaria(int v[], int n, int x){
  int ini = 0, fim = n-1;
    int cont = 1;
    while(ini <= fim){
        int meio = (ini + fim)/2;
        if(x < v[meio]){
            fim = meio-1;
            cont++;
        }
        else if(x > v[meio]){
            ini = meio+1;
            cont++;
    }
    else return cont;
  }
}

int AcessoBinariaQuant(int id){
    int v[48620], i = 0, cont = 0;
    FILE *fp = fopen("DadosPizzaria.txt","rb");
    fseek(fp, 0, SEEK_SET);
    while(fread(&D, sizeof(Dados), 1, fp)){
        v[i] = D.order_details_id;
        i++;
    }
    cont = AcessoBinaria(v, 48620, id);
    fclose(fp);
    return cont;
}
