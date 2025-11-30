
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/admin.h"
#include "../../include/teste.h"

void Gerar_Prova(){
    Curso novo;
    
    memset(&novo, 0, sizeof(Curso));
    printf(linha);
    printf("       Gerando a prova...\n");
    printf(linha);
    getchar();
    printf("Informe o nome do curso:\n");
    fgets(novo.nome,100,stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    /*Itemos agora pedir a quantidade de disciplinas para limitar o array de Testes*/
    printf("Informe o numero de disciplinas:\n");
    scanf("%d",&novo.num_disc);
    getchar();
    /*Itemos agora o nome de cada desciplina para podermos identicalas cada uma em si */
    for (int i = 1; i <= novo.num_disc; i++)
    {
        printf("Informe o nome da %iº disciplina:\n",i);
        fgets(novo.teste[i-1].nome,100,stdin);
        novo.teste[i-1].qtd = 0;
        novo.teste[i-1].nome[strcspn(novo.teste[i-1].nome, "\n")] = '\0';
        
    }
     Curso *curso= &novo;
    
    SaveCurso(curso);
    PrepararCurso(novo);
}

int SelectDisciplina(Curso curso){
     /*Itemos agora o nome de cada desciplina para podermos identicalas cada uma em si */
    int ch;
    do{
        printf(linha);
        printf("Insere a posicao da disciplina\n");
        printf("Ou degite 0 para sair\n");
        for (int i = 1; i <= curso.num_disc; i++)
        {
            printf("%i-%s\n",i,curso.teste[i-1].nome);
        }
        scanf("%i",&ch);
        if(ch==0)
         return ch;
        if(!(ch>0&&ch<curso.num_disc+1)) 
            printf("Erro este valor nao perterce ao intervalo\n");
        getchar();
        
    } while (!(ch>0&&ch<curso.num_disc+1));
    return ch-1;
}

Curso DeleteDisciplina(Curso curso, char* seccao){
     /*Itemos agora o nome de cada desciplina para podermos identicalas cada uma em si */
    int ch;
    do{
        printf(linha);
        printf("Insere a posicao da %s que sera removida\n",seccao);
        printf("Ou degite 0 para sair\n");
        for (int i = 1; i <= curso.num_disc; i++)
        {
            printf("%i-%s\n",i,curso.teste[i-1].nome);
        }
        scanf("%i",&ch);

        if(ch==0)
         return curso;
         printf("Removendo a disciplina %s\n",curso.teste[ch-1].nome);
        if(!(ch>0&&ch<curso.num_disc+1)) 
            printf("Erro este valor nao perterce ao intervalo\n");
        getchar();
        
    } while (!(ch>0&&ch<curso.num_disc+1));
    curso.num_disc--;
    for (int i = ch-1; i < curso.num_disc; i++)
    {
        curso.teste[i]=curso.teste[i+1];
    }
    memset(&curso.teste[curso.num_disc], 0, sizeof(Teste));
    printf("Disciplina removida com sucesso \n");
    EditCurso(curso);
    return curso;
}

void GerarMenuTeste(Curso curso,int n){
     
    int ch;
    do 
    {    
        printf(linha);
        printf("    Construindo Teste\n");
        printf(linha);
        printf("1-Adicionar perguntas/respostas teste\n");
        printf("2-Editar perguntas/respostas teste\n");
        printf("3-Reiniciar teste\n");
        printf("4-Voltar\n");
        scanf("%i",&ch);
        switch (ch)
        {
        case 1:
           curso=buildQuestion(curso,n);
            break;
        case 2:
            curso=editQuestion(curso, n);
            break;
        case 3:
            curso=Reiniciar(curso,n);
            break;
        default:
             printf("Erro degite um valor encontrado no intervalo\nTecla qualquer para continuar");
             getchar();
        }
   }while(ch!=3);
   
}

Curso AdicionarDisciplina(Curso curso){
    getchar();
    printf("Informe o nome da %iº disciplina:\n",curso.num_disc+1);
    fgets(curso.teste[curso.num_disc].nome,100,stdin);
    curso.teste[curso.num_disc].qtd = 0;
    curso.teste[curso.num_disc].nome[strcspn(curso.teste[curso.num_disc].nome, "\n")] = '\0';   
    curso.num_disc++;
    EditCurso(curso);
    return curso;
}


Curso Reiniciar(Curso curso,int n){
    char c;
    printf("Deseja realmente reiniciar(S/N)\n");
    scanf("%c",&c);
    if (c=='S')
    {   
        memset(curso.teste[n].asks,0,sizeof(Question));
        EditCurso(curso);   
    }
    return curso;
}

void PrepararCurso(Curso curso){
    
    int ch;
    do 
    {
        printf(linha);
        printf("    Preparando as disciplinas do curso\n");
        printf(linha);
        printf("1-Selecionar disciplina\n");
        printf("2-Remover disciplina\n");
        printf("3-Adicionar disciplina\n");
        printf("4-Voltar\n");
        scanf("%i",&ch);
        switch (ch)
        {
        case 1:
            int select=SelectDisciplina(curso);
            if (select>=0)
            {
                GerarMenuTeste(curso,select);
            }
            break;
        case 2:
            curso=DeleteDisciplina(curso,"disciplina");
            break;
        case 3:
            curso=AdicionarDisciplina(curso);
            break;
        default:
            printf("Erro degite um valor encontrado no intervalo\nTecla qualquer para continuar");
            getchar();
        }
    }while(ch!=4);
}

void VerResultados() {
    printf("=========================================\n");
    printf("          RESULTADOS DOS ALUNOS\n");
    printf("=========================================\n");
    
    FILE *arquivo = fopen("data/alunos.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum resultado encontrado.\n");
        return;
    }
    
    AlunoResult aluno;
    int count = 0;
    
    while (fread(&aluno, sizeof(AlunoResult), 1, arquivo) == 1) {
        printf("Aluno: %s\n", aluno.nome);
        printf("Nº Inscrição: %d\n", aluno.numInscricao);
        printf("Curso: %s\n", aluno.curso);
        printf("Média: %.2f/20\n", aluno.media);
        printf("Status: %s\n", aluno.media >= 10 ? "APROVADO" : "REPROVADO");
        printf("-----------------------------------------\n");
        count++;
    }
    
    fclose(arquivo);
    
    if (count == 0) {
        printf("Nenhum aluno realizou testes ainda.\n");
    } else {
        printf("Total de alunos: %d\n", count);
    }
    
    printf("Pressione Enter para continuar...");
    getchar();
    getchar();
}

