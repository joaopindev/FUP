#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ARQUIVO "filmes.txt"

typedef struct {
    int id;
    int duracao;
    float nota;
    char nome[51];
    char genero[51];
} Catalogo;

Catalogo* filme = NULL;
int qtd = 0;

void salvar_dados() {
    FILE *f = fopen(ARQUIVO, "w");
    if (f != NULL) {
        fprintf(f, "%d\n", qtd);
        for (int i = 0; i < qtd; i++) {
            fprintf(f, "%d\n%s\n%s\n%f\n%d\n",
                filme[i].id,
                filme[i].nome,
                filme[i].genero,
                filme[i].nota,
                filme[i].duracao
            );
        }
        fclose(f);
    }
}

void carregar_dados() {
   FILE *f = fopen(ARQUIVO, "r");
   if (f != NULL) {
       fscanf(f, "%d\n", &qtd);
       if (qtd > 0) {
           filme = malloc(qtd * sizeof(Catalogo));
           if (filme == NULL) {
               printf("Erro ao alocar memoria.\n");
               return;
           }
           for (int i = 0; i < qtd; i++) {
               fscanf(f, "%d\n", &filme[i].id);
               fscanf(f, "%50[^\n]\n", filme[i].nome);
               fscanf(f, "%50[^\n]\n", filme[i].genero);
               fscanf(f, "%f\n", &filme[i].nota);
               fscanf(f, "%d\n", &filme[i].duracao);
           }
       }
       fclose(f);
   }
}
void listar() {
    if (qtd == 0) {
        printf("Nenhum filme cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE FILMES ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d | Nome: %s | Nota: %.1f Estrelas | Duracao: %d minutos | Genero: %s\n", 
               filme[i].id, filme[i].nome, filme[i].nota, filme[i].duracao, filme[i].genero);
    }
    printf("\n");
}

void adicionar() {
    filme = realloc(filme, (qtd + 1) * sizeof(Catalogo));

    getchar();
    printf("Digite o nome do filme: ");
    scanf("%50[^\n]", filme[qtd].nome);
    getchar();

    printf("Digite o genero do filme: ");
    scanf("%50[^\n]", filme[qtd].genero);
    
    getchar();
    printf("Digite a nota do filme (DE 0 A 5): ");
    scanf("%f", &filme[qtd].nota);
    if (filme[qtd].nota > 5.0) {
        filme[qtd].nota = 5.0;
        printf("Nota maxima e 5! Valor ajustado.\n");
    }
    
    printf("Digite a duracao do filme: ");
    scanf("%d", &filme[qtd].duracao);

    filme[qtd].id = qtd + 1;
    qtd++;
    printf("Filme adicionado com sucesso!\n\n");
}

void editar() {
    int id;
    printf("Digite o ID do filme que deseja editar: ");
    scanf("%d", &id);

    for (int i = 0; i < qtd; i++) {
        if (filme[i].id == id) {
            getchar();

            printf("Novo nome do filme: ");
            scanf("%50[^\n]", filme[i].nome);

            getchar();
            printf("Novo genero do filme: ");
            scanf("%50[^\n]", filme[i].genero);

            printf("Nova nota do filme (DE 0 A 5): ");
            scanf("%f", &filme[i].nota);
            if (filme[i].nota > 5.0) {
                filme[i].nota = 5.0;
                printf("Nota maxima é 5! Valor ajustado.\n");
            }
            printf("Nova duracao do filme: ");
            scanf("%d", &filme[i].duracao);
            printf("Filme editado com sucesso!\n\n");
            return;
        }
    }
    printf("ID não encontrado.\n\n");
}

void remover() {
    int id;
    printf("Digite o ID do filme que deseja remover: ");
    scanf("%d", &id);

    for (int i = 0; i < qtd; i++) {
        if (filme[i].id == id) {
            for (int j = i; j < qtd - 1; j++) {
                filme[j] = filme[j + 1];
            }
            qtd--;
            filme = realloc(filme, qtd * sizeof(Catalogo));

            for (int i = 0; i < qtd; i++) {
                filme[i].id = i + 1;
            }

            printf("Filme removido com sucesso!\n");
            return;
        }
    }

    printf("ID nao encontrado.\n\n");
}


int main() {
    int op;

    carregar_dados();

    printf("  __  __                   _ _ _           " ANSI_COLOR_RED " ______ _ _      " ANSI_COLOR_RESET "\n");
    printf(" |  \\/  |                 | (_) |         " ANSI_COLOR_RED "|  ____| (_)     " ANSI_COLOR_RESET "\n");
    printf(" | \\  / | ___  _ __   ___ | |_| |_ ___  ___" ANSI_COLOR_RED "| |__  | |___  __" ANSI_COLOR_RESET "\n");
    printf(" | |\\/| |/ _ \\| '_ \\ / _ \\| | | __/ _ \\/ __" ANSI_COLOR_RED "|  __| | | \\ \\/ /" ANSI_COLOR_RESET "\n");
    printf(" | |  | | (_) | | | | (_) | | | || (_) \\__ \\" ANSI_COLOR_RED " |    | | |>  < " ANSI_COLOR_RESET "\n");
    printf(" |_|  |_|\\___/|_| |_|\\___/|_|_|\\__\\___/|___/" ANSI_COLOR_RED "_|    |_|_/_/\\_\\" ANSI_COLOR_RESET "\n");
    printf("\n");

    while (1) {
        printf("[1] - Listar filmes\n");
        printf("[2] - Adicionar filme\n");
        printf("[3] - Editar filme\n");
        printf("[4] - Remover filme\n");
        printf("[0] - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        if (op == 1) {
            listar();
        } else if (op == 2) {
            adicionar();
        } else if (op == 3) {
            editar();
        } else if (op == 4) {
            remover();
        } else if (op == 0) {
            salvar_dados();
            printf("Encerrando...\n");
            break;
        } else {
            printf("Opção invalida.\n");
        }
    }

    free(filme);
    return 0;
}
