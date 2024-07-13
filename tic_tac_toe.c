//Gabriel Nobrega Toscano

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char tabuleiro[3][3]; //Variavel char -- O tabuleiro 3x3 (Matriz)

// funcao para imprimir o tabuleiro -- Utiliza um loop para printar 3 vezes
void print_tabuleiro() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < 2)
            printf("---|---|---\n"); //Estrutura do tabuleiro (Linhas e colunas)
    }
    printf("\n");
}

// funcao para verificar se alguém ganhou ou se o tabuleiro está cheio
int checar() {
    // Verificar linhas (i) e colunas(j)
    for (int i = 0; i < 3; i++) {
        if ((tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ') ||
            (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' '))
            return 1; // Se alguma linha ou colunauna tem todas as mesmas marcacoes
    }
    // Verificar diagonais
    if ((tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ') ||
        (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' '))
        return 1; // Se alguma diagonal tem todas as mesmas marcações

    // Verificar se o tabuleiro ta cheio
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ')
                return 0; // Ainda tem espacos vazios
        }
    }
    return -1; // Empatou
}

// funcao para a jogada do jogador
void jogador() {
    int linha, coluna;
    printf("Sua vez (linha | coluna): ");
    scanf("%d %d", &linha, &coluna);
    if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || tabuleiro[linha - 1][coluna - 1] != ' ') {
        printf("Jogada invalida! Deixa de ser burro e escolhe um numero entre 1 e 3.\n");
        jogador(); // Chamar recursivamente até que uma jogada válida seja feita
    } else {
        tabuleiro[linha - 1][coluna - 1] = 'X';
    }
}

// funcao para a jogada do computador
void computador() {
    // Verificar se a casa do meio está vazia
    if (tabuleiro[1][1] == ' ') {
        tabuleiro[1][1] = 'O';
        return;
    }

    // FAzer uma jogada aleatória
    int linha, coluna;
    do {
        linha = rand() % 3;
        coluna = rand() % 3;
    } while (tabuleiro[linha][coluna] != ' '); // Escolher uma posição vazia
    tabuleiro[linha][coluna] = 'O';
}

int main() {
    srand(time(NULL)); // Iniciar o gerador de números aleatórios

    // Iniciar o tabuleiro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }

    int vez_jogador = 1; // Ponto para indicar a vez do jogador

    while (1) {
        print_tabuleiro();
        int result = checar();
        if (result == 1) {
            printf("Você ganhou de mim. Parabens!\n");
            break;
        } else if (result == -1) {
            printf("Empatou. Somos duplamente burros!\n");
            break;
        }

        if (vez_jogador) {
            jogador();
        } else {
            printf("Computador está pensando... Aqui vai minha jogada: \n");
            computador();
        }

        vez_jogador = !vez_jogador; // Alternar a vez do jogador com o computador
    }

    print_tabuleiro();
    return 0;
}
