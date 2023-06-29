#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "arquivos.h"
#include "Btree.h"



char opcoes[][51] = {"Pesquisar",  "Indexar", "Sair"};
int x[] = {30, 55, 81};
int y[] = {24, 24, 24};

void TelaPrincipal () {
    TextColoreback(GREEN, BLACK);
    Borda(0, 0, 118, 28, 1, 0);
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
    Borda(27, 23, 15, 2, 0,0);
    Borda(52, 23, 15, 2, 0,0);
    Borda(77, 23, 15, 2, 0,0);
    GotoXY(46, 9); printf("       _....._");
    GotoXY(46, 10); printf("   _.:`.--|--.`:._");
    GotoXY(46, 11); printf("  .: .'\o  | o /'. '.");
    GotoXY(46, 12); printf(" // '.  \ o|  /  o '.\"");
    GotoXY(46, 13); printf("//'._o'. \ |o/ o_.-'o\\");
    GotoXY(46, 14); printf("|| o '-.'.\|/.-' o   ||");
    GotoXY(46, 15); printf("||--o--o-->|");
    GotoXY(46, 16); printf("              // ""--.._");
    GotoXY(46, 17); printf("             ||  (_)  _  -.");
    GotoXY(46, 18); printf("             ||    _ (_)    '-.");
    GotoXY(46, 19); printf("             ||   (_)   __..-'");
    GotoXY(46, 20); printf("              \\__..--""");
}


int main(){

    Ler_Arquivo();
    int escolha = 0;
    do {
        TelaPrincipal();
        escolha = Menu(opcoes, x, y, escolha, 3);
        if(escolha == 0)
            Executar_Btree();
        if(escolha == 1)
           TelaIndexar();
        if(escolha == 2)
            break;
    } while(escolha != -1);
    GotoXY(0, 45);
    return  0;
}
