#include <stdio.h>

// Estrutura para armazenar um fator primo e seu expoente.
typedef struct {
    int fator;
    int expoente;
} FatorPrimo;

// Função auxiliar para calcular potência, removendo a dependência de math.h
long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

// Função para calcular a Razão de Eficiência
void calcularRazaoEficiencia(int N) {
    FatorPrimo fatores[22]; // N <= 10^5 não terá muitos fatores primos distintos
    int num_fatores_distintos = 0;
    int n_temp = N;

    // Passo 1: Fatoração Prima com Divisão por Tentativa
    // Trata o fator 2
    if (n_temp % 2 == 0) {
        fatores[num_fatores_distintos].fator = 2;
        fatores[num_fatores_distintos].expoente = 0;
        while (n_temp % 2 == 0) {
            fatores[num_fatores_distintos].expoente++;
            n_temp /= 2;
        }
        num_fatores_distintos++;
    }

    // Trata fatores ímpares
    // A condição i*i <= n_temp substitui i <= sqrt(n_temp) para evitar a biblioteca matemática.
    for (int i = 3; (long long)i * i <= n_temp; i += 2) {
        if (n_temp % i == 0) {
            fatores[num_fatores_distintos].fator = i;
            fatores[num_fatores_distintos].expoente = 0;
            while (n_temp % i == 0) {
                fatores[num_fatores_distintos].expoente++;
                n_temp /= i;
            }
            num_fatores_distintos++;
        }
    }

    // Se n_temp for um primo > 2
    if (n_temp > 2) {
        fatores[num_fatores_distintos].fator = n_temp;
        fatores[num_fatores_distintos].expoente = 1;
        num_fatores_distintos++;
    }

    // Saída dos fatores primos e seus expoentes
    printf("Fatores primos e seus expoentes:\n");
    for (int i = 0; i < num_fatores_distintos; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d^%d", fatores[i].fator, fatores[i].expoente);
    }
    printf("\n");

    // Passo 2: Cálculo de tau(N)
    long long tau = 1;
    for (int i = 0; i < num_fatores_distintos; i++) {
        tau *= (fatores[i].expoente + 1);
    }
    printf("Calculo de tau(N): %lld\n", tau);

    // Passo 3: Cálculo de sigma(N)
    long long sigma = 1;
    for (int i = 0; i < num_fatores_distintos; i++) {
        // Usa a função power() local em vez de pow() de math.h
        long long termo = (power(fatores[i].fator, fatores[i].expoente + 1) - 1) / (fatores[i].fator - 1);
        sigma *= termo;
    }
    printf("Calculo de sigma(N): %lld\n", sigma);

    // Passo 4: Cálculo da Razão de Eficiência
    double razao = 0.0;
    if (tau > 0) { // Evita divisão por zero para N=1
        razao = (double)(sigma - N - 1) / tau;
    }
    
    // Saída final formatada
    printf("Resultado final da Razao de Eficiencia:\n");
    printf("%.2f\n", razao);
}

int main() {
    printf("--- André Henrique Belarmino - 241025149 ---\n");
    printf("--- Giovanna Felipe - 241038998 ---\n\n");
    int N;
    scanf("%d", &N);
    calcularRazaoEficiencia(N);
    return 0;
}