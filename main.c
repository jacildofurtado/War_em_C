//Desafio War Estruturado em C

// Nível novato: Construir uma base de dados de territórios utilizando uma estrutura de dados composta.

// Nível aventureiro: Primeiro, você receberá a missão de implementar a funcionalidade de ataque entre territórios. Com base nos territórios já cadastrados, o sistema deverá permitir que um jogador selecione um território como atacante, e outro como defensor. O ataque será resolvido por meio de uma simulação com dados aleatórios (como rolagem de dados), e o resultado alterará o controle e as tropas do território atacado. 

// Nível Mestre: Você receberá a missão de implementar a funcionalidade de missões estratégicas individuais para cada jogador, que deverá receber, no início do jogo, uma missão sorteada de forma automática entre diversas descrições pré-definidas, armazenadas em um vetor de strings. Essa missão será consultada durante o jogo para verificar se a condição de vitória foi atingida. A nova camada de estratégia exige organização modular do código, uso de ponteiros, passagem de parâmetros por valor e referência e gerenciamento adequado da memória.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes globais
#define TOTAL_MISSOES 2

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

// Função para o sorteio da missão do jogador
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int sorteioMissao = rand() % totalMissoes;

    // Aloca memória exatamente do tamanho da missão sorteada.
    *destino = malloc(strlen(missoes[sorteioMissao]) + 1);
    if (*destino == NULL) {
        printf("\nErro ao alocar memória para missão.\n");
        exit(1);
    }

    strcpy(*destino, missoes[sorteioMissao]);
}

// Função para ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1; // Rola um dado de 1 a 6
    int dadoDefensor = rand() % 6 + 1;

    printf("--- RESULTADO DA BATALHA ---\n\n");

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    // Verificação do vencedor
    if (dadoAtacante > dadoDefensor) {
        printf("\nVITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n\n");

        defensor->tropas --; // Reduz em 1 a tropa do defensor.

        // Verifica se o defensor ainda possui tropas no seu territorio.
        if (defensor->tropas == 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", defensor->nome, atacante->cor);

            strcpy(defensor->cor, atacante->cor); // copia a cor do atacante para o defensor caso ele fique sem tropas (conquistado).

            // Transfere metade das tropas do territorio atacante para o conquistado.
            defensor->tropas = atacante->tropas / 2;
        }

    } else {
        printf("ATAQUE FRACASOU! O atacante perdeu 1 tropa.\n\n");
        atacante->tropas --; // Reduz em 1 a tropa do atacante.
    }
}

// Função para verificar se a missão foi cumprida.
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Missão 1: Conquistar todos os territórios
    if (strcmp(missao, "Conquiste todos os territorios") == 0) {
        for(int i = 1; i < tamanho; i++) {
            if(strcmp(mapa[i].cor, mapa[0].cor) != 0) {
                return 0; // Ainda existe território inimigo.
            }
        }
        return 1; // Todos são da mesma cor.
    }

    // Missão 2: Conquistar ao menos 1 território
    if (strcmp(missao, "Conquiste ao menos 1 territorio") == 0){
        int contador = 0;

        for(int i = 0; i < tamanho; i++) { // Esse loop percorre o mapa e verifica se tem mais de um território com a mesma cor do jogador.
            if(strcmp(mapa[i].cor, mapa[0].cor) == 0) {
                contador++;
            }
        }
        return contador >= 2; // Se tiver 2 ou mais territórios com a mesma cor retorna 1 (missão cumprida).
    }


}

// Função para liberação de memória
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}


// Função principal (main)
int main () {
    srand(time(NULL)); // Gera números aleatórios

    // Vetor de missões.
    char* missoes[] = {"Conquiste todos os territorios", "Conquiste ao menos 1 territorio"};

    printf("=================================================\n\n");
    printf("       WAR ESTRUTURADO - CADASTRO INICIAL        \n\n");
    printf("=================================================\n\n");

    int qtdTerritorios = 0;

    printf("Digite o numero de territorios que deseja cadastrar: \n");
    scanf("%d", &qtdTerritorios);
    limparBufferEntrada();

    Territorio* mapa = alocarmapa(qtdTerritorios);

    cadastrarTerritorios(mapa, qtdTerritorios);

    char* missaoJogador;

    atribuirMissao(&missaoJogador, missoes, TOTAL_MISSOES);

    printf("\nSua missão (Exercito %s ) é: \n%s\n", mapa[0].cor, missaoJogador);

    int atacante, defensor;

    int acao;


    do {
        exibirMapa(mapa, qtdTerritorios);

        printf("\n--- Menu de acoes ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &acao);
        limparBufferEntrada();

        switch (acao)
        {
        case 1:
            printf("\n--- FASE DE ATAQUE ---\n\n");

            // Escolha do atacante e do defensor.
            printf("Escolha o territorio atacante (1 a %d, ou 0 para voltar pro menu): ", qtdTerritorios);
            scanf("%d", &atacante);
            if (atacante == 0) {
                printf("Voltando pro menu...\n");
                break;
            }

            printf("Escolha o territorio defensor (1 a %d, ou 0 para voltar pro menu): ", qtdTerritorios);
            scanf("%d", &defensor);
            if (defensor == 0) {
                printf("Voltando pro menu...\n");
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
            break;
        
        case 2:
            // Se o resultado do retorno da função verificarMissao for 1 a missão foi concluida.
            if (verificarMissao(missaoJogador, mapa, qtdTerritorios)) {
                printf("\n🎉 PARABÉNS! Você cumpriu sua missão!\n");
                printf("Missão: %s\n", missaoJogador);
                acao = 0; // encerra o jogo
            } else {
                printf("\nVoce ainda nao cumpriu sua missao\n");
            }
            break;

        case 0:
            printf("\nSaindo...");
            break;
        
        default:
            break;
        }
    } while (acao != 0);
    
    liberarMemoria(mapa, missaoJogador);

    return 0;
}