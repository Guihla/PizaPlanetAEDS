#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buscar.h"
#include "interface.h"
#include "Btree.h"

Dados D;

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

void TelaNaoExiste(){
    TextColoreback(GREEN, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    GotoXY(51, 15); printf("ID nao encontrado!");
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
}


void TelaLeitura(){
    TextColoreback(GREEN, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    Borda(30, 2, 17, 2, 0,0);
    Borda(33, 5, 15, 2, 0,0);
    Borda(29, 8, 15, 2, 0,0);
    Borda(28, 11, 15, 2, 0,0);
    Borda(32, 14, 15, 2, 0,0);
    Borda(32, 17, 15, 2, 0,0);
    Borda(30, 20, 83, 2, 0,0);
    Borda(72, 2, 15, 2, 0,0);
    Borda(69, 5, 15, 2, 0,0);
    Borda(65, 8, 15, 2, 0,0);
    Borda(76, 11, 15, 2, 0,0);
    Borda(71, 14, 40, 2, 0,0);
    GotoXY(16, 3); printf("ID do Pedido: ");
    GotoXY(16, 6); printf("Ordem do Pedido: ");
    GotoXY(16, 9); printf("Id da Pizza: ");
    GotoXY(16, 12); printf("Quantidade: ");
    GotoXY(16, 15); printf("Data do Pedido: ");
    GotoXY(16, 18); printf("Hora do Pedido: ");
    GotoXY(16, 21); printf("Ingredientes: ");
    GotoXY(56, 3); printf("Preco Unitario: ");
    GotoXY(56, 6); printf("Preco Total: ");
    GotoXY(56, 9); printf("Tamanho: ");
    GotoXY(56, 12); printf("Categoria da Pizza: ");
    GotoXY(56, 15); printf("Nome da Pizza: ");

}

