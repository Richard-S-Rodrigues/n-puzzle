#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

void swap (int *a, int *b);

int main() {
    int n, i, j, count = 1;

    setlocale(LC_ALL, "");

    printf("\nDigite n(entre 3 e 5): ");
    scanf("%d", &n);

    if (n < 3 || n > 5) {
        printf("\nValor incorreto!\n");
        return 0;
    }

    int values_in_board[n][n];
    int board[n][n];
    int board_copy[n][n];

    void get_random(int arr[n][n], int size) {
        int i, j, y, x;

        srand(time(NULL));

        for(i = size - 1; i > 0; i--) {
            for(j = size - 1; j > 0; j--) {
                y = rand() % (i + 1);
                x = rand() % (j + 1);
                swap(&arr[i][j], &arr[y][x]);
            }
        }
    }

    int handle_keys(int arr[n][n], int size) {
        int i, j, cached_i, cached_j, is_valid_key = 0;
        char input;

        // Irá guardar a coordenada do 'X' toda vez que um novo tabuleiro for gerado
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                if (arr[i][j] == 'X') {
                    cached_i = i;
                    cached_j = j;
                }
            }
        }

        input = getch();

        switch(input) {
            case -32:
                is_valid_key = 1;
                break;
            case 72: // Cima
                if (cached_i > 0) {
                    swap(&arr[cached_i][cached_j], &arr[cached_i-1][cached_j]);
                }
                break;
            case 75: // Esquerda
                if (cached_j > 0) {
                    swap(&arr[cached_i][cached_j], &arr[cached_i][cached_j-1]);
                }
                break;
            case 77: // Direita
                if (cached_j < size - 1) {
                    swap(&arr[cached_i][cached_j], &arr[cached_i][cached_j+1]);
                }
                break;
            case 80: // Baixo
                if (cached_i < size - 1) {
                    swap(&arr[cached_i][cached_j], &arr[cached_i+1][cached_j]);
                }
                break;
            default:
                is_valid_key = 1;
                break;

        }
        return is_valid_key;
    }

    void render_board(int arr[n][n], int size) {
        int equal;
        int is_valid_key = handle_keys(arr, size);

        // '0' = sim e '1' se n�o.
        // Evita contagens a mais
        if (is_valid_key == 0) {
            count++;
        }
        // Limpa a tela - Windows
        system("cls");

        for (i = 0; i < size; i++) {
            printf("\n");
            for (j = 0; j < size; j++) {
                 if (arr[i][j] == 88) {
                    printf("X\t");
                 } else {
                    printf("%d\t", arr[i][j]);
                 }

                 if (arr[i][j] != board_copy[i][j]) {
                    equal = 0;
                 } else {
                    equal += 1;
                 }
            }
            printf("\n");
        }

        if (equal < size * size) {
            render_board(board, n);
        } else {
            printf("\nSucesso!\nNúmero de movimentos: %d\n", (count));
        }

    }

    // Armazena os valores
    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            values_in_board[i][j] = count;
            count++;
        }
    }

    // Armazena os valores no tabuleiro
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (values_in_board[i][j] == n * n) {
                board[i][j] = 'X';
            } else {
                board[i][j] = values_in_board[i][j];
            }
        }

    }

    // Copia do tabuleiro ordenado
    memcpy(board_copy, board, sizeof board_copy);

    // Embaralha os elementos do tabuleiro
    get_random(board, n);

    count = 0;
    render_board(board, n);

    return 0;
}

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


