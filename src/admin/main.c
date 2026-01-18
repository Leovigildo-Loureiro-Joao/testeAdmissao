#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../../include/admin.h"
#include "../../include/teste.h"
#include "../../include/Aluno.h"



/*Curso*/

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
	int i;
    for (i = 0; i < count; i++)
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
        int i ;
        for (i = 1; i <= limite; i++)
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
    int i ;
    for (i = 0; i < n; i++)
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
	int c; 
    for ( c = 0; c < qtd; c++)
    {
        printf("    %s\n",asks[c].question);
    }
}

void ListTests(Teste teste[],int num_disc){
	int t;
    for ( t = 0; t < num_disc; t++)
    {
        printf("   Teste de %s(%i)\n",teste[t].nome,teste[t].qtd);
        if(teste[t].qtd==0) {
            printf("    <vazio>\n");
        }else{ ListAsks(teste[t].asks,teste[t].qtd);}
        
    }
   
}

/*Utils*/
//----------------------------------

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
    int i;
    for (i = 1; i <= novo.num_disc; i++)
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
        int i;
        for (i = 1; i <= curso.num_disc; i++)
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
     int i;
    do{
        printf(linha);
        printf("Insere a posicao da %s que sera removida\n",seccao);
        printf("Ou degite 0 para sair\n");
       
        for (i = 1; i <= curso.num_disc; i++)
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
    for (i = ch-1; i < curso.num_disc; i++)
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
    
    int ch,select;
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
            select=SelectDisciplina(curso);
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
    BuscarCurso();
    FILE *arquivo = fopen("data/alunos.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum resultado encontrado.\n");
        return;
    }
    
    Aluno aluno;
    int count = 0;
    
    while (fread(&aluno, sizeof(Aluno), 1, arquivo) == 1) {

        printf("Aluno: %s\n", aluno.nome);
        printf("Nº Inscrição: %d\n", aluno.numInscricao);
        printf("Curso: %s\n", cursos[aluno.idCurso].nome);
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

//---------------------------------
//Teste
//-----------------------------------

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
    
    int i;
    for (i = last; i <= teste.qtd; i++)
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
        int f;
        for ( f = 0; f < 3; f++)
        {
            char fSl[10];
            printf("Informe a resposta falsa \n");
            fgets(teste.asks[i-1].other[f],200,stdin);
            teste.asks[i-1].other[f][strcspn(teste.asks[i-1].other[f],"\n")]='\0';
        }
         if (verifyTechnicalErrors(teste.asks[i-1])){
            printf("A questao possui erros tera de reformular a questão %iº \n",i);
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
        printf("Não existem perguntas nesta disciplina.\n");
        printf("Pressione Enter para voltar...");
        getchar();
        return;
    }
    
    // Mostra todas as perguntas
    int i;
    for ( i = 0; i < teste.qtd; i++) {
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
        int i;
        for ( i = 0; i < 3; i++) {
            printf("  %d. %s\n", i + 1, teste.asks[index].other[i]);
        }
        printf("\nOPÇÕES:\n");
        printf("1 - Alterar pergunta\n");
        printf("2 - Alterar resposta correta\n");
        printf("3 - Alterar alternativas incorretas\n");
        printf("4 - Voltar\n");
        printf("Escolha uma opção: ");
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
            	int i;
                for ( i = 0; i < 3; i++) {
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
                printf("Opção invalida! Tente novamente.\n");
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
	int i;
    if (strlen(teste.question)==0||strlen(teste.solution)==0)
        return 1;
    for ( i = 0; i < 3; i++)
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
	int i;
    for ( i = 0; i < qtd; i++)
    {
        media += strcmp(answer[i].value, asks[i].solution) == 0 ? 1 : 0;
    }
    return media;
}

void printSolution(Question ask,int cont){
    printf("-------------------------\nQuestão nº %i \n",cont);
    printf("%s\n",&ask.question);
    Answer* answers= buildRandomSolution(ask);
    int c,j;
    for ( c = 0; c < 4; c++)
    {
        printf("%c) %s\n",answers[c].choose,answers[c].value);
    }
    scanf(" %c", &answer[cont-1].choose);
    getchar();
    for ( j = 0; j < 4; j++)
    {
        if (answer[cont-1].choose==answers[j].choose)
            strcpy(answer[cont-1].value,answers[j].value);
    }
}


void shuffle(char *arr[], int n) {
	 int i;
    for ( i = n - 1; i > 0; i--) {
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
    int i;
    for ( i = 0; i < strlen(p); i++)
    {
        answer[i].choose=p[i];
        strcpy(answer[i].value, answerValues[i]);
    }
   return answer;
}

// Metodo principal

int main_admin(){
	int n=0;
   do
   {
        
        printf(linha);
        printf("     Bem vindo Administrador\n");
        printf(linha);
        printf("1-Criar Prova\n");
        printf("2-Editar Prova\n");
        printf("3-Ver Provas\n");
        printf("4-Visualizar Resultados\n");
        printf("5-Sair\n");
        scanf("%i",&n);
        switch (n)
        {
        case 1:
            Gerar_Prova();
            break;
        case 2:
            GerarMenuSeccao();
            break;
        case 3:
            ListCurso();
            break;
         case 4:
            VerResultados();
            break;
        default:
            break;
        }
   } while (n!=5);
   
    return 0;
}


int main(){
  setlocale(LC_ALL, "Portuguese");

   int n;
   do
   {
        printf(linha);
        printf("Bem vindo a simulação do teste de admissão\n");
        printf(linha);
        printf("|1-Simular Admin\n|Aqui ira gerar as provas para os cursos        \n");
        printf("|-------------------------------------------------------------------\n");
        printf("|2-Simular Aluno ou Candidato\n|Aqui ira fazer as provas ou teste de admissão do curso escolhido  \n|mas, este tem que existir na base de dados\n");
        printf("|-------------------------------------------------------------------\n");
        printf("|3-Sair da simulação\n");
        scanf("%i",&n);
        switch (n)
        {
        case 1:
            main_admin();
            break;
        case 2:
            mainAluno();
            break;
        default:
        	break;
        }
   } while (n!=3);
   
    return 0;
}
