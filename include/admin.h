
#ifndef ADMIN

    #define ADMIN
    #define linha "======================================\n"
    typedef struct {
        int numInscricao;
        char nome[100];
        char curso[100];
        float media;
        // Adicione outros campos que existam na sua struct Aluno
    } AlunoResult;

    void GerarMenuAdmin();

    void Gerar_Prova();

    void GerarMenuSeccao();
    
    void VerResultados();
   

   

#endif