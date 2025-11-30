#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/admin.h"
#include "../../include/teste.h"
#include "teste.h"

Answer answer[20];


Curso buildQuestion(Curso curso,int n){
    Teste teste=curso.teste[n];
    int c=0;
    int last=teste.qtd+1;
    if (teste.qtd==0)
    {
        printf("Informe a quantidade de question\n");
        scanf("%i",&teste.qtd);
        getchar();
    }else{
        printf("Informe a quantidade de question sera adicionada \n");
        scanf("%i",&c);
        teste.qtd+=c;
        getchar();
    }
    
    
    for (int i = last; i <= teste.qtd; i++)
    {
        
        printf(linha);
        printf("     Gerando o teste de admissao de %s\n",teste.nome);
        printf(linha);
       
        printf("Informe a pergunta da questão %i \n",i);
        fgets(teste.asks[i-1].question,200,stdin);
        teste.asks[i-1].question[strcspn(teste.asks[i-1].question,"\n")]='\0';
        printf("Informe a resposta verdadeira \n");
        fgets(teste.asks[i-1].solution,200,stdin);
        teste.asks[i-1].solution[strcspn(teste.asks[i-1].solution,"\n")]='\0';
        for (int f = 0; f < 3; f++)
        {
            char fSl[10];
            printf("Informe a resposta falsa \n");
            fgets(teste.asks[i-1].other[f],200,stdin);
            teste.asks[i-1].other[f][strcspn(teste.asks[i-1].other[f],"\n")]='\0';
        }
         if (verifyTechnicalErrors(teste.asks[i-1])){
            printf("A questao possui erros tera de reformular a questao nº%i \n",i);
            i--;
            continue;
        }
        printf("Perfeito pergunta adicionada\n");
        printf("Clique em enter para continuar\n");
        getchar();
        
    }
    curso.teste[n]=teste;
    EditCurso(curso);
    return curso;
}


Curso editQuestion(Curso curso, int n){
    Teste teste = curso.teste[n];
    
    // Lista as perguntas da disciplina
    printf("=========================================\n");
    printf("EDITAR PERGUNTAS - %s\n", teste.nome);
    printf("=========================================\n");
    
    if (teste.qtd == 0) {
        printf("Nao existem perguntas nesta disciplina.\n");
        printf("Pressione Enter para voltar...");
        getchar();
        return;
    }
    
    // Mostra todas as perguntas
    for (int i = 0; i < teste.qtd; i++) {
        printf("%d. %s\n", i + 1, teste.asks[i].question);
    }
    
    // Seleciona qual pergunta editar
    int pergunta_num;
    do {
        printf("\nSelecione o numero da pergunta a editar (1-%d): ", teste.qtd);
        scanf("%d", &pergunta_num);
        getchar();
        
        if (pergunta_num < 1 || pergunta_num > teste.qtd) {
            printf("Numero invalido! Tente novamente.\n");
        }
    } while (pergunta_num < 1 || pergunta_num > teste.qtd);
    
    int index = pergunta_num - 1;
    
    // Menu de edição
    int opcao;
    do {
        printf("\n=========================================\n");
        printf("EDITANDO PERGUNTA %d\n", pergunta_num);
        printf("=========================================\n");
        printf("Pergunta atual: %s\n", teste.asks[index].question);
        printf("Resposta correta: %s\n", teste.asks[index].solution);
        printf("Alternativas incorretas:\n");
        for (int i = 0; i < 3; i++) {
            printf("  %d. %s\n", i + 1, teste.asks[index].other[i]);
        }
        printf("\nOPCOES:\n");
        printf("1 - Alterar pergunta\n");
        printf("2 - Alterar resposta correta\n");
        printf("3 - Alterar alternativas incorretas\n");
        printf("4 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Nova pergunta: ");
                fgets(teste.asks[index].question, 200, stdin);
                teste.asks[index].question[strcspn(teste.asks[index].question, "\n")] = '\0';
                printf("Pergunta atualizada com sucesso!\n");
                break;
                
            case 2:
                printf("Nova resposta correta: ");
                fgets(teste.asks[index].solution, 200, stdin);
                teste.asks[index].solution[strcspn(teste.asks[index].solution, "\n")] = '\0';
                printf("Resposta correta atualizada com sucesso!\n");
                break;
                
            case 3:
                printf("ALTERNATIVAS INCORRETAS:\n");
                for (int i = 0; i < 3; i++) {
                    printf("Nova alternativa incorreta %d: ", i + 1);
                    fgets(teste.asks[index].other[i], 200, stdin);
                    teste.asks[index].other[i][strcspn(teste.asks[index].other[i], "\n")] = '\0';
                }
                printf("Alternativas atualizadas com sucesso!\n");
                break;
                
            case 4:
                printf("Voltando ao menu anterior...\n");
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 4) {
            printf("Pressione Enter para continuar...");
            getchar();
        }
        
    } while (opcao != 4);
    
    // Atualiza o curso
    curso.teste[n] = teste;
    EditCurso(curso);
    return curso;
}

 int verifyTechnicalErrors(Question teste){

    if (strlen(teste.question)==0||strlen(teste.solution)==0)
        return 1;
    for (int i = 0; i < 3; i++)
    {
        if (strlen(teste.other[i])==0)
            return 1;
        if (!strcmp(teste.solution,teste.other[i]))
            return 1;
    }
    return 0;
}

float analiseAnswer(Question asks[],int qtd){
    float media=0;
    for (int i = 0; i < qtd; i++)
    {
        media += strcmp(answer[i].value, asks[i].solution) == 0 ? 1 : 0;
    }
    return media;
}

void printSolution(Question ask,int cont){
    printf("-------------------------\nQuestão nº %i \n",cont);
    printf("%s\n",&ask.question);
    Answer* answers= buildRandomSolution(ask);
    for (int c = 0; c < 4; c++)
    {
        printf("%c) %s\n",answers[c].choose,answers[c].value);
    }
    scanf(" %c", &answer[cont-1].choose);
    getchar();
    for (int j = 0; j < 4; j++)
    {
        if (answer[cont-1].choose==answers[j].choose)
            strcpy(answer[cont-1].value,answers[j].value);
    }
}


void shuffle(char *arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char *aux = arr[i];
        arr[i] = arr[j];
        arr[j] = aux;
    }
}

Answer* buildRandomSolution(Question teste){
    char p[]="abcd";
    char *answerValues[4]={
        teste.solution,
        teste.other[0],
        teste.other[1],
        teste.other[2],
    };

    shuffle(answerValues,4);

    Answer *answer = malloc(sizeof(Answer) * 4);

    if (!answer) return NULL;
    for (int i = 0; i < strlen(p); i++)
    {
        answer[i].choose=p[i];
        strcpy(answer[i].value, answerValues[i]);
    }
   return answer;
}


