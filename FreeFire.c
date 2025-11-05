#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//define 10 como máximo de itens
#define MAX_ITENS 10

typedef struct{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void cadastrarItem (Item mochila[], int *quantidadeItens);
void removerItem (Item mochila[], int *quantidadeItens);
void listarItens (Item mochila[], int quantidadeItens);
void buscarItem (Item mochila[], int quantidadeItens);


//Função para cadastrar Itens
void cadastrarItem(Item mochila[], int *quantidadeItens){
    if (*quantidadeItens >= MAX_ITENS){
        printf("Mochila lotada! Não é possível adicionar mais itens.");
        return;
    }
    Item novoItem;
    
    printf("\n Cadastro \n");

    //Cadastro do nome
    printf("Nome:");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    //cadastro de tipo
    printf("Tipo de Item:");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    //Cadastro de quantidade
    printf("Quantidade de Itens:");
    scanf("%d", &novoItem.quantidade);
    getchar();

    mochila[*quantidadeItens] = novoItem;
    (*quantidadeItens)++;

    printf("\nItem adicionado com sucesso!\n");

}

// Função para remover item
void removerItem(Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30]; //busca pelo nome do item
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = -1;

    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    //caso o item for encontrao é feita sua remoção
    if (encontrado != -1) {
        for (int j = encontrado; j < *quantidadeItens - 1; j++) {
            mochila[j] = mochila[j + 1];
        }
        (*quantidadeItens)--;
        printf("\nItem removido com sucesso!\n");
    } else {
        printf("\nItem nao encontrado!\n");
    }
}

//Função para listar os itens cadastrados
void listarItens(Item mochila[], int quantidadeItens){
    if (quantidadeItens == 0){
        printf("\nMochila vazia\n");
        return;
    }

    printf("\n Itens presentes na mochila:\n");
    for (int i = 0; i < quantidadeItens; i++){
        printf("\nItem %d \n", i+1);
        printf("Nome: %s \n", mochila[i].nome);
        printf ("Tipo: %s \n", mochila[i].tipo);
        printf("Quantidade: %d \n", mochila[i].quantidade);

    }
}

//Função para a busca de itens
void buscarItem(Item mochila[], int quantidadeItens){
    if (quantidadeItens == 0){
        printf("\n Mochila vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("\n Digite o nome do item que deseja buscar:");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < quantidadeItens; i++){
        if (strcmp(mochila[i].nome, nomeBusca) == 0){
            printf("\nItem encontrado!\n");
            printf("Nome: %s \n", mochila[i].nome);
            printf("Tipo: %s \n", mochila[i].tipo);
            printf("Quantidade: %d \n", mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado!");
}

int main() {
    Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;
    
    do{
        printf("\n--- Inventário ---\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar item\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");

        printf("Escolha uma opção\n");

        scanf("%d", &opcao);

        getchar();
        //switch de opções de escolhas
        switch (opcao){
            case 1:
                cadastrarItem(mochila, &quantidadeItens);
                break;
            case 2:
                removerItem(mochila, &quantidadeItens);
                break;
            case 3:
                listarItens(mochila, quantidadeItens);
                break;
            case 4:
                buscarItem(mochila, quantidadeItens);
                break;
            case 5:
                printf("Sistema encerrado\n");
                break;
            default:
                printf("Não temos essa opção! Tente outra vez.\n");

        }
    }while (opcao != 0);

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
