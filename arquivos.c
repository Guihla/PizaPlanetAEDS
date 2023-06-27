#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"

Dados D[10000];

void Ler_Arquivo(){
    char linha[100000], texto[100000];
    char *sub, *sub2;
    int campo = 0, i = 0, j, tam, t, a, aspas;

    FILE *fp = fopen("Banco de Dados.csv", "r");
    if(fp == NULL){
        printf("Nao abriu Banco de Dados.csv\n");
        exit(1);
    }
    fscanf(fp, " %[^\n]", linha); // Linha dos nomes das colunas
    //printf("%s\n", linha); // Mostra a linha
    while (fscanf (fp, " %[^\n]", linha)!=EOF){
        //printf("%s\n", linha); // Mostra a linha
        if(i > 10) break; // testa com os primeiros 20
        campo = 0;
        texto[0] = 0;
        tam = strlen(linha);
        memset(&D[i], 0, sizeof(Dados));
        for(t = 0; t < tam; t++){
            a = 0;
            aspas = 0;
            while(linha[t] != ';' && t < tam){
                texto[a++] = linha[t++];
                if(t > 0 && linha[t-1] == '\"'){
                    //printf("\n\naspas\n\n");
                    //t++;
                    a--;
                    while(linha[t] != '\"' && t < tam){
                        texto[a++] = linha[t++];
                    }
                    t++;
                }
            }
            texto[a++] = 0;
            switch (campo){
            case 0:
                D[i].order_details_id = atoi(texto);
                break;
            case 1:
                D[i].order_id = atoi(texto);
                break;
            case 2:
                strncpy(D[i].pizza_id, texto, 99); //99 pq é o tamanho da string menos 1
                break;
            case 3:
                D[i].quantity = atoi(texto);
                break;
            case 4:
                strncpy (D[i].order_date, texto, 10); //atoi transforma string em inteiro
                break;
            case 5:
                strncpy (D[i].order_time, texto, 8);
                break;
            case 6:
                D[i].unit_price = atof(texto);
                break;
            case 7:
                D[i].total_price = atof(texto);
                break;
            case 8:
                strncpy (D[i].pizza_size, texto, 1);
                break;
            case 9:
                strncpy (D[i].pizza_category, texto, 30);
                break;
            case 10:
                strncpy (D[i].pizza_ingredients, texto, 100);
                break;
            case 11:
                strncpy (D[i].pizza_name, texto, 60);
                break;
            }
            campo++;
        }
        i++;
    }
    for(j = 0; j < 11; j++){
        printf(" %d\n %d\n %s\n %d\n %s\n %s\n %.2f\n %.2f\n %s\n %s\n %s\n %s\n\n",
               D[j].order_details_id, D[j].order_id, D[j].pizza_id, D[j].quantity, D[j].order_date,
               D[j].order_time, D[j].unit_price, D[j].total_price,
               D[j].pizza_size, D[j].pizza_category, D[j].pizza_ingredients,  D[j].pizza_name);
    }
    fclose (fp);
}
