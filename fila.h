#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da fila
typedef struct NoFila {
    void* dado;                // Ponteiro genérico para armazenar qualquer tipo de dado
    struct NoFila* prox;       // Ponteiro para o próximo nó
} NoFila;

// Estrutura da fila
typedef struct {
    NoFila* frente;            // Primeiro elemento da fila
    NoFila* tras;              // Último elemento da fila
} Fila;

// Funções da fila
Fila* criaFila();
void enfileira(Fila* f, void* dado);
void* desenfileira(Fila* f);
int filaVazia(Fila* f);
void destroiFila(Fila* f);

// Implementação das funções

// Cria uma fila vazia
Fila* criaFila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->frente = NULL;
    f->tras = NULL;
    return f;
}

// Adiciona um elemento à fila
void enfileira(Fila* f, void* dado) {
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));  // Aloca memória para um novo nó
    novo->dado = dado;                                 // Atribui o dado ao nó
    novo->prox = NULL;                                 // O novo nó será o último, então seu próximo é NULL

    if (f->tras != NULL) {                             // Se a fila não estiver vazia
        f->tras->prox = novo;                          // O próximo do último nó aponta para o novo
    }
    f->tras = novo;                                    // Atualiza o último nó para ser o novo nó

    if (f->frente == NULL) {                           // Se a fila estava vazia
        f->frente = novo;                              // O novo nó é agora também o primeiro
    }
}

// Remove e retorna o primeiro elemento da fila
void* desenfileira(Fila* f) {
    if (f->frente == NULL) {                           // Se a fila estiver vazia
        return NULL;                                   // Retorna NULL
    }

    NoFila* temp = f->frente;                          // Armazena o nó que será removido
    void* dado = temp->dado;                           // Obtém o dado do nó
    f->frente = f->frente->prox;                       // Avança o ponteiro para o próximo nó

    if (f->frente == NULL) {                           // Se a fila ficou vazia
        f->tras = NULL;                                // Também atualiza o último para NULL
    }

    free(temp);                                        // Libera a memória do nó removido
    return dado;                                       // Retorna o dado removido
}

// Verifica se a fila está vazia
int filaVazia(Fila* f) {
    return (f->frente == NULL);                        // Retorna 1 se a fila estiver vazia, 0 caso contrário
}

// Destrói a fila e libera a memória
void destroiFila(Fila* f) {
    while (!filaVazia(f)) {                            // Enquanto a fila não estiver vazia
        desenfileira(f);                               // Remove todos os nós
    }
    free(f);                                           // Libera a memória da estrutura da fila
}

#endif // FILA_H
