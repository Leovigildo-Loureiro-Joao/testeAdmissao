#include <stdio.h>
#include "../../include/admin.h"
#include "../../include/teste.h"

int main(){
    int n;
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