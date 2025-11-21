#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ESTRUTURA
typedef struct {
    char nome;  
    int id;     
} Peca;

#define MAX_QUEUE 10  // tam max(no video falou 5 porem, 10 já vai ficar para os proximos niveis)
#define MAX_PILHA 3   // capacidade máxima da pilha de reserva

//fAbstrai a Fila
typedef struct {
    Peca pecas[MAX_QUEUE];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Abstrai a Pilha
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

// Protótipos das funções
Peca gerarPeca(int *contador_id);
void inicializarFila(Fila *fila);
int filaCheia(Fila *fila);
int filaVazia(Fila *fila);
void enfileirar(Fila *fila, Peca peca);
Peca desenfileirar(Fila *fila);
void exibirFila(Fila *fila);
void inicializarPilha(Pilha *pilha);
int pilhaCheia(Pilha *pilha);
int pilhaVazia(Pilha *pilha);
void push(Pilha *pilha, Peca peca);
Peca pop(Pilha *pilha);
void exibirPilha(Pilha *pilha);
void trocarFrenteComTopo(Fila *fila, Pilha *pilha);
void trocarTresPrimeirosComTresPilha(Fila *fila, Pilha *pilha);

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
    printf("Fila de peças\t");
    int i = fila->frente;
    for (int count = 0; count < fila->tamanho; count++) {
        printf("[%c %d] ", fila->pecas[i].nome, fila->pecas[i].id);
        i = (i + 1) % MAX_QUEUE;
    }
    printf("\n");
}

// Inicializa a Pilha
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

// Verifica se pilha está cheia
int pilhaCheia(Pilha *pilha) {
    return pilha->topo == MAX_PILHA - 1;
}

// Verifica se pilha está vazia
int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

// Empilha peça
void push(Pilha *pilha, Peca peca) {
    if (pilhaCheia(pilha)) {
        printf("Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
}

// Desempilha peça
Peca pop(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Não há peças reservadas para usar.\n");
        Peca vazia = {'\0', -1};
        return vazia;
    }
    Peca peca_removida = pilha->pecas[pilha->topo];
    pilha->topo--;
    return peca_removida;
}

// Exibe a pilha
void exibirPilha(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha de reserva\t(Topo -> Base): Vazia\n");
        return;
    }
    printf("Pilha de reserva\t(Topo -> Base): ");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
    }
    printf("\n");
}

// Corpo
int main() {
    srand(time(NULL));  // usa o rand para numeros aleatorios

    Fila fila;
    inicializarFila(&fila);

    Pilha pilha;
    inicializarPilha(&pilha);

    int contador_id = 0;

    // Inicializa a fila com 5 peças
    for (int i = 0; i < 5; i++) {
        Peca nova = gerarPeca(&contador_id);
        enfileirar(&fila, nova);
    }
//opções
    int opcao;
    do {
        printf("\nEstado atual:\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpções disponíveis:\n");
        printf("Código\tAção\n");
        printf("1\tJogar peça da frente da fila\n");
        printf("2\tEnviar peça da fila para a pilha de reserva\n");
        printf("3\tUsar peça da pilha de reserva\n");
        printf("4\tTrocar peça da frente da fila com o topo da pilha\n");
        printf("5\tTrocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0\tSair\n");
        printf("Opção escolhida: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {  // Jogar peça
                Peca jogada = desenfileirar(&fila);
                if (jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                    // Gera nova peça e enfileira
                    Peca nova = gerarPeca(&contador_id);
                    enfileirar(&fila, nova);
                }
                break;
            }
            case 2: {  // Reservar peça
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    Peca reservada = desenfileirar(&fila);
                    push(&pilha, reservada);
                    printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                    // Gera nova peça e enfileira
                    Peca nova = gerarPeca(&contador_id);
                    enfileirar(&fila, nova);
                } else if (filaVazia(&fila)) {
                    printf("Fila vazia! Não há peças para reservar.\n");
                } else {
                    printf("Pilha cheia! Não é possível reservar mais peças.\n");
                }
                break;
            }
            case 3: {  // Usar peça reservada
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                }
                break;
            }
            case 4: {  // Trocar peça da frente da fila com o topo da pilha
                trocarFrenteComTopo(&fila, &pilha);
                break;
            }
            case 5: {  // Trocar os 3 primeiros da fila com as 3 peças da pilha
                trocarTresPrimeirosComTresPilha(&fila, &pilha);
                break;
            }
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
