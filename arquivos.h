#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

struct dados
{
    int order_details_id;
    int order_id;
    char pizza_id[100];
    int quantity;
    char order_date[11];
    char order_time[9];
    float unit_price;
    float total_price;
    char pizza_size[2];
    char pizza_category[31];
    char pizza_ingredients[101];
    char pizza_name[61];
};
typedef struct dados Dados;

void Ler_Arquivo();
void Telaarquivo();

#endif // ARQUIVO_H_INCLUDED
