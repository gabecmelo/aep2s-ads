#include <stdio.h>
#include <stdlib.h>

#define MAX_USUARIOS 50

struct usuario {
    char nome[50];
    char senha[50];
};

struct usuario u[MAX_USUARIOS];
int total_usuarios = 0;

// Prototipação da função menu
void menu();

void cadastrar() {
    system("cls");
    if (total_usuarios >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido!\n");
        return;
    }

    printf("Digite o nome: \n");
    scanf("%49s", u[total_usuarios].nome); 

    printf("Digite a senha: \n");
    scanf("%49s", u[total_usuarios].senha); 

    total_usuarios++; 
    printf("Usuario cadastrado com sucesso!\n");
    system("cls");
}

void listar(){
    system("cls");
    for(int i=0;i<total_usuarios;i++){
        printf("Nome: %s\n", u[i].nome);
        printf("Senha: %s\n", u[i].senha);
        printf("\n");
        
    }

    menu();
}


void menu() {
    int op;

    do {
        printf("Digite a opçao que deseja executar: \n");
        printf("1 - Cadastrar Usuario\n");
        printf("2 - Listar Usuarios\n");
        printf("3 - Atualizar Usuarios\n");
        printf("4 - Deletar Usuario\n");
        printf("5 - Sair\n");
        scanf("%i", &op);

        switch (op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: // atualizar(); break;
            case 4: // deletar(); break;
            case 5: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n"); break;
        }

    } while (op != 5);
}


int main() {
    printf("Bem-vindo ao CRUD!\n");
    menu();
    return 0;
}
