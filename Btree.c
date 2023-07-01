#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


BTree* BuscaBTree(BTree* No, int Chave){
    int i;
    int Tot = No -> TotalChaves;
    //printf("*");
    for(i = 0; i < Tot; i++){
        if(No -> Chaves[i] == Chave)return No;
        if(No -> Chaves[i] > Chave){
            if(!No -> EhFolha)
                return BuscaBTree(No -> Filhos[i], Chave);
            break;
        }
    }
    //if(i >= Tot){
        if(!No->EhFolha)
            return BuscaBTree(No->Filhos[i], Chave);
    //}
    return NULL;
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


BTree *BuscarID(BTree *No){
    int Escolha = 0, id;
    BTree * Buscado;
    int x[] = {47, 55};
    int y[] = {14, 24};
    TextColoreback(GREEN, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    GotoXY(17, 14); printf("             ID do pedido: ");
    Borda(46, 13, 30, 2, 0, 0);
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
    char Opcoes[][51] = {"","Sair"};
    Borda(52, 23, 15, 2, 0,0);
    Escolha = Menu(Opcoes, x, y, Escolha, 2);
    if(Escolha == 0){
        scanf("%d", &id);
        Buscado = BuscaBTree(No, id);
    }
    if(Escolha == 1)
    return Buscado;
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
    TextColoreback(WHITE, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    GotoXY(49, 15); printf("Indexado com Sucesso!");
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
    Borda(52, 23, 15, 2, 0,0);
    char Indexando[][51] = {"Sair"};
    int Selecione = 0;
    int c[] = {58};
    int d[] = {24};
    Selecione = Menu(Indexando, c, d, Selecione, 1);
    //GotoXY(0,60);Imprime(No);
    return No;
}


int BuscaBinaria(int v[], int n, int x){
  int ini = 0, fim = n-1;
  while(ini <= fim){
    int meio = (ini + fim)/2;
    if(x < v[meio])fim = meio-1;
    else if(x > v[meio])ini = meio+1;
    else return meio;
  }
  return -1;
}

int Encontrar_Binaria(int id){
    int v[48620], i = 1, res;
    FILE *fp = fopen("DadosPizzaria.txt","rb");
    fseek(fp, 0, SEEK_SET);
    while(fread(&D, sizeof(Dados), 1, fp)){
        v[i] = D.order_details_id;
        i++;
    }
    /*for(int j = 0; j < 48621; j++){
        printf("%d\n", v[j]);
    }*/
    res = BuscaBinaria(v, 48620, id);
    return res;
}

