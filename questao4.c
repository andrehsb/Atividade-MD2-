//Andre Henrique de Souza Belarmino 241025149
//Giovanna Felipe Guimarães 241038998

#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

// Função para calcular o máximo divisor comum (MDC) com exibição dos passos
int mdcComPassos(int a, int b) {
    int resto;
    while (b != 0) { // linha 10
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto; // linha 14
    }
    return a;
}

// funcao pra calcular o inverso modular usando o algoritmo estendido de Euclides
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    mdcComPassos(a, m); // linha 23

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0; // linha 36
    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n", A, B, x1);
    return x1;
}

// funcao pra calcular a exponenciacao modular (a^x mod n1)
int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp % 2 != 0) // linha 45
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}

int main() {
    printf("--- André Henrique Belarmino - 241025149 ---\n");
    printf("--- Giovanna Felipe - 241038998 ---\n\n");
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(G, Zn); // linha 72
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicacao modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf("Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1); // linha 78
    printf("Valor final da congruencia: %d\n", resultado);

    return 0;
}

//-------------------------------------------------------------------------------------------


//Insira H: 7
//Insira G: 3
//Insira Zn: 11
//Insira x: 10
//Insira n1: 13

//SAIDA:

//Algoritmo de Euclides: 3 mod 11 = 3
//Algoritmo de Euclides: 11 mod 3 = 2
//Algoritmo de Euclides: 3 mod 2 = 1
//Algoritmo de Euclides: 2 mod 1 = 0

//Substituindo, temos que o inverso de 3 em 11 é 4.
//Fazendo a multiplicacao modular: 7 * 4 mod 11 = 6
//Sendo 4 o inverso de 3.
//Valor final da congruencia: 4


//----------------------------------------------------------------------------------------------------


//2)

// (V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
// (F) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
// (V) A operação (H * inverso) % Zn representa a divisão modular de H por G.
// (F) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.
// (F) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.
// (V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
// (F) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.