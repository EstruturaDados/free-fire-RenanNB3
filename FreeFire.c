#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//define 10 como máximo de itens
#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// FUNÇÕES DO VETOR

void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("\n--- Inserir Item (Vetor) ---\n");
    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochila[*qtd] = novo;
    (*qtd)++;
    printf("Item adicionado!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int i, pos = -1;
    for (i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        for (i = pos; i < *qtd - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*qtd)--;
        printf("Item removido!\n");
    } else {
        printf("Item nao encontrado!\n");
    }
}

void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n--- Itens na mochila (Vetor) ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenarVetor(Item mochila[], int qtd) {
    Item temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome (Bubble Sort).\n");
}

int buscarBinariaVetor(Item mochila[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// FUNÇÕES DA LISTA ENCADEADA


void inserirItemLista(No **inicio) {
    No *novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de alocacao!\n");
        return;
    }

    printf("\n--- Inserir Item (Lista) ---\n");
    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item adicionado!\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido!\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    printf("\n--- Itens na mochila (Lista Encadeada) ---\n");
    No *atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista(No *inicio, char nome[]) {
    comparacoesSequencial = 0;
    No *atual = inicio;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return;
        }
        atual = atual->proximo;
    }
    printf("\nItem nao encontrado!\n");
}

int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;
    No *mochilaLista = NULL;

    int opcaoEstrutura, opcaoOperacao;
    char nomeBusca[30];

    do {
        printf("\n--SELECIONE A ESTRUTURA DE DADOS --\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcaoEstrutura);
        limparBuffer();

        if (opcaoEstrutura == 1) {
            do {
                printf("\n--- Mochila com Vetor ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial\n");
                printf("5 - Ordenar e buscar binaria\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcaoOperacao);
                limparBuffer();

                switch (opcaoOperacao) {
                    case 1:
                        inserirItemVetor(mochilaVetor, &qtdVetor);
                        break;
                    case 2:
                        removerItemVetor(mochilaVetor, &qtdVetor);
                        break;
                    case 3:
                        listarItensVetor(mochilaVetor, qtdVetor);
                        break;
                    case 4:
                        printf("Nome do item a buscar: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        int pos;
                        pos = buscarSequencialVetor(mochilaVetor, qtdVetor, nomeBusca);
                        if (pos != -1)
                            printf("Item encontrado! Quantidade: %d\n", mochilaVetor[pos].quantidade);
                        else
                            printf("Item nao encontrado!\n");
                        printf("Comparacoes (sequencial): %d\n", comparacoesSequencial);
                        break;
                    case 5:
                        ordenarVetor(mochilaVetor, qtdVetor);
                        printf("Nome do item para busca binaria: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        pos = buscarBinariaVetor(mochilaVetor, qtdVetor, nomeBusca);
                        if (pos != -1)
                            printf("Item encontrado! Quantidade: %d\n", mochilaVetor[pos].quantidade);
                        else
                            printf("Item nao encontrado!\n");
                        printf("Comparacoes (binaria): %d\n", comparacoesBinaria);
                        break;
                }

            } while (opcaoOperacao != 0);
        }

        else if (opcaoEstrutura == 2) {
            do {
                printf("\n--- Mochila com Lista Encadeada ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar item (sequencial)\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcaoOperacao);
                limparBuffer();

                switch (opcaoOperacao) {
                    case 1:
                        inserirItemLista(&mochilaLista);
                        break;
                    case 2:
                        removerItemLista(&mochilaLista);
                        break;
                    case 3:
                        listarItensLista(mochilaLista);
                        break;
                    case 4:
                        printf("Nome do item a buscar: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        buscarSequencialLista(mochilaLista, nomeBusca);
                        printf("Comparacoes (sequencial): %d\n", comparacoesSequencial);
                        break;
                }

            } while (opcaoOperacao != 0);
        }

    } while (opcaoEstrutura != 0);

    printf("\nSistema encerrado.\n");
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
