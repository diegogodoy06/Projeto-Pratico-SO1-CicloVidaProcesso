#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "processo.h"

#define TEMPO_MAX_CPU 10

int main() {
    Fila* filaPronto = criaFila();
    Fila* filaEspera = criaFila();

    // Adicionar processos de teste
    for (int i = 0; i < 5; i++) {
        Processo* p = criaProcesso(i, rand() % 50 + 10);
        enfileira(filaPronto, p);
    }

    // Simulacao do ciclo de vida dos processos
    while (!filaVazia(filaPronto)) {
        Processo* p = (Processo*) desenfileira(filaPronto);
        printf("Executando processo %d\n", p->id);

        // Simula a execucao do processo
        executaProcesso(p, TEMPO_MAX_CPU);

        if (p->tempo_restante > 0) {
            printf("Processo %d não finalizado, tempo restante: %d\n", p->id, p->tempo_restante);
            enfileira(filaPronto, p);
        } else {
            printf("Processo %d finalizado\n", p->id);
            free(p);
        }
    }

    // Limpeza
    destroiFila(filaPronto);
    destroiFila(filaEspera);

    return 0;
}
