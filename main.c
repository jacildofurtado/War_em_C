//Desafio War Estruturado em C

// Nível novato: Construir uma base de dados de territórios utilizando uma estrutura de dados composta.

// Nível aventureiro: Primeiro, você receberá a missão de implementar a funcionalidade de ataque entre territórios. Com base nos territórios já cadastrados, o sistema deverá permitir que um jogador selecione um território como atacante, e outro como defensor. O ataque será resolvido por meio de uma simulação com dados aleatórios (como rolagem de dados), e o resultado alterará o controle e as tropas do território atacado. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Definição de estrutura (struct)
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Alocação de memória
Territorio* alocarmapa(int qtd) {
    Territorio* mapa = calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) { // Verifica se a alocação de memória deu certo.
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    return mapa;
}

// Função para cadastro de territórios
void cadastrarTerritorios(Territorio* mapa, int qtd) {

    // Laço de cadastro
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastrando Territorio --- %d\n", i+1);

        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, 30, stdin); // Captura a entrada do dado do usuário

        printf("Cor do Exercito (ex: Verde, Azul...): ");
        fgets(mapa[i].cor, 10, stdin); // Captura a entrada do dado do usuário

        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Percorre a string salva até encontrar o '\n' e substitui ele por '\0'.

        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0'; // Percorre a string salva até encontrar o '\n' e substitui ele por '\0'.

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas); // Captura a entrada do dado do usuário
        limparBufferEntrada();

    }

    printf("\nCadastro inicial realizado com sucesso!\n\n");


}

// Função para exibição
void exibirMapa (Territorio* mapa, int qtd) {
    printf("=================================================\n");
    printf("            MAPA DO MUNDO - ESTADO ATUAL         \n");
    printf("=================================================\n\n");

    // Laço de exibição
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);

    }
}

// Função para ataque
void atacar(Territorio* atacante, Territorio* defensor){
    int dadoAtacante = rand() % 6 + 1; // Rola um dado de 1 a 6
    int dadoDefensor = rand() % 6 + 1;

    printf("--- RESULTADO DA BATALHA ---\n\n");

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    // Verificação do vencedor
    if (dadoAtacante > dadoDefensor) {
        printf("\nVITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n\n");

        defensor->tropas --; // Reduz em 1 a tropa do defensor

        // Verifica se o defensor ainda possui tropas no seu territorio.
        if (defensor->tropas == 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", defensor->nome, atacante->cor);

            strcpy(defensor->cor, atacante->cor); // copia a cor do atacante para o defensor caso ele fique sem tropas (conquistado).

            // Transfere 1 tropa do territorio atacante para o conquistado.
            defensor->tropas = 1; // Define as tropas do territorio conquistado em 1.
            atacante->tropas --; // Diminui 1 tropa do territorio vitorioso.
        }

    } else {
        printf("ATAQUE FRACASOU!\n\n");
    }
}

// Função para liberação de memória
void liberarMemoria(Territorio * mapa) {
    free(mapa);
}


// Função principal (main)
int main () {
    srand(time(NULL)); // Gera números aleatórios

    printf("=================================================\n\n");
    printf("       WAR ESTRUTURADO - CADASTRO INICIAL        \n\n");
    printf("=================================================\n\n");

    int qtdTerritorios = 0;

    printf("Digite o numero de territorios que deseja cadastrar: \n");
    scanf("%d", &qtdTerritorios);
    limparBufferEntrada();

    Territorio* mapa = alocarmapa(qtdTerritorios);
    cadastrarTerritorios(mapa, qtdTerritorios);

    int atacante, defensor;

    int continuar = 1;
    
    // Loop de ataque.
    while (continuar) {
        exibirMapa(mapa, qtdTerritorios);

        printf("\n--- FASE DE ATAQUE ---\n\n");

        // Escolha do atacante e do defensor.
        printf("Escolha o territorio atacante (1 a %d, ou 0 pra sair): ", qtdTerritorios);
        scanf("%d", &atacante);
        if (atacante == 0) {
            printf("Saindo...\n");
            break;
        }

        printf("Escolha o territorio defensor (1 a %d, ou 0 pra sair): ", qtdTerritorios);
        scanf("%d", &defensor);
        if (defensor == 0) {
            printf("Saindo...\n");
            break;
        }
        limparBufferEntrada();

        // Ajuste de índice.
        atacante--;
        defensor--;

        // Validações.
        if (atacante < 0 || atacante >= qtdTerritorios || defensor < 0 || defensor >= qtdTerritorios) {
            printf("\nOpção invalida!\n");
            continue;
        }

        if (atacante == defensor){
            printf("Um territorrio nao pode atacar a si mesmo!\n\n");
            continue;
        }

        if (strcmp(mapa[atacante].cor, mapa[defensor].cor) == 0) {
            printf("Não é permitido atacar um territorio da mesma cor\n\n");
            continue;
        }

        atacar(&mapa[atacante], &mapa[defensor]);

    }
    
    liberarMemoria(mapa);

    return 0;
}