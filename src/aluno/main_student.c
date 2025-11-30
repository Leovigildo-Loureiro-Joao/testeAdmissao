#include <stdio.h>
#include "../../include/teste.h"
#include "../../include/Aluno.h"


int main(){
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

 