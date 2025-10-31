#include <stdio.h>
#define TAM 8

void limparTela() {
    // Função opcional (funciona no Windows)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirTabuleiro(int tabuleiro[TAM][TAM], int revelar) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 3 && !revelar)
                printf("0 ");
            else
                printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void posicionarNavios(int tabuleiro[TAM][TAM], int jogador) {
    int linha, coluna;
    printf("=== Jogador %d: Posicione seus 3 navios (1 célula cada) ===\n", jogador);
    for (int n = 1; n <= 3; n++) {
        do {
            printf("Navio %d - Digite linha e coluna (0 a %d): ", n, TAM - 1);
            scanf("%d %d", &linha, &coluna);
            if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM || tabuleiro[linha][coluna] == 3)
                printf("Posição inválida! Tente novamente.\n");
        } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM || tabuleiro[linha][coluna] == 3);
        tabuleiro[linha][coluna] = 3;
    }
    limparTela();
}

int todosAfundados(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == 3)
                return 0;
    return 1;
}

void jogarTurno(int atacante, int alvo[TAM][TAM]) {
    int linha, coluna;
    printf("=== Jogador %d, é sua vez de atacar! ===\n", atacante);
    exibirTabuleiro(alvo, 0);

    do {
        printf("Digite coordenadas de ataque (linha e coluna de 0 a %d): ", TAM - 1);
        scanf("%d %d", &linha, &coluna);
        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM)
            printf("Coordenadas inválidas! Tente novamente.\n");
    } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM);

    if (alvo[linha][coluna] == 3) {
        printf("🎯 ACERTOU UM NAVIO!\n");
        alvo[linha][coluna] = 1;
    } else if (alvo[linha][coluna] == 1 || alvo[linha][coluna] == 2) {
        printf("⚠️ Já atirou aqui! Perdeu a vez.\n");
    } else {
        printf("🌊 ÁGUA!\n");
        alvo[linha][coluna] = 2;
    }
}

int main() {
    int jogador1[TAM][TAM] = {0};
    int jogador2[TAM][TAM] = {0};
    int vencedor = 0;
    int turno = 1;

    printf("=== BATALHA NAVAL - MODO 2 JOGADORES ===\n\n");

    // Posicionamento
    posicionarNavios(jogador1, 1);
    posicionarNavios(jogador2, 2);

    // Batalha
    while (!vencedor) {
        if (turno == 1) {
            jogarTurno(1, jogador2);
            if (todosAfundados(jogador2)) {
                vencedor = 1;
                break;
            }
            turno = 2;
        } else {
            jogarTurno(2, jogador1);
            if (todosAfundados(jogador1)) {
                vencedor = 2;
                break;
            }
            turno = 1;
        }
        printf("\nPressione ENTER para continuar o jogo...\n");
        getchar(); getchar();
        limparTela();
    }

    printf("🏆 PARABÉNS, JOGADOR %d! Você venceu a batalha naval! 🏆\n", vencedor);
    printf("\n=== Fim do Jogo ===\n");

    return 0;
}
