#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila.h"
#include "processo.h"

#define TEMPO_MAX_CPU 10
#define CHANCE_BLOQUEIO 30  // Percentual de chance de bloquear um processo
#define CHANCE_FILHO 20     // Percentual de chance de criar um processo filho

// Estatísticas globais
int totalProcessosFinalizados = 0;
int totalTempoBloqueio = 0;
int processosBloqueados = 0;
int processosExecucaoParaPronto = 0;

// Função para criar um processo filho
void criaProcessoFilho(Processo* pai, Fila* filaPronto) {
    static int idFilho = 100;  // IDs de filhos começam em 100
    int tempoExecucaoFilho = rand() % 50 + 10;  // Tempo de execução aleatório
    Processo* filho = (Processo*)malloc(sizeof(Processo));
    
    filho->id = idFilho++;
    filho->tempo_execucao = tempoExecucaoFilho;
    filho->tempo_restante = tempoExecucaoFilho;
    filho->bloqueado = 0;
    filho->tempo_bloqueio = 0;
    filho->filhos_criados = 0;
    filho->filhos_restantes = 0;
    filho->tempo_total_espera = 0;
    filho->tempo_esperando_filhos = 0;
    filho->pai = pai;  // Atribuindo o pai

    pai->filhos_criados++;
    pai->filhos_restantes++;
    
    printf("Processo %d criou o filho %d com tempo de execução %d\n", pai->id, filho->id, filho->tempo_execucao);
    enfileira(filaPronto, filho);
}

// Função para finalizar um filho
void finalizaFilho(Processo* filho, Fila* filaPronto) {
    Processo* pai = filho->pai;  // Obtém o processo pai do filho
    if (pai != NULL) {
        pai->filhos_restantes--;
        printf("Processo %d finalizou um filho. Filhos restantes: %d\n", pai->id, pai->filhos_restantes);
        
        // Se o pai não tem mais filhos, ele pode ser re-adicionado à fila de prontos
        if (pai->filhos_restantes == 0) {
            printf("Processo %d não tem mais filhos e pode ser finalizado\n", pai->id);
            // Re-adiciona o pai à fila de prontos, apenas se não estiver em execução
            enfileira(filaPronto, pai);
        }
    } else {
        printf("Erro: Processo filho %d não tem pai válido!\n", filho->id);
    }
    free(filho);  // Libera a memória do processo filho
}

void simulaProcesso(Processo* p, Fila* filaPronto, Fila* filaEspera) {
    printf("Executando processo %d\n", p->id);

    // Atualiza o tempo total de espera
    p->tempo_total_espera += (p->tempo_execucao - p->tempo_restante);

    int tempoUsado = p->tempo_restante > TEMPO_MAX_CPU ? TEMPO_MAX_CPU : p->tempo_restante;
    executaProcesso(p, tempoUsado);

    // Se o processo tem filhos e está aguardando, ele não pode finalizar até que todos os filhos terminem
    if (p->filhos_restantes > 0) {
        printf("Processo %d está aguardando seus filhos\n", p->id);
        p->tempo_esperando_filhos += tempoUsado;
        enfileira(filaEspera, p);  // Bloqueia o processo enquanto espera pelos filhos
        return;
    }

    // Simula o bloqueio do processo
    if (rand() % 100 < CHANCE_BLOQUEIO) {
        printf("Processo %d foi bloqueado\n", p->id);
        bloqueiaProcesso(p);
        p->tempo_bloqueio += tempoUsado;
        processosBloqueados++;
        totalTempoBloqueio += tempoUsado;
        enfileira(filaEspera, p);
    } else if (p->tempo_restante > 0) {
        // Se o processo não terminou, volta para a fila de prontos
        printf("Processo %d não terminou, voltando para a fila de prontos\n", p->id);
        processosExecucaoParaPronto++;
        enfileira(filaPronto, p);
    } else {
        // Se o processo terminou
        printf("Processo %d foi finalizado\n", p->id);
        totalProcessosFinalizados++;
        finalizaFilho(p, filaPronto);  // Passa filaPronto como argumento
    }
}

void relatorioFinal(Fila* filaPronto, Fila* filaEspera) {
    printf("\n--- Relatorio Final ---\n");
    printf("Total de processos finalizados: %d\n", totalProcessosFinalizados);
    printf("Total de processos bloqueados: %d\n", processosBloqueados);
    if (processosBloqueados > 0) {
        printf("Tempo medio de bloqueio: %d unidades de tempo\n", totalTempoBloqueio / processosBloqueados);
    }
    printf("Processos que alternaram entre Execucao e Pronto: %d\n", processosExecucaoParaPronto);
    
    // Relatando tempo total de execução e espera por filhos
    printf("\n--- Tempo Total de Execucao e Bloqueio por Filhos ---\n");
    while (!filaVazia(filaPronto)) {
        Processo* p = desenfileira(filaPronto);
        printf("Processo %d: Tempo total de execucao: %d, Tempo esperando filhos: %d\n", 
                p->id, (p->tempo_execucao - p->tempo_restante) + p->tempo_total_espera, p->tempo_esperando_filhos);
        free(p);
    }
}

int main() {
    srand(time(NULL));

    Fila* filaPronto = criaFila();
    Fila* filaEspera = criaFila();

    // Adicionar processos iniciais
    for (int i = 0; i < 5; i++) {
        Processo* p = (Processo*)malloc(sizeof(Processo));
        p->id = i;
        p->tempo_execucao = rand() % 50 + 10;
        p->tempo_restante = p->tempo_execucao;
        p->bloqueado = 0;
        p->tempo_bloqueio = 0;
        p->filhos_criados = 0;
        p->filhos_restantes = 0;
        p->tempo_total_espera = 0;
        p->tempo_esperando_filhos = 0;
        p->pai = NULL;  // Inicialmente não tem pai
        
        enfileira(filaPronto, p);
    }

    // Simulação do ciclo de vida dos processos
    while (!filaVazia(filaPronto) || !filaVazia(filaEspera)) {
        if (!filaVazia(filaPronto)) {
            Processo* p = (Processo*) desenfileira(filaPronto);
            simulaProcesso(p, filaPronto, filaEspera);
            
            if (rand() % 100 < CHANCE_FILHO) {
                criaProcessoFilho(p, filaPronto);
            }
        }
        
        if (!filaVazia(filaEspera)) {
            Processo* p = (Processo*) desenfileira(filaEspera);
            printf("Processo %d foi desbloqueado\n", p->id);
            desbloqueiaProcesso(p);
            enfileira(filaPronto, p);
        }
    }

    relatorioFinal(filaPronto, filaEspera);

    destroiFila(filaPronto);
    destroiFila(filaEspera);

    return 0;
}
