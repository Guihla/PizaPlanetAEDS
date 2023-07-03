#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BTree.h"
#include "interface.h"
#include "arquivos.h"
int cont;

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
    //printf("*");
    for(i = 0; i < Tot; i++){
        if(No -> Chaves[i] == Chave) return No ->index[i]; // retorna o índice e não o ponteiro
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
    return 0;
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
    TextColoreback(LIGHT_RED, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    TextColoreback(WHITE, BLACK);
    GotoXY(49, 15); printf("Indexado com Sucesso!");
    TextColoreback(LIGHT_RED, BLACK);
    GotoXY(16, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(16, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(16, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(16, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(16, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
    GotoXY(82, 2); printf("          ,MMM8&&&.");
    GotoXY(82, 3); printf("     _...MMMMM88&&&&..._");
    GotoXY(82, 4); printf("  .::'''MMMMM88&&&&&&'''::.");
    GotoXY(82, 5); printf(" ::     MMMMM88&&&&&&     ::");
    GotoXY(82, 6); printf(" '::....MMMMM88&&&&&&....::'");
    GotoXY(82, 7); printf("    `''''MMMMM88&&&&''''`");
    GotoXY(82, 8); printf("          'MMM8&&&'");
    Borda(52, 23, 15, 2, 0,0);
    char Indexando[][51] = {"Sair"};
    int Selecione = 0;
    int c[] = {58};
    int d[] = {24};
    Selecione = Menu(Indexando, c, d, Selecione, 1);
    return No;
}

int AcessoBinaria(int v[], int n, int x){
  int ini = 0, fim = n-1, cont = 1;
  while(ini <= fim){
    int meio = (ini + fim)/2;
    if(x < v[meio]){
        fim = meio-1;
    }
    else if(x > v[meio]){
        ini = meio+1;
    }
    else return meio;
    cont++;
  }
  return cont;
}

int AcessoBinariaQuant(int id){
    int v[48620], i = 0, cont;
    FILE *fp = fopen("DadosPizzaria.txt","rb");
    fseek(fp, 0, SEEK_SET);
    while(fread(&D, sizeof(Dados), 1, fp)){
        v[i] = D.order_details_id;
        i++;
    }
    cont = AcessoBinaria(v, 48620, id);
    return cont;
}
