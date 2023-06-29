#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXITENS 20
#include "BTree.h"
#include "buscar.h"

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
    for(i = mediana+1, j = 0; i < No->TotalChaves; i++, j++)
    {
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
    int Tot = No->TotalChaves;
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


void Imprimir_Dados(){
    GotoXY(31, 3); printf("%d", D.order_details_id);
    GotoXY(34, 6); printf("%d", D.order_id);
    GotoXY(30, 9); printf("%s", D.pizza_id);
    GotoXY(29, 12); printf(" %d", D.quantity);
    GotoXY(33, 15); printf("%s", D.order_date);
    GotoXY(33, 18); printf("%s", D.order_time);
    GotoXY(31, 21); printf("%s", D.pizza_ingredients);
    GotoXY(74, 3); printf("%.2f", D.unit_price);
    GotoXY(70, 6); printf("%.2f", D.total_price);
    GotoXY(66, 9); printf("%s", D.pizza_size);
    GotoXY(77, 12); printf("%s", D.pizza_category);
    GotoXY(72, 15); printf("%s", D.pizza_name);
}

void Executar_Btree(){
    FILE *fp = fopen("DadosPizzaria.txt","rb");
    int i, Chave;
    BTree* raiz, *Buscado;
    raiz = Executar_Indexar();
    int id;
    char Opcoes[][51] = {"","Sair"};
    char Selecao[][51] = {"Nova pesquisa", "Sair"};
    char NaoExiste[][51] = {"Nova Pesquisa", "Sair"};
    int Escolha = 0, Selecionar = 0, Nao = 0;
    int x[] = {47, 55};
    int y[] = {14, 24};
    int a[] = {44, 67};
    int b[] = {25, 25};
    int e[] = {44, 67};
    int f[] = {25, 25};
    do{
        TelaBuscar();
        Borda(52, 23, 15, 2, 0,0);
        Escolha = Menu(Opcoes, x, y, Escolha, 2);
        if(Escolha == 0){
            scanf("%d", &id);
            Buscado = BuscaBTree(raiz, id);
            if(Buscado == NULL){
                TelaNaoExiste();
                Borda(42, 24, 15, 2, 0,0);
                Borda(65, 24, 15, 2, 0,0);
                Nao = Menu(NaoExiste, e, f, Nao, 2);
                if(Nao == 0)
                if(Nao == 1)break;
            }
            else{
                TelaLeitura();
                fseek(fp, Buscado -> index, SEEK_SET);
                fread(&D, sizeof(Dados), 0, fp);
                Imprimir_Dados();
                Borda(42, 24, 15, 2, 0,0);
                Borda(65, 24, 15, 2, 0,0);
                Selecionar = Menu(Selecao, a, b, Selecionar, 2);
                if(Selecionar == 0)
                if(Selecionar == 1)break;
            }
    }
    }while(Escolha != 1);
    fclose(fp);
}



    /*
    Buscado = BuscaBTree(raiz, Chave);
    printf("\n");

    if(Buscado == NULL)
    {
        printf("Chave nao encontrada!!\n");
    }
    else
    {
        printf("Chave Encontrada!!\n");
        printf("Em %d\n", Buscado->Chaves[0]);
    }*/

