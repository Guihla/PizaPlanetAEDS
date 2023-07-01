#include "interface.h"
#include "arquivos.h"

Dados D;

void GotoXY(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int GetTecla(){
    int ch;
    ch = getch();
    if(ch == 224){
        ch = getch() + 1000;
    }
    return ch;
}

void TextColoreback(int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             letras + (fundo << 4));
}

void Borda(int x, int y, int largura, int altura, int tipo, int sombra){
    char C[][6] = {"\xda\xbf\xc0\xd9\xc4\xb3" ,
                   "\xc9\xbb\xc8\xbc\xcd\xba"};
    int i, j;
    GotoXY(x, y); printf("%c", C[tipo][0]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][1]);
    for(j = 0; j < altura; j++){
        GotoXY(x, y+j+1); printf("%c", C[tipo][5]);

        for(i = 0; i < largura; i++) printf(" ");
        printf("%c", C[tipo][5]);
        if(sombra) printf("\xb2");
    }
    GotoXY(x, y+altura); printf("%c", C[tipo][2]);
    for(i = 0; i < largura; i++) printf("%c", C[tipo][4]);
    printf("%c", C[tipo][3]);
    if(sombra){
        GotoXY(x+1, y+altura+1);
        for(i = 0; i < largura+2; i++) printf("\xb2");
    }
}

int Menu(char opcoes[][51], int x[], int y[], int opcao, int n){
    int i; int tecla;
    TextColoreback(WHITE, BLACK);
    for(i = 0; i < n; i++) {
        GotoXY(x[i], y[i]); printf("%s", opcoes[i]);
    }
    do {
        TextColoreback(LIGHT_CYAN, BLACK);
        GotoXY(x[opcao], y[opcao]);
        printf("%s", opcoes[opcao]);
        tecla = GetTecla();
        TextColoreback(WHITE, BLACK);
        if(tecla == 13) return opcao;
        GotoXY(x[opcao], y[opcao]);
        printf("%s", opcoes[opcao]);
        if(tecla == TEC_BAIXO || tecla == TEC_DIR) opcao ++;
        if(tecla == TEC_CIMA || tecla == TEC_ESQ) opcao --;
        if(opcao < 0) opcao = n - 1;
        if(opcao >= n) opcao = 0;
    } while(tecla != 27);
    return -1;
}

void TelaBuscar(){
    TextColoreback(WHITE, BLACK);
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
    TextColoreback(WHITE, BLACK);
    Borda(3, 1, 111, 26, 1, 0);
    GotoXY(51, 15); printf("ID nao encontrado!");
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
    Borda(52, 23, 15, 2, 0,0);
    char Nao[][51] = {"Sair"};
    int Selecao = 0;
    int a[] = {58};
    int b[] = {24};
    Borda(52, 23, 15, 2, 0,0);
    Selecao = Menu(Nao, a, b, Selecao, 1);
}


void TelaLeitura(){
    TextColoreback(WHITE, BLACK);
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
    GotoXY(31, 3); printf("%d ", D.order_details_id);
    GotoXY(34, 6); printf("%d ", D.order_id);
    GotoXY(30, 9); printf("%s ", D.pizza_id);
    GotoXY(29, 12); printf(" %d ", D.quantity);
    GotoXY(33, 15); printf("%s ", D.order_date);
    GotoXY(33, 18); printf("%s ", D.order_time);
    GotoXY(31, 21); printf("%s ", D.pizza_ingredients);
    GotoXY(74, 3); printf("%.2f ", D.unit_price);
    GotoXY(70, 6); printf("%.2f ", D.total_price);
    GotoXY(66, 9); printf("%s ", D.pizza_size);
    GotoXY(77, 12); printf("%s ", D.pizza_category);
    GotoXY(72, 15); printf("%s ", D.pizza_name);
    char Ler[][51] = {"Sair"};
    int Selecionar = 0;
    int p[] = {58};
    int q[] = {24};
    Borda(52, 23, 15, 2, 0,0);
    Selecionar = Menu(Ler, p, q, Selecionar, 1);
}

void TelaPrincipal (){
    TextColoreback(WHITE, BLACK);
    Borda(0, 0, 118, 28, 1, 0);
    GotoXY(33, 2); printf("    ____  _                    ____  __                 __");
    GotoXY(33, 3); printf("   / __ \\(_)_______  ____ _   / __ \\/ /___ _____  ___  / /_");
    GotoXY(33, 4); printf("  / /_/ / /_  /_  / / __ `/  / /_/ / / __ `/ __ \\/ _ \\/ __/");
    GotoXY(33, 5); printf(" / ____/ / / /_/ /_/ /_/ /  / ____/ / /_/ / / / /  __/ /_ ");
    GotoXY(33, 6); printf("/_/   /_/ /___/___/\\__,_/  /_/   /_/\\__,_/_/ /_/\____/\\\__/");
    Borda(16, 23, 15, 2, 0,0);
    Borda(40, 23, 15, 2, 0,0);
    Borda(64, 23, 15, 2, 0,0);
    Borda(88, 23, 15, 2, 0,0);
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
