#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float gera_erro(float max)
{
    int decimais = 0;
    int verifica = max;
    int soma=0;
    if(verifica!=0)
    {
        soma += rand() % (verifica);
    }
    while(verifica - max != 0)
    {
        decimais++;
        max*=10;
        verifica = max;
    }
    decimais = pow(10,decimais);
    soma*= decimais;
    soma += rand()%decimais;
    max = soma;
    max /= decimais;
    if(rand()%2 == 0)
        return max;
    else
        return -max;

}

float linear(float x, float a, float b)
{
    return x*a + b;
}

float quadrada(float x, float a, float b, float c)
{
    return a*x*x + b*x + c;
}

float cubica(float x, float a, float b, float c, float d)
{
    return a*x*x*x + b*x*x + c*x + d;
}

float racional(float x, float a, float b)
{
    return a/(x+b);
}

int main()
{
    
    int qtd,passo,incerteza,escolha;
    float range_erro,soma;
    float *vetor_x,*vetor_y;
    srand(time(NULL));
    printf("Digite a quantidade de valores: ");
    scanf("%d", &qtd);
    printf("Digite a range do erro: ");
    scanf("%f", &range_erro);
    printf("Digite o espaco entre os valores gerados: ");
    scanf("%d", &passo);
    vetor_x = (float*) new float[qtd];
    vetor_y = (float*) new float[qtd];
    for(int i=0;i<qtd;i++)
    {
        vetor_x[i] = soma + 1+rand()%(passo);
        soma = vetor_x[i];
        if(range_erro!=0)
        {
            vetor_x[i]+= gera_erro(range_erro);
            
        }

    }
    float param[4];
    printf("Digite a funcao desejada:\n1-Linear\n2-Quadrada\n3-Cubica\n4-Racional\n");
    scanf("%d",&escolha);
    switch(escolha)
    {
        case 1:
            for(int i=0;i<2;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= linear(vetor_x[i],param[1],param[2]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        
        case 2:
            for(int i=0;i<3;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= quadrada(vetor_x[i],param[1],param[2],param[3]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        case 3:
            for(int i=0;i<4;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= cubica(vetor_x[i],param[1],param[2],param[3],param[4]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        case 4:
            for(int i=0;i<2;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= racional(vetor_x[i],param[1],param[2]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;

    }
    FILE *f = fopen("func.csv","w");
    for(int i=0;i<qtd;i++)
    {
        fprintf(f,"%f;%f;%f;%f\n",vetor_x[i],range_erro,vetor_y[i],range_erro);
    }
}