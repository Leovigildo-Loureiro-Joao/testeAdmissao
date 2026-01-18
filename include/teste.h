
#ifndef TESTE_H
#define TESTE_H

    typedef struct {
        char question[200];
        char solution[200];
        char other[3][200];
    } Question;

    typedef struct {
        char nome[100];
        int qtd;
        Question asks[20];
    } Teste;

    typedef struct 
    {
        char nome [100];
        int num_disc;
        Teste teste [20];
    } Curso;

    extern Curso cursos[20];

    typedef struct
    {
        char choose;
        char value[200];
    } Answer;



    int BuscarCurso();

    void SaveCurso(Curso *curso);

    void EditCurso(Curso curso);

    void PrepararCurso(Curso curso);

    void GerarMenuTeste(Curso curso,int n);
    Curso editQuestion(Curso curso, int n);
    Curso Reiniciar(Curso curso,int n);

    void DeleteCurso();

    void ListCurso();

    int SelectDisciplina(Curso curso);

    Curso buildQuestion(Curso curso,int n);

    int SelectCurso(char * info);

    float analiseAnswer(Question asks[],int qtd);

    void printSolution(Question ask,int cont);

    Answer* buildRandomSolution(Question teste);

    void VerResultados();
    
    int mainAluno();

#endif
