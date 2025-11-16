#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

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

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
    int prioridade; // só usado no nível Mestre
} Item;

    Item mochila[MAX];
    int total = 0;  // quantidade de itens cadastrados
    int opcao;

    bool estaOrdenadoPorNome = false;

    do {
        printf("\n=== MOCHILA ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome (sequencial)\n");
        printf("5 - Ordenar mochila\n");
        printf("6 - Buscar item por nome (binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar ENTER

        // -------------------------------------
        // ADICIONAR ITEM
        // -------------------------------------
        if (opcao == 1) {
            if (total >= MAX) {
                printf("Mochila cheia!\n");
            } else {
                printf("Nome: ");
                fgets(mochila[total].nome, 30, stdin);

                printf("Tipo: ");
                fgets(mochila[total].tipo, 30, stdin);

                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);

                printf("Prioridade (1 a 5): ");
                scanf("%d", &mochila[total].prioridade);
                getchar();

                total++;
                estaOrdenadoPorNome = false;

                printf("Item adicionado!\n");
            }
        }

        // -------------------------------------
        // REMOVER ITEM
        // -------------------------------------
        else if (opcao == 2) {
            char nomeBusca[30];
            int i, j;
            bool achou = false;

            printf("Nome do item para remover: ");
            fgets(nomeBusca, 30, stdin);

            for (i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                    achou = true;
                    for (j = i; j < total - 1; j++)
                        mochila[j] = mochila[j + 1];
                    total--;
                    printf("Item removido!\n");
                    break;
                }
            }

            if (!achou)
                printf("Item não encontrado.\n");
        }

        // -------------------------------------
        // LISTAR ITENS
        // -------------------------------------
        else if (opcao == 3) {
            printf("\n=== ITENS NA MOCHILA ===\n");
            if (total == 0) {
                printf("Nenhum item cadastrado.\n");
            } else {
                for (int i = 0; i < total; i++) {
                    printf("\nItem %d:\n", i + 1);
                    printf("Nome: %s", mochila[i].nome);
                    printf("Tipo: %s", mochila[i].tipo);
                    printf("Quantidade: %d\n", mochila[i].quantidade);
                    printf("Prioridade: %d\n", mochila[i].prioridade);
                }
            }
        }

        // -------------------------------------
        // BUSCA SEQUENCIAL
        // -------------------------------------
        else if (opcao == 4) {
            char nomeBusca[30];
            bool achou = false;

            printf("Nome para buscar: ");
            fgets(nomeBusca, 30, stdin);

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                    printf("\n=== Item encontrado ===\n");
                    printf("Nome: %s", mochila[i].nome);
                    printf("Tipo: %s", mochila[i].tipo);
                    printf("Quantidade: %d\n", mochila[i].quantidade);
                    printf("Prioridade: %d\n", mochila[i].prioridade);
                    achou = true;
                    break;
                }
            }

            if (!achou)
                printf("Item não encontrado.\n");
        }

        // -------------------------------------
        // ORDENAR MOCHILA (INSERTION SORT)
        // -------------------------------------
        else if (opcao == 5) {
            int criterio;
            int comparacoes = 0;

            printf("\nOrdenar por:\n");
            printf("1 - Nome\n");
            printf("2 - Tipo\n");
            printf("3 - Prioridade\n");
            printf("Escolha: ");
            scanf("%d", &criterio);
            getchar();

            for (int i = 1; i < total; i++) {
                Item aux = mochila[i];
                int j = i - 1;

                while (j >= 0) {
                    bool deveTrocar = false;

                    if (criterio == 1)
                        deveTrocar = strcmp(aux.nome, mochila[j].nome) < 0;
                    else if (criterio == 2)
                        deveTrocar = strcmp(aux.tipo, mochila[j].tipo) < 0;
                    else if (criterio == 3)
                        deveTrocar = aux.prioridade < mochila[j].prioridade;

                    comparacoes++;

                    if (deveTrocar)
                        mochila[j + 1] = mochila[j];
                    else
                        break;

                    j--;
                }

                mochila[j + 1] = aux;
            }

            if (criterio == 1)
                estaOrdenadoPorNome = true;
            else
                estaOrdenadoPorNome = false;

            printf("Mochila ordenada! Comparações feitas: %d\n", comparacoes);
        }

        // -------------------------------------
        // BUSCA BINÁRIA (SOMENTE SE ORDENADO POR NOME)
        // -------------------------------------
        else if (opcao == 6) {

            if (!estaOrdenadoPorNome) {
                printf("A mochila precisa estar ordenada por nome!\n");
            } else {
                char nomeBusca[30];
                printf("Nome para buscar (binária): ");
                fgets(nomeBusca, 30, stdin);

                int inicio = 0, fim = total - 1;
                bool achou = false;

                while (inicio <= fim) {
                    int meio = (inicio + fim) / 2;
                    int r = strcmp(nomeBusca, mochila[meio].nome);

                    if (r == 0) {
                        printf("\n=== Item encontrado (binária) ===\n");
                        printf("Nome: %s", mochila[meio].nome);
                        printf("Tipo: %s", mochila[meio].tipo);
                        printf("Quantidade: %d\n", mochila[meio].quantidade);
                        printf("Prioridade: %d\n", mochila[meio].prioridade);
                        achou = true;
                        break;
                    } else if (r < 0) {
                        fim = meio - 1;
                    } else {
                        inicio = meio + 1;
                    }
                }

                if (!achou)
                    printf("Item não encontrado.\n");
            }
        }

    } while (opcao != 0);

    printf("\nSaindo da ilha... Até mais, sobrevivente!\n");

    return 0;
}
