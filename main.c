#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "arquivos.h"
#include "Btree.h"

Dados D;

char opcoes[][51] = {"Pesquisar",  "Indexar", "Comparar", "Sair"};
char NaoExiste[][51] = {"Sair"};
int x[] = {20, 45, 68, 94};
int y[] = {24, 24, 24, 24};

int main(){

    BTree *raiz = NovaBTree(), *No, *Buscado;
    int id, cont=0, Nao = 0, res;
    int escolha = 0;
    do {
        TelaPrincipal();
        escolha = Menu(opcoes, x, y, escolha, 4);
        if(escolha == 0){//BUSCAR
            TelaBuscar();
            GotoXY(47, 14);scanf("%d", &id);
            Buscado = BuscaBTree(No, id);
            if(Buscado == NULL){
                TelaNaoExiste();
            }else{
                FILE *fp = fopen("DadosPizzaria.txt","rb+");
                fseek(fp, Buscado -> index, SEEK_SET);
                fread(&D, sizeof(Dados), 1, fp);
                TelaLeitura();
                fclose(fp);
        }
        }
        if(escolha == 1){//INDEXAR
            No = IndexarBTree(raiz);

        }
        if(escolha == 2){
            TelaBuscar();
            GotoXY(47, 14);scanf("%d", &id);
            res = Encontrar_Binaria(id);
            if(res == -1){
                TelaNaoExiste();
            }//ELSE IMPRIMIR TEMPO E CONTAGEM DE ACESSO
        }
        if(escolha == 3){
            break;
        }
            //break;}//SAIR MENU
    }while(escolha != -1);
    GotoXY(0, 45);
    return  0;
}

