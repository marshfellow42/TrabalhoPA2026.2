#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Item {
    char nome[100];
    char descricao[100];
    char tipo[100];
};

struct Jogador {
    char nome[100];
    int pontos_de_vida;
    struct Item itens[3];
    int rodadas_bloqueadas;
};

struct Casa {
    char simbolo[100];
    char descricao[100];
    char tipo[100];
};

struct Partida {
    struct Jogador jogadores[2];
    int casas;
};

struct RegistroRanking {
    char nome[100];
};

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void inicio(struct Partida *partida, struct Casa *casas, int qtd_casas_especiais) {
    (*partida).casas = 30;
    char tabuleiro[(*partida).casas][10]; // 30 casas, cada uma com até 9 caracteres + '\0'

    for (int i = 0; i < (*partida).casas; i++) {
        int dado = rand() % 20 + 1;
        if (dado < qtd_casas_especiais) {
            tabuleiro[i][0] = casas[dado].simbolo[0];
            tabuleiro[i][1] = '\0';
        } else {
            strcpy(tabuleiro[i], "O");
        }
    }

    strcpy(tabuleiro[0], "[P1, P2]");

    for (int i = 0; i < (*partida).casas; i++) {
        printf("%s ", tabuleiro[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); 

    struct Partida partida;
    // Inicializar a struct para evitar que o lixo na memória cause bugs na hora de ler os símbolos
    struct Casa casas[6] = {0};

    FILE *arq_casas;
    
    arq_casas = fopen("casas.txt", "r");
    
    if (arq_casas == NULL) {
        printf("O arquivo casas.txt não foi aberto.");
        return 1;
    };

    char linha[256];
    int casa_atual = 0;
    while (fgets(linha, sizeof linha, arq_casas)) {
        if (linha[0] == '\n') {
            casa_atual++;
            if (casa_atual >= 6) break;
            continue;
        }

        if (casas[casa_atual].simbolo[0] == '\0') {
            strcpy(casas[casa_atual].simbolo, linha);
        } else if (casas[casa_atual].descricao[0] == '\0') {
            strcpy(casas[casa_atual].descricao, linha);
        } else if (casas[casa_atual].tipo[0] == '\0') {
            strcpy(casas[casa_atual].tipo, linha);
        }
    }

    fclose(arq_casas);

    printf("1) Começar\n"
            "2) Continuar Partida Salva\n"
            "3) Ver Ranking\n"
            "4) Instruções\n"
            "0) Sair\n");

    int escolha = 0;
    
    scanf("%d", &escolha);
    
    switch (escolha) {
        case 1:
            limpar_tela();
            inicio(&partida, casas, 6);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            printf("%s", casas[1].simbolo);
        case 0:
            return 0;
            break;
        default:
            printf("Esta opção não existe.");
    }
}