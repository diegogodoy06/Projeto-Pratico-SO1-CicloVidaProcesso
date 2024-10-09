#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;                     // Identificador do processo
    int tempo_execucao;         // Tempo total de execucao
    int tempo_restante;         // Tempo restante de CPU
    int bloqueado;              // Flag de bloqueio
} Processo;

// Funções de manipulação de processos
Processo* criaProcesso(int id, int tempo_execucao);
void executaProcesso(Processo* p, int tempo_cpu);
void bloqueiaProcesso(Processo* p);
int estaBloqueado(Processo* p);

// Cria um novo processo
Processo* criaProcesso(int id, int tempo_execucao) {
    Processo* p = (Processo*) malloc(sizeof(Processo));
    p->id = id;
    p->tempo_execucao = tempo_execucao;
    p->tempo_restante = tempo_execucao;
    p->bloqueado = 0;
    return p;
}

// Simula a execucao do processo por um tempo de CPU
void executaProcesso(Processo* p, int tempo_cpu) {
    if (p->tempo_restante > tempo_cpu) {
        p->tempo_restante -= tempo_cpu;
    } else {
        p->tempo_restante = 0;
    }
}

// Bloqueia o processo
void bloqueiaProcesso(Processo* p) {
    p->bloqueado = 1;
}

// Verifica se o processo esta bloqueado
int estaBloqueado(Processo* p) {
    return p->bloqueado;
}


#endif
