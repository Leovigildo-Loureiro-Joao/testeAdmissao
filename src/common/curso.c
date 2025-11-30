#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/teste.h"

const int MAX_CURSOS=20;
Curso cursos[20];



void SaveCurso(Curso *curso){ 
    FILE *arquivo=fopen("data/cursos.dat","ab");
    if (arquivo==NULL)
    {
        printf("Erro ao criar ou abrir o file");
    }else{
        fwrite(curso, sizeof(Curso), 1, arquivo);
        fclose(arquivo);
        printf("Curso '%s' salvo com sucesso!\n", curso->nome);
    } /* 
   
    */
}

int BuscarCurso(){ 
    int n=0;
    FILE *arquivo=fopen("data/cursos.dat","rb");
    if (arquivo==NULL)
    {
        printf("Erro ao criar ou abrir o file");
    }else{
        while (fread(&cursos[n],sizeof(Curso),1,arquivo)==1&&MAX_CURSOS>n)
        {
            n++; 
        }
        fclose(arquivo);
    } 
    return n;
}

void EditCurso(Curso curso){ 
    int n=BuscarCurso();
    RefreshCursos(curso,n);
    FILE *arquivo=fopen("data/cursos.dat","wb");
    if (arquivo==NULL)
    {
        printf("Erro ao criar ou abrir o file\n");
    }else{    
        fwrite(cursos,sizeof(Curso),n,arquivo);
        fclose(arquivo);
        printf("Salvo com sucesso\n");
    } 
}

void RefreshCursos(Curso curso,int count){
    for (int i = 0; i < count; i++)
    {
       if (strcmp(cursos[i].nome,curso.nome)==0)
       {
            cursos[i]=curso;
            printf("Curso %s editado com sucesso\n",curso.nome);
            break;
       }
       
    }
    
}

void GerarMenuSeccao(){
    int sel=SelectCurso("Selecione um curso");
    PrepararCurso(cursos[sel]);
   
}

int SelectCurso(char * info){
    int limite=BuscarCurso();
    int ch;
    do{
        printf("-------------------------------\n");
        printf("%s\n",info);
        for (int i = 1; i <= limite; i++)
        {
            printf("%i-%s\n",i,cursos[i-1].nome);
            
        }
        scanf("%i",&ch);
        if(!(ch>0&&ch<limite+1)) printf("Erro este valor nao perterce ao intervalo\n");
        getchar();
        
    } while (!(ch>0&&ch<limite+1));
    return ch-1;
}


void DeleteCurso(){

}

void ListCurso(){ 
    
    int n=BuscarCurso();
    printf("=========================================\n");
    printf("          CURSOS CADASTRADOS\n");
    printf("=========================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("  Cursos - %s\n",cursos[i].nome);
        ListTests(cursos[i].teste,cursos[i].num_disc);
        printf("____________________________________\n\n");
    }
    printf("Clique qualquer tecla para voltar ao menu principal...\n");
    getchar();
    getchar();
    
}


void ListAsks(Question asks[],int qtd){
    for (int c = 0; c < qtd; c++)
    {
        printf("    %s\n",asks[c].question);
    }
}

void ListTests(Teste teste[],int num_disc){
    for (int t = 0; t < num_disc; t++)
    {
        printf("   Teste de %s(%i)\n",teste[t].nome,teste[t].qtd);
        if(teste[t].qtd==0) {
            printf("    <vazio>\n");
        }else{ ListAsks(teste[t].asks,teste[t].qtd);}
        
    }
   
}
