#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//define 20 como máximo de componentes
#define MAX_COMP 20


typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


int comparacoes = 0;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarComponentes(Componente lista[], int n) {
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%02d] Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

//Função de Bubble Sort

void bubbleSortNome(Componente lista[], int n) {
    comparacoes = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

 void insertionSortTipo(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            lista[j + 1] = lista[j];
            j--;
            comparacoes++;
        }
        comparacoes++;
        lista[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
}

//Busca Binária

int buscaBinariaPorNome(Componente lista[], int n, char nomeBusca[]) {
    int ini = 0, fim = n - 1, meio;
    int comparacoesBusca = 0;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        comparacoesBusca++;

        int cmp = strcmp(lista[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("\nComponente encontrado na posicao %d!\n", meio + 1);
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                   lista[meio].nome, lista[meio].tipo, lista[meio].prioridade);
            printf("Comparacoes na busca: %d\n", comparacoesBusca);
            return meio;
        } else if (cmp < 0) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nComponente nao encontrado!\n");
    printf("Comparacoes na busca: %d\n", comparacoesBusca);
    return -1;
}

void medirTempo(void (*algoritmo)(Componente[], int), Componente lista[], int n, char tipoOrdenacao[]) {
    Componente copia[MAX_COMP];
    memcpy(copia, lista, sizeof(Componente) * n);

    clock_t inicio = clock();
    algoritmo(copia, n);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n-- Resultado da Ordenacao (%s) --\n", tipoOrdenacao);
    mostrarComponentes(copia, n);
    printf("Comparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
}


int main() {
    Componente componentes[MAX_COMP];
    int qtd = 0;
    int opcao;
    char nomeBusca[30];

    printf("-- Montagem da Torre de Fuga --\n");

    do {
        printf("\nDigite o nome do componente (ou 'fim' para encerrar): ");
        fgets(componentes[qtd].nome, 30, stdin);
        componentes[qtd].nome[strcspn(componentes[qtd].nome, "\n")] = '\0';
        if (strcmp(componentes[qtd].nome, "fim") == 0) break;

        printf("Tipo do componente: ");
        fgets(componentes[qtd].tipo, 20, stdin);
        componentes[qtd].tipo[strcspn(componentes[qtd].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[qtd].prioridade);
        limparBuffer();

        qtd++;
    } while (qtd < MAX_COMP);

    if (qtd == 0) {
        printf("\nNenhum componente foi cadastrado.\n");
        return 0;
    }

    do {
        printf("\n-- MENU --\n");
        printf("1 - Ordenar por Nome (Bubble Sort)\n");
        printf("2 - Ordenar por Tipo (Insertion Sort)\n");
        printf("3 - Ordenar por Prioridade (Selection Sort)\n");
        printf("4 - Buscar componente-chave (após ordenação por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha sua estrategia: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                medirTempo(bubbleSortNome, componentes, qtd, "Bubble Sort (Nome)");
                break;
            case 2:
                medirTempo(insertionSortTipo, componentes, qtd, "Insertion Sort (Tipo)");
                break;
            case 3:
                medirTempo(selectionSortPrioridade, componentes, qtd, "Selection Sort (Prioridade)");
                break;
            case 4:
                printf("\nDigite o nome do componente-chave: ");
                fgets(nomeBusca, 30, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                bubbleSortNome(componentes, qtd); // garantindo a ordenação
                buscaBinariaPorNome(componentes, qtd, nomeBusca);
                break;
            case 0:
                printf("\nEncerrando a simulacao...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    printf("\nTorre de Fuga montada com sucesso. Missao completa!\n");
    return 0;
}
    


// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
