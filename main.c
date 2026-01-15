//Desafio War Estruturado em C

// Nível novato: Construir uma base de dados de territórios utilizando uma estrutura de dados composta.

#include <stdio.h>
#include <string.h>

// Constantes Globais
#define MAX_TERRITORIOS 5 // Define a quantidade de territorios no array territorios.

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

// Definição de estrutura (struct)
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função principal (main)
int main () {
    struct Territorio territorios[MAX_TERRITORIOS]; // Definição do array territorios com a estrutura Territorio.

    printf("=================================================\n\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");

    // Laço de cadastro
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio --- %d\n", i+1);

        printf("Nome do Territorio: ");
        fgets(territorios[i].nome, 30, stdin); // Captura a entrada do dado do usuário

        printf("Cor do Exercito (ex: Verde, Azul...): ");
        fgets(territorios[i].cor, 10, stdin); // Captura a entrada do dado do usuário

        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Percorre a string salva até encontrar o '\n' e substitui ele por '\0'.

        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // Percorre a string salva até encontrar o '\n' e substitui ele por '\0'.

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas); // Captura a entrada do dado do usuário
        limparBufferEntrada();

        printf("\n"); //Pular uma linha
    }

    printf("Cadastro inicial realizado com sucesso!\n");

    printf("\n"); //Pular uma linha

    printf("=================================================\n");
    printf("            MAPA DO MUNDO - ESTADO ATUAL         \n");
    printf("=================================================\n");

    printf("\n"); //Pular uma linha

    // Laço de exibição
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("TERRITORIO %d:\n", i+1);
        printf(" - Nome: %s\n", territorios[i].nome);
        printf(" - Dominado por: Exercito %s\n", territorios[i].cor);
        printf(" - Tropas: %d\n", territorios[i].tropas);

        printf("\n"); //Pular uma linha
    }
    
    
}