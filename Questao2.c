#include <stdio.h>
#include <stdlib.h> // Para abs()

/*
 * Justificativa do Método (MDC):
 * O Algoritmo Euclidiano foi escolhido para calcular o Máximo Divisor Comum (MDC)
 * por sua alta eficiência (complexidade logarítmica), sendo superior a métodos
 * como a fatoração em primos para entradas maiores. Ele é o padrão da indústria
 * para este tipo de cálculo.
 */
long long mdc(long long a, long long b) {
    while (b!= 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*
 * Justificativa do Método (MMC):
 * O Mínimo Múltiplo Comum (MMC) é calculado usando a identidade matemática fundamental:
 * MMC(a, b) = (|a * b|) / MDC(a, b).
 * Esta abordagem é muito mais eficiente do que a simulação por força bruta (verificar
 * múltiplos um a um), especialmente para números grandes. A integração com a função mdc()
 * garante uma solução robusta e escalável.
 * A expressão é reordenada para (a / mdc(a, b)) * b para prevenir overflow de inteiros
 * que poderia ocorrer ao multiplicar 'a' e 'b' antes da divisão.
 */
long long mmc(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a / mdc(a, b)) * b;
}

// Lógica principal do programa
int main() {
    int n;
    printf("--- André Henrique Belarmino - 241025149 ---\n");
    printf("--- Giovanna Felipe - 241038998 ---\n\n");
    printf("--- Calculadora de Sincronizacao de Chaves Criptograficas ---\n");
    printf("Objetivo: Encontrar o primeiro ano (ate 50) em que todas as chaves estao ativas.\n\n");

    // Passo 1: Solicitar e validar o número de chaves
    printf("Passo 1: Insira o numero de chaves (N, entre 1 e 10): ");
    scanf("%d", &n);

    // Validação da entrada N
    if (n < 1 || n > 10) {
        printf("\nErro: O numero de chaves deve estar entre 1 e 10.\n");
        return 1; // Encerra com código de erro
    }

    int ciclos[n];

    // Passo 2: Solicitar e validar os ciclos de cada chave
    printf("Passo 2: Insira os %d ciclos (C, entre 2 e 20), separados por espaco: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ciclos[i]);
        // Validação da entrada Ci
        if (ciclos[i] < 2 || ciclos[i] > 20) {
            printf("\nErro: O ciclo de cada chave deve estar entre 2 e 20.\n");
            return 1; // Encerra com código de erro
        }
    }

    printf("\n--- Iniciando Calculo do MMC Iterativo ---\n");

    // Inicializa o MMC acumulado com 1 (elemento neutro para o cálculo de MMC)
    long long mmc_resultado = 1;
    printf("Valor inicial do MMC acumulado: %lld\n", mmc_resultado);

    // Passo 3: Calcular o MMC de todos os ciclos de forma iterativa
    for (int i = 0; i < n; i++) {
        printf("\n--------------------------------------------------\n");
        printf("Passo 3.%d: Processando o ciclo C%d = %d\n", i + 1, i + 1, ciclos[i]);

        long long mmc_anterior = mmc_resultado;
        int ciclo_atual = ciclos[i];

        // Cálculo intermediário do MDC
        long long mdc_calculado = mdc(mmc_anterior, ciclo_atual);
        printf("   - Calculo do MDC: mdc(%lld, %d) = %lld\n", mmc_anterior, ciclo_atual, mdc_calculado);

        // Cálculo intermediário do MMC
        mmc_resultado = mmc(mmc_anterior, ciclo_atual);
        printf("   - Calculo do MMC: mmc(%lld, %d) = (%lld / %lld) * %d = %lld\n",
               mmc_anterior, ciclo_atual, mmc_anterior, mdc_calculado, ciclo_atual, mmc_resultado);
        printf("   - MMC acumulado atualizado para: %lld\n", mmc_resultado);
    }
    printf("--------------------------------------------------\n");

    printf("\nPasso 4: Verificacao do resultado final\n");
    printf("   - O MMC final de todos os ciclos e: %lld\n", mmc_resultado);

    // Passo 5: Verificar a condição de limite do ano
    printf("   - Comparando com o limite de ano (50)...\n");
    if (mmc_resultado > 50 || mmc_resultado <= 0) {
        printf("\nResultado Final: impossivel\n");
        printf("Justificativa: O primeiro ano de sincronizacao (%lld) esta fora do limite permitido (1 a 50).\n", mmc_resultado);
    } else {
        printf("\nResultado Final: %lld\n", mmc_resultado);
        printf("Justificativa: O valor %lld e o primeiro ano em que todas as chaves podem ser usadas simultaneamente dentro do limite de 50 anos.\n", mmc_resultado);
    }

    return 0;
}