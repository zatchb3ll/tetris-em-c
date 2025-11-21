#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ESTRUTURA
typedef struct {
    char nome;  
    int id;     
} Peca;

#define MAX_QUEUE 10  // tam max(no video falou 5 porem, 10 já vai ficar para os proximos niveis)

//fAbstrai a Fila
typedef struct {
    Peca pecas[MAX_QUEUE];
    int frente;
    int tras;    
    int tamanho; 
} Fila;

// Gera peça
Peca gerarPeca(int *contador_id) {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova_peca.nome = tipos[rand() % 4];
    nova_peca.id = (*contador_id)++;
    return nova_peca;
}

// Inicializa a Fila
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// FVerifica se tá cheia
int filaCheia(Fila *fila) {
    return fila->tamanho == MAX_QUEUE;
}

// Verifica se tá vazia
int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

// Enfileira peça
void enfileirar(Fila *fila, Peca peca) {
    if (filaCheia(fila)) {
        printf("Fila cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    fila->tras = (fila->tras + 1) % MAX_QUEUE;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
}

// Desenfileira peça
Peca desenfileirar(Fila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia! Não há peças para jogar.\n");
        Peca vazia = {'\0', -1};
        return vazia;
    }
    Peca peca_removida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_QUEUE;
    fila->tamanho--;
    return peca_removida;
}

// FExibe a fila
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila de peças\n");
    int i = fila->frente;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("[%c %d] ", fila->pecas[i].nome, fila->pecas[i].id);
        i = (i + 1) % MAX_QUEUE;
    }
    printf("\n");
}

// Corpo
int main() {
    srand(time(NULL));  // usa o rand para numeros aleatorios

    Fila fila;
    inicializarFila(&fila);

    int contador_id = 0;

    // Inicializa a fila
    for (int i = 0; i < 5; i++) {
        Peca nova = gerarPeca(&contador_id);
        enfileirar(&fila, nova);
    }
//eixbe opções
    int opcao;
    do {
        printf("\nEstado atual da fila:\n");
        exibirFila(&fila);

        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        //assim como na robotica o switch organiza portas, no nosso caso organiza as opcoes
        switch (opcao) {
            case 1: {
                Peca jogada = desenfileirar(&fila);
                if (jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }
                break;
            }
            case 2: {
                Peca nova = gerarPeca(&contador_id);
                enfileirar(&fila, nova);
                printf("Nova peça inserida: [%c %d]\n", nova.nome, nova.id);
                break;
            }
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
//retorna a 0, ou seja, finaliza o programa
    return 0;
}
