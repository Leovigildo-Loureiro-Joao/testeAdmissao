#ifndef ALUNO_H
#define ALUNO_H

typedef struct {
    char nome [40];
    int numInscricao;
    int idCurso;
    float media;
} Aluno;

extern Aluno alunos[];

Aluno addDataOfStudent();

void searchDataOfStudent();

void SaveAluno(Aluno *alunos);

int BuscarAlunos();

void RealizarTeste();
int Exists(int inscrito);


#endif

