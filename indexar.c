#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexar.h"
#include "interface.h"
#include "arquivos.h"
#include "Btree.h"

Dados D;

void TelaIndexar(){
    Executar_Indexar();
    TextColoreback(GREEN, BLACK);
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
    do{
        Selecione = Menu(Indexando, c, d, Selecione, 1);
        if(Selecione == 0)break;
    }while(Selecione != 1);
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


BTree* Indexar(){
    BTree* raiz;
    BTree* indexado;
    raiz = NovaBTree();
    indexado = IndexarBTree(raiz);
    return indexado;
}

BTree* Executar_Indexar(){
    BTree* aux;
    aux = Indexar();
    return aux;
}


