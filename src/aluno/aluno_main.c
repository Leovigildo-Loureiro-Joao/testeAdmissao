#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../../include/teste.h"
#include "../../include/Aluno.h"

Aluno alunos[];
Aluno selectAluno;
const int MAX_ALUNOS=20;

Aluno addDataOfStudent(){
    getchar();
    Aluno student;
    printf("Informe o seu nome caro candidato\n");
    fgets(student.nome,40,stdin);
    student.nome[strcspn(student.nome,"\n")]='\0';
    int value=1;
    while (value==1)
    {
        printf("Informe o seu numero de inscrição\n");
        scanf("%i",&student.numInscricao);
        getchar();
        value=Exists(student.numInscricao);
    } 
    
    student.idCurso=SelectCurso("Selecione o seu curso");
    SaveAluno(&student);
    selectAluno=student;
    return student;
}

void searchDataOfStudent(){
    getchar();
    BuscarAlunos();
    Aluno student;
    int value=0;
    while (value==0)
    {
        printf("Informe o seu numero de inscrição\n");
        scanf("%i",&student.numInscricao);
        getchar();
        value=Exists(student.numInscricao);
    } 
    printf("---------------------------------\n");
    printf("Candidato(a) %s\n",selectAluno.nome);
    printf("A sua media é de %.2f\n",selectAluno.media);
    printf("---------------------------------\n");
    printf("Prima qualquer tecla para voltar...");
    getchar();

}

int Exists(int inscrito){
    int tot=BuscarAlunos();
    int i;
    for (i = 0; i < tot; i++)
    { 
      if (alunos[i].numInscricao==inscrito)
      {
        selectAluno=alunos[i];
        return 1;
      }
    }
    return 0;
}

void SaveAluno(Aluno *aluno){
    FILE *f;
    if (f=fopen("data/alunos.dat","ab"))
    {
        fwrite(aluno,sizeof(Aluno),1,f);
        fclose(f);
        printf("Aluno inserido '%s' salvo com sucesso!\n", aluno->nome);
    }
    
}

void EditAluno(Aluno aluno){
    int n = BuscarAlunos();
    RefreshAluno(aluno, n);
    FILE *f = fopen("data/alunos.dat", "wb");
    if (f != NULL) {
        fwrite(alunos, sizeof(Aluno), n, f);
        fclose(f);
        printf("Dados do aluno '%s' salvo com sucesso!\n", aluno.nome);
    } else {
        printf("Erro ao abrir o arquivo para escrita!\n");
    }
}

void RefreshAluno(Aluno aluno,int n){
   int i;
    for (i = 0; i < n; i++)
    {
        if (alunos[i].numInscricao==aluno.numInscricao)
        {
            alunos[i]=aluno;
            break;
        }
    }
    
}

int BuscarAlunos(){
    FILE *f;
    int n=0;
	if ((f=fopen("data/alunos.dat","rb"))==NULL&&strlen(selectAluno.nome)==0)
    {
        f=fopen("data/alunos.dat","wb");
        fclose(f);
    }
    if (f=fopen("data/alunos.dat","rb"))
    {
        while (fread(&alunos[n],sizeof(Aluno),1,f)==1&&n<MAX_ALUNOS)
        {
            n++;
        }
    }
    fclose(f);
    return n;
}

void RealizarTeste(){
    Aluno aluno= addDataOfStudent();
    Curso curso= cursos[aluno.idCurso];
    aluno.media=0;
    int nteste,i;
    for ( nteste = 0; nteste < curso.num_disc; nteste++)
    {
        Teste teste=curso.teste[nteste];
        printf("Iniciando o teste de %s\n",teste.nome);
        for ( i = 1; i <= teste.qtd; i++)
        {
            printSolution(teste.asks[i-1],i);
        }
        aluno.media += (analiseAnswer(teste.asks,teste.qtd) / teste.qtd) * 20;
    }
    aluno.media=aluno.media/curso.num_disc;
    printf("O seu resultado foi %.2f\n",aluno.media);
    EditAluno(aluno);
    printf("Prima qualquer tecla para voltar...");
    getchar();
}



// main

int mainAluno(){
    int n;
    do
    {
        printf("============================\n");
        printf(" Bem vindo caro candidato\n");
        printf("============================\n");
        printf("1-Realizar teste\n");
        printf("2-Ver resultado\n");
        printf("3-Sair\n");
        printf("Selecione uma das opções\n");
        scanf("%i",&n);
        switch (n)
        {
        case 1:
            RealizarTeste();
            break;
        case 2:
            searchDataOfStudent();
            break;
        default:
            break;
        }
    } while (n!=3);
    
    return 0;
}



 



