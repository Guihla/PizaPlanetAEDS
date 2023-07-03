#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "arquivos.h"
#include "Btree.h"

Dados D;

int main(){
    Ler_Arquivo();
    char opcoes[][51] = {"Pesquisar",  "Indexar", "Comparar", "Sair"};
    int x[] = {20, 45, 68, 94};
    int y[] = {24, 24, 24, 24};
    BTree *raiz = NovaBTree(), *No;
    int id, buscado, buscab, cont, indexado = 0;
    int escolha = 0;
    do {
        TelaPrincipal();
        escolha = Menu(opcoes, x, y, escolha, 4);
        if(escolha == 0){ //BUSCAR
            TelaBuscar();
            TextColoreback(WHITE, BLACK);
            GotoXY(47, 14);scanf("%d", &id);
            buscado = BuscaindexnaBTree(No, id);
            if(buscado == -1){
                TelaNaoExiste();
            }else{
                FILE *fp = fopen("DadosPizzaria.txt","rb+");
                fseek(fp, buscado, SEEK_SET);
                fread(&D, sizeof(Dados), 1, fp);
                TelaLeitura();
                fclose(fp);
        }
        }
        if(escolha == 1){//INDEXAR
            if(indexado != 0){
                Tela_Indexar();
            }
            else{
                Tela_Indexar();
                No = IndexarBTree(raiz);
                indexado++;
            }
        }
        if(escolha == 2){//COMPARAR
            cont = 0;
            TelaBuscar();
            TextColoreback(WHITE, BLACK);
            GotoXY(47, 14);scanf("%d", &id);
            buscab = AcessoBinariaQuant(id);
            cont += BuscaBTreeCont(No, id);
            TelaComparacao(buscab, cont);
        }
        if(escolha == 3){//SAIR
            break;
        }
    }while(escolha != -1);
    GotoXY(0, 45);
    Imprime(No);
    return  0;
}
