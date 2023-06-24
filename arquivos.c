#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

struct dados{
    int order_details_id;
    int order_id;
    char pizza_id[31];
    int quantity;
    int order_date; //como inserir data;
    int order_time; //como inserir hora
    float unit_price;
    float total_price;
    char pizza_size;
    char pizza_category[31];
    char pizza_ingredients[101];
    char pizza_name[61];
};
typedef struct dados Dados;

Dados D[1000];

void LerArquivo(){
    char linha [1001];
    char *sub;
    int campo = 0, i = 0, j;

    FILE *fp = fopen("Users/PC/Desktop/Trabalho AEDS/Data Model - Pizza Sales.csv", "r");

    if(fp == NULL){
        printf("Nao abriu Data Model - Pizza Sales.csv\n");
        exit(1);
    }

    fscanf (fp, " %[^\n]", linha); // Linha dos nomes das colunas
    //printf("%s\n", linha); // Mostra a linha
    while (fscanf (fp, " %[^\n]", linha)!=EOF){
        //printf("%s\n", linha); // Mostra a linha
        //if(i > 20) break; // testa com os primeiros 20
        campo = 0;
        sub = strtok (linha, ","); // 1a. substring antes da ,
        while (sub!= NULL){
            switch (campo){
            case 0:
                D[i].order_details_id = atoi(sub);
                campo++;
                break;
            case 1:
                D[i].order_id = atof (sub);
                campo++;
                break;
            case 2:
                strcpy (D[i].pizza_id, sub);
                campo++;
                break;
            case 3:
                D[i].quantity = atof (sub);
                campo++;
                break;
            case 4:
                D[i].order_date = atof (sub);
                campo++;
                break;
            case 5:
                D[i].order_time = atof (sub);
                campo++;
                break;
            case 6:
                D[i].unit_price = atof (sub);
                campo++;
                break;
            case 7:
                D[i].total_price = atof (sub);
                campo++;
                break;
            case 8:
                strcpy (D[i].pizza_size, sub);
                campo++;
                break;
            case 9:
                strcpy (D[i].pizza_category, sub);
                campo++;
                break;
            case 10:
                strcpy (D[i].pizza_ingredients, sub);
                campo++;
                break;
            case 11:
                strcpy(D[i].pizza_name, sub);
                campo++;
                break;
            }
            sub = strtok (NULL, ","); //próxima substring separada por
        }
        i++;
        for(j = 0; j < 12; j++){
    printf("%d %d %s %d %d %d %.2f %.2f %c %s %s %s", D[j].order_details_id, D[j].order_id, D[j].pizza_id, D[j].quantity, D[j].order_date, D[j].order_time, D[j].unit_price, D[j].total_price, D[j].pizza_size, D[j].pizza_category, D[j].pizza_ingredients, D[j].pizza_name);
        }
        fclose(fp);
}
}
