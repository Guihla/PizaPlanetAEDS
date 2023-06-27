#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buscar.h"
#include "interface.h"

Dados D[10000];

void TelaBuscar(){
    TextColoreback(GREEN, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    GotoXY(17, 14); printf("             ID do pedido: ");
    Borda(46, 13, 30, 2, 0, 0);
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
}


void Buscar_Pizza(){
    int id;
    char Opcoes[][51] = {"","Sair"};
    int Escolha = 0;
    int x[] = {47, 55};
    int y[] = {14, 24};
    do{
        TelaBuscar();
        Borda(52, 23, 15, 2, 0,0);
        Escolha = Menu(Opcoes, x, y, Escolha, 2);
        if(Escolha == 0){

        }
    }while(Escolha != 1);
}
