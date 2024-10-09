#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX_PROCESSOS 100
#define MAX_FILHOS 10
#define MAX_TEMPO_EXECUCAO 100

typedef struct Processo {
    int id;
    int tempoExecucao;
    int filhos[MAX_FILHOS];
    int numFilhos;
    bool finalizado;
} Processo;

typedef struct Fila {
    Processo *processos[MAX_PROCESSOS];
    int frente;
    int tras;
} Fila;

Fila filaProntos;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
}

bool filaVazia(Fila *f) {
    return f->frente == f->tras;
}

bool filaCheia(Fila *f) {
    return (f->tras + 1) % MAX_PROCESSOS == f->frente;
}

void enfileirar(Fila *f, Processo *p) {
    if (!filaCheia(f)) {
        f->processos[f->tras] = p;
        f->tras = (f->tras + 1) % MAX_PROCESSOS;
    } else {
        printf("Erro: Fila cheia!\n");
    }
}

Processo *desenfileirar(Fila *f) {
    if (!filaVazia(f)) {
        Processo *p = f->processos[f->frente];
        f->frente = (f->frente + 1) % MAX_PROCESSOS;
        return p;
    }
    return NULL;
}

void criarProcesso(Fila *fila, int id, int tempo) {
    Processo *p = (Processo *)malloc(sizeof(Processo));
    p->id = id;
    p->tempoExecucao = tempo;
    p->numFilhos = 0;
    p->finalizado = false;
    enfileirar(fila, p);
}

void executarProcesso(Processo *p) {
    if (p->finalizado) {
        printf("Processo %d já foi finalizado.\n", p->id);
        return;
    }

    printf("Executando processo %d\n", p->id);
    p->tempoExecucao--;

    if (p->tempoExecucao <= 0) {
        p->finalizado = true;
        printf("Processo %d foi finalizado\n", p->id);
    } else {
        printf("Processo %d não terminou, voltando para a fila de prontos\n", p->id);
    }
}

void criarFilho(Processo *pai, int id, int tempo) {
    if (pai->numFilhos < MAX_FILHOS) {
        pai->filhos[pai->numFilhos] = id;
        pai->numFilhos++;
        printf("Processo %d criou o filho %d com tempo de execução %d\n", pai->id, id, tempo);
        criarProcesso(&filaProntos, id, tempo);
    } else {
        printf("Erro: Número máximo de filhos atingido para o processo %d\n", pai->id);
    }
}

void simular() {
    while (!filaVazia(&filaProntos)) {
        Processo *p = desenfileirar(&filaProntos);
        executarProcesso(p);

        // Cria filhos aleatórios (exemplo)
        if (!p->finalizado) {
            int idFilho = rand() % 1000; // Gera um ID aleatório para o filho
            int tempoFilho = rand() % MAX_TEMPO_EXECUCAO + 1; // Tempo de execução entre 1 e MAX_TEMPO_EXECUCAO
            criarFilho(p, idFilho, tempoFilho);
        }

        free(p);
    }
}

int main() {
    srand(time(NULL));
    inicializarFila(&filaProntos);

    // Criando processos iniciais
    for (int i = 0; i < 5; i++) {
        criarProcesso(&filaProntos, i, rand() % MAX_TEMPO_EXECUCAO + 1);
    }

    simular();

    return 0;
}
