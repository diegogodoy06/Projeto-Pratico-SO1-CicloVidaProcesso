#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da fila
typedef struct NoFila {
    void* dado;                // Ponteiro genérico para armazenar qualquer tipo de dado
    struct NoFila* prox;
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
    NoFila* novo = (NoFila*) malloc(sizeof(NoFila));
    novo->dado = dado;
    novo->prox = NULL;

    if (f->tras != NULL) {
        f->tras->prox = novo;
    }
    f->tras = novo;

    if (f->frente == NULL) {
        f->frente = novo;
    }
}

// Remove e retorna o primeiro elemento da fila
void* desenfileira(Fila* f) {
    if (f->frente == NULL) {
        return NULL;
    }

    NoFila* temp = f->frente;
    void* dado = temp->dado;
    f->frente = f->frente->prox;

    if (f->frente == NULL) {
        f->tras = NULL;
    }

    free(temp);
    return dado;
}

// Verifica se a fila está vazia
int filaVazia(Fila* f) {
    return (f->frente == NULL);
}

// Destrói a fila e libera a memória
void destroiFila(Fila* f) {
    while (!filaVazia(f)) {
        desenfileira(f);
    }
    free(f);
}

#endif // FILA_H
