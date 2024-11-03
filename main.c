#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#define MAX_USUARIOS 50

void linhaCol(int lin, int col) { // PROCEDIMENTO PARA POSICIONAR O CURSOR NO CONSOLE
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col-1, lin-1});
}

enum { // CORES DE OP��ES DE LETRAS
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum { // CORES DAS OP��ES DE FUNDO
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

// Prototipa��o da fun��o menu
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
    getch(); // Aguarda uma tecla antes de retornar ao menu, nos outros tamb�m funcionar� assim
    system("cls");
}

void listar() {
    system("cls");
    printf("================ LISTA DE USU�RIOS =================\n");
    if (total_usuarios == 0) {
        printf("Nenhum usu�rio cadastrado.\n\n");
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

void atualizar(){
    system("cls");
    int encontrado = -1;
    char nomeAt[50];
    char senhaAt[50];

    printf("Digite o nome do usuario que ira atualizar: ");
    scanf("%s", nomeAt);

    for(int i=0;i < total_usuarios;i++){
        if(strcmp(u[i].nome, nomeAt) == 0){
            encontrado = i;
            printf("Digite a nova senha: ");
            scanf("%s", senhaAt);
            break;
        }
        
    } 
    
    if(encontrado != -1){
        strcpy(u[encontrado].senha, senhaAt);
        
        printf("Usuario atualizado com sucesso!");
        printf("\nPressione qualquer tecla para voltar ao menu...");
        getch(); // Aguarda uma tecla antes de retornar ao menu, nos outros tamb�m funcionar� assim
        system("cls");
    } else {
        printf("Usuario nao encontrado! Tente novamente");
        printf("\nPressione qualquer tecla para voltar ao menu...");
        getch(); // Aguarda uma tecla antes de retornar ao menu, nos outros tamb�m funcionar� assim
        system("cls");
    }
}

void deletar(){
    system("cls");

    char nomeDel[50];

    printf("Digite o nome do usuario que deseja deletar: ");
    scanf("%s", nomeDel);

    int encontrado = -1;

    for(int i=0;i < total_usuarios;i++){
        if(strcmp(u[i].nome, nomeDel) == 0){
            encontrado = i;
            break;
        }
    } 

    if(encontrado != -1){
        for(int i=0;i < total_usuarios;i++){
            u[i] = u[i+1];
        }
        total_usuarios--;
        printf("Usuario deletado com sucesso!");
        printf("\nPressione qualquer tecla para voltar ao menu...");
        getch(); // Aguarda uma tecla antes de retornar ao menu, nos outros tamb�m funcionar� assim
        system("cls");
    } else {
        printf("Usuario nao encontrado!");
        printf("\nPressione qualquer tecla para voltar ao menu...");
        getch(); // Aguarda uma tecla antes de retornar ao menu, nos outros tamb�m funcionar� assim
        system("cls");
    }
}

void menu() {
    int opcao = 1;  // OP��O INICIAL
    int tecla;

    textColor(WHITE, _BLACK);
    system("cls"); 

    textColor(WHITE, _BLUE);
    box(10, 20, 20, 60);  

    linhaCol(11, 31);
    printf("BEM VINDO AO CRUD!");    
    linhaCol(13, 22);
    printf("Escolha a opcao que deseja executar:");

    // LA�O DE REPETI��O PARA MENU E NAVEGA��O
    while (1) {

        // Exibindo as op��es e destacando a op��o selecionada
        for (int i = 1; i <= 5; i++) {
            linhaCol(14 + i, 27); 

            // Destaca a linha selecionada
            if (i == opcao) {
                textColor(BLUE, _CYAN);  // Fundo ciano para a linha selecionada
            } else {
                textColor(WHITE, _BLUE);  // Fundo azul padr�o para outras linhas dentro da caixa
            }

            switch (i) {
                case 1: printf("     Cadastrar Usuario     "); break;
                case 2: printf("     Listar Usuarios       "); break;
                case 3: printf("     Atualizar Usuarios    "); break;
                case 4: printf("     Deletar Usuario       "); break;
                case 5: printf("     Sair                  "); break;
            }
        }

        tecla = getch();

        if (tecla == 224) { // NAVEGA��O COM AS SETAS
            tecla = getch();
            if (tecla == 72 && opcao > 1) {
                opcao--;
            } else if (tecla == 80 && opcao < 5) {
                opcao++;
            }
        } else if (tecla == 13) {  // Enter para selecionar a op��o
            break;
        }
    }

    // Executa a op��o selecionada e volta a cor para o preto e branco padr�o do console
    textColor(WHITE, _BLACK);
    
    switch (opcao) {
        case 1: cadastrar(); break;
        case 2: listar(); break;
        case 3: atualizar(); break;
        case 4: deletar(); break;
        case 5: 
            linhaCol(23, 22);
            textColor(WHITE, _BLACK);
            return;
    }

    menu();  // Retorna ao menu principal ap�s executar a op��o
} 

int main() {
    setlocale(LC_ALL, "portuguese");
    menu();
    return 0;
}

