# Projeto Prático SO1 - Ciclo de Vida de um Processo

## Descrição
Este projeto tem como objetivo simular o ciclo de vida dos processos em um sistema operacional, conforme exigido para a disciplina de Sistemas Operacionais (SO1) do 1º Bimestre. A implementação é feita na linguagem de programação C, utilizando estruturas de dados apropriadas para gerenciar o estado dos processos.

## Um documento Word foi elaborado, contendo:
  - Descrição da implementação do projeto.
  - Explicação das estruturas de dados utilizadas e suas finalidades.

## Estruturas Utilizadas
O projeto faz uso das seguintes estruturas de dados:
- **Fila**: Para gerenciar os processos prontos e os processos em espera.
- **Processo (PCB)**: Estrutura que contém informações sobre cada processo, como seu identificador e tempo de execução.

## Requisitos
- **Compilador**: O projeto deve ser compilado com um compilador C (por exemplo, GCC).
- **Sistema Operacional**: O projeto foi desenvolvido e testado no Windows 11.

## Instruções de Compilação e Execução
Para compilar e executar o projeto, siga as instruções abaixo:

1. **Clone o repositório**:
```bash
  git clone https://github.com/diegogodoy06/Projeto-Pratico-SO1-CicloVidaProcesso.git
```
2. **Compile o código**:
  ```bash
    gcc main.c fila.c processo.c -o cicloVidaProcesso
```
3. **Execute o programa**:
  ```bash
  ./cicloVidaProcesso
