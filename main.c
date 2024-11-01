#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#define MAX_USUARIOS 50

void linhaCol(int lin, int col) { // PROCEDIMENTO PARA POSICIONAR O CURSOR NO CONSOLE
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col-1, lin-1});
}

enum { // CORES DE OPÇÕES DE LETRAS
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum { // CORES DAS OPÇÕES DE FUNDO
	_BLACK=0, _BLUE=16, _GREEN=32, _CYAN=48, _RED=64, _MAGENTA=80, _BROWN=96, _LIGHTGRAY=112, _DARKGRAY=128, 
	_LIGHTBLUE=144, _LIGHTGREEN=160, _LIGHTCYAN=176, _LIGHTRED=192, _LIGHTMAGENTA=208, _YELLOW=224, _WHITE=240
};

void textColor(int letras, int fundo) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + fundo);
}

void box(int lin1, int col1, int lin2, int col2) {
    int i, j;

    // IMPRIMINDO A LINHA SUPERIOR
    linhaCol(lin1, col1);
    printf("+");
    for (i = col1 + 1; i < col2; i++) {
        printf("-");
    }
    printf("+");

    // LATERAIS E FUNDO DA CAIXA
    for (i = lin1 + 1; i < lin2; i++) {
        linhaCol(i, col1);
        printf("|");
        for (j = col1 + 1; j < col2; j++) {
            linhaCol(i, j);
            printf(" ");
        }
        linhaCol(i, col2);
        printf("|");
    }

    // LINHA INFERIOR
    linhaCol(lin2, col1);
    printf("+");
    for (i = col1 + 1; i < col2; i++) {
        printf("-");
    }
    printf("+");
}

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
    printf("\nPressione qualquer tecla para voltar ao menu...");
    getch(); // Aguarda uma tecla antes de retornar ao menu, nos outros também funcionará assim
    system("cls");
}

void listar() {
    system("cls");
    printf("================ LISTA DE USUÁRIOS =================\n");
    if (total_usuarios == 0) {
        printf("Nenhum usuário cadastrado.\n\n");
    } else {
        for(int i = 0; i < total_usuarios; i++) {
            printf("Nome: %s\n", u[i].nome);
            printf("Senha: %s\n", u[i].senha);
            printf("-------------------------------------------\n");
        }
    }
    printf("\nPressione qualquer tecla para voltar ao menu...");
    getch();
}

void menu() {
    int opcao = 1;  // OPÇÃO INICIAL
    int tecla;

    textColor(WHITE, _BLACK);
    system("cls"); 

    textColor(WHITE, _BLUE);
    box(10, 20, 20, 60);  

    linhaCol(11, 31);
    printf("BEM VINDO AO CRUD!");    
    linhaCol(13, 22);
    printf("Escolha a opção que deseja executar:");

    // LAÇO DE REPETIÇÃO PARA MENU E NAVEGAÇÃO
    while (1) {

        // Exibindo as opções e destacando a opção selecionada
        for (int i = 1; i <= 5; i++) {
            linhaCol(14 + i, 27); 

            // Destaca a linha selecionada
            if (i == opcao) {
                textColor(BLUE, _CYAN);  // Fundo ciano para a linha selecionada
            } else {
                textColor(WHITE, _BLUE);  // Fundo azul padrão para outras linhas dentro da caixa
            }

            switch (i) {
                case 1: printf("     Cadastrar Usuário     "); break;
                case 2: printf("     Listar Usuários       "); break;
                case 3: printf("     Atualizar Usuários    "); break;
                case 4: printf("     Deletar Usuário       "); break;
                case 5: printf("     Sair                  "); break;
            }
        }

        tecla = getch();

        if (tecla == 224) { // NAVEGAÇÃO COM AS SETAS
            tecla = getch();
            if (tecla == 72 && opcao > 1) {
                opcao--;
            } else if (tecla == 80 && opcao < 5) {
                opcao++;
            }
        } else if (tecla == 13) {  // Enter para selecionar a opção
            break;
        }
    }

    // Executa a opção selecionada e volta a cor para o preto e branco padrão do console
    textColor(WHITE, _BLACK);
    
    switch (opcao) {
        case 1: cadastrar(); break;
        case 2: listar(); break;
        case 3: /* atualizar(); */ break;
        case 4: /* deletar(); */ break;
        case 5: 
            linhaCol(23, 22);
            textColor(WHITE, _BLACK);
            return;
    }

    menu();  // Retorna ao menu principal após executar a opção
} 

int main() {
    setlocale(LC_ALL, "portuguese");
    menu();
    return 0;
}

