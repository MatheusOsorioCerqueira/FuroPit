#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//gera um erro randomico com base no parametro passado
float gera_erro(float max)
{
    int decimais = 0;
    int verifica = max;
    float retorno = 0;
    while(verifica - max != 0)
    {
        decimais++;
        max*=10;
        verifica = max;
    }
    decimais = pow(10,decimais);
    verifica = (rand()%verifica);
    retorno = verifica;
    retorno/=decimais;
    if(rand()%2 == 0)
        return retorno;
    else
        return -retorno;

}

float exponencial(float x, float a, float b)//funcao exponencial f(x)=B*e^(A*X)
{
    return b*exp(x*a);
}

float linear(float x, float a, float b)// função linear f(x)=AX+B
{
    return x*a + b;
}

float quadrada(float x, float a, float b, float c)//função quadrada f(x)=A*X² + B*x + C
{
    return a*x*x + b*x + c;
}

float cubica(float x, float a, float b, float c, float d)//função cubica f(x)=A*X³ + B*X² + C*X + D
{
    return a*x*x*x + b*x*x + c*x + d;
}

float racional(float x, float a, float b)//função racional f(x)= A/(X+B)
{
    return a/(x+b);
}

int main()
{
    
    int qtd,passo,incerteza,escolha,parametros;
    float range_erro,soma;
    float *vetor_x,*vetor_y;
    srand(time(NULL));
    printf("Digite a quantidade de valores: ");//quantidade de valores que terão no vetor gerado
    scanf("%d", &qtd);
    printf("Digite a range do erro: ");//tamanho do erro dos parametros
    scanf("%f", &range_erro);
    printf("Digite o espaco entre os valores gerados: ");//espaço maximo entre os valores
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
    printf("Digite a funcao desejada:\n1-Linear\n2-Quadrada\n3-Cubica\n5-Racional\n");//escolhe a função
    scanf("%d",&escolha);
    switch(escolha)
    {
        case 1:
            parametros = 2;
            for(int i=0;i<2;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= linear(vetor_x[i],param[0],param[1]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        
        case 2:
        parametros = 3;
            for(int i=0;i<3;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= quadrada(vetor_x[i],param[0],param[1],param[2]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        case 3:
        parametros = 4;
            for(int i=0;i<4;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= cubica(vetor_x[i],param[0],param[1],param[2],param[3]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        case 4:
        parametros = 2;
            for(int i=0;i<2;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= exponencial(vetor_x[i],param[0],param[1]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;
        case 5:
        parametros = 2;
            for(int i=0;i<2;i++)
            {
                printf("Var %c: ", ('A'+i));
                scanf("%f",&param[i]);
            }
            for(int i=0;i<qtd;i++)
            {
                vetor_y[i]= racional(vetor_x[i],param[0],param[1]);
                vetor_y[i]+=gera_erro(range_erro);
            }
            break;

    }
    FILE *f = fopen("func.csv","w");
    FILE *f2 = fopen("log.txt","w");
    for(int i=0;i<qtd;i++)
    {
        printf("%f;%f;%f;%f\n",vetor_x[i],range_erro,vetor_y[i],range_erro);
        fprintf(f,"%f;%f;%f;%f\n",vetor_x[i],range_erro,vetor_y[i],range_erro);//imprime arquivo .csv com os valores usados

    }
    //a partir daqui tudo imprime no log.txt e so é grande pra ficar bonito, não tem mais nada aqui
    for(int i=0;i<parametros;i++)
    {
        fprintf(f2,"Var %c: %f\n",('A'+parametros),param[i]);
    }
    fprintf(f2,"funcao usada: %d\n\nX=[",escolha);
    for(int i=0;i<qtd;i++)
    {
        fprintf(f2,"%f",vetor_x[i]);
        if(i<(qtd-1))
        {
            fprintf(f2,",");
        }
        else
        {
            fprintf(f2,"]\n\nY=[");
        }
    }
    for(int i=0;i<qtd;i++)
    {
        fprintf(f2,"%f",vetor_y[i]);
        if(i<(qtd-1))
        {
            fprintf(f2,",");
        }
        else
        {
            fprintf(f2,"]\n\nerro=[");
        }
    }
    for(int i=0;i<qtd;i++)
    {
        fprintf(f2,"%f",range_erro);
        if(i<(qtd-1))
        {
            fprintf(f2,",");
        }
        else
        {
            fprintf(f2,"]");
        }
    }
}