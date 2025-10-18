#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef long long ll;

// --- AUXILIARES ---
ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// Algoritmo estendido de Euclides
ll extended_euclid(ll a, ll b, ll *x, ll *y) {
    if (a == 0) { 
        *x = 0; *y = 1; return b; 
    }
    ll x1 = 1, y1 = 0, x2 = 0, y2 = 1;
    ll r1 = a, r2 = b;
    while (r2 != 0) {
        ll q = r1 / r2;
        ll r = r1 - q * r2; r1 = r2; r2 = r;
        ll nx = x1 - q * x2; x1 = x2; x2 = nx;
        ll ny = y1 - q * y2; y1 = y2; y2 = ny;
    }
    *x = x1; *y = y1;
    return r1;
}

int isPrime(ll n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0) return 0;
    return 1;
}

// --- NOVA FUNÇÃO: Verifica se é possível aplicar o Teorema de Fermat ---
int podeAplicarFermat(ll M, ll n) {
    if (!isPrime(n)) {
        printf("    Nao é possível aplicar Fermat: n = %lld nao é primo.\n", n);
        return 0;
    }
    ll g = gcd(M, n);
    if (g != 1) {
        printf("    Nao é possível aplicar Fermat: mdc(M, n) = %lld ≠ 1.\n", g);
        return 0;
    }
    printf("    É possível aplicar o Pequeno Teorema de Fermat.\n");
    return 1;
}

// --- Pollard Rho ---
ll f_with_c(ll x, ll c, ll N) {
    __int128 t = (__int128)x * x + c;
    return (ll)(t % N);
}

ll pollard_rho_factorization(ll N) {
    if (N % 2 == 0) return 2;
    printf("\n--- Fatorando N = %lld ---\n", N);
    ll c = 1;
    while (1) {
        ll x = 2, y = 2, p = 1;
        ll iter = 0;
        printf("Tentativa com c = %lld\n", c);
        printf("Iter.\t| x_i\t\t| x_2i\t\t| |x_2i-x_i|\t| mdc\n");
        printf("------------------------------------------------------------------\n");
        while (p == 1) {
            iter++;
            x = f_with_c(x, c, N);
            y = f_with_c(f_with_c(y, c, N), c, N);
            ll diff = x - y; if (diff < 0) diff = -diff;
            p = gcd(diff, N);
            printf("%lld\t| %-10lld\t| %-10lld\t| %-12lld\t| %lld\n", iter, x, y, diff, p);
            if (p == N) {
                printf("Encontrou p == N nesta tentativa (falha com c = %lld). Reiniciando com novo c.\n", c);
                break;
            }
        }
        printf("------------------------------------------------------------------\n");
        if (p > 1 && p < N) {
            printf("Fator nao trivial de %lld encontrado: %lld\n", N, p);
            return p;
        }
        c++;
        if (c > 1000) {
            fprintf(stderr, "Pollard falhou (muitos c). Saindo.\n");
            exit(EXIT_FAILURE);
        }
    }
}

// --- CODIFICACAO / DECODIFICACAO ---
ll char_to_code(char c) {
    if (c == ' ') return 0;
    if (isalpha((unsigned char)c)) return (toupper((unsigned char)c) - 'A' + 11);
    return -1;
}

char code_to_char(ll code) {
    if (code == 0) return ' ';
    if (code >= 11 && code <= 36) return (char)('A' + (code - 11));
    return '?';
}

// exponenciacao modular
ll modular_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    printf("   -> Exponenciacao modular: base=%lld, exp=%lld, mod=%lld\n", base, exp, mod);
    while (exp > 0) {
        if (exp & 1) {
            __int128 tmp = (__int128)res * base;
            res = (ll)(tmp % mod);
            printf("      exp impar -> res = (res * base) %% mod = %lld\n", res);
        }
        exp >>= 1;
        if (exp) {
            __int128 tmp2 = (__int128)base * base;
            base = (ll)(tmp2 % mod);
            printf("      base quadrado -> base = base*base %% mod = %lld\n", base);
        }
    }
    printf("   -> Resultado final: %lld\n", res);
    return res;
}

int main() {
    printf("--- André Henrique Belarmino - 241025149 ---\n");
    printf("--- Giovanna Felipe - 241038998 ---\n\n");

    ll N1 = 0, N2 = 0;
    while (N1 < 100 || N1 > 9999) {
        printf("Digite o primeiro numero composto (N1) [100 a 9999]: ");
        if (scanf("%lld", &N1) != 1) { fprintf(stderr, "Entrada invalida\n"); return 1; }
        if (N1 < 100 || N1 > 9999) printf("Erro: O numero deve ter 3 ou 4 digitos.\n");
    }
    while (N2 < 100 || N2 > 9999 || N2 == N1) {
        printf("Digite o segundo numero composto (N2), distinto de N1 [100 a 9999]: ");
        if (scanf("%lld", &N2) != 1) { fprintf(stderr, "Entrada invalida\n"); return 1; }
        if (N2 < 100 || N2 > 9999) printf("Erro: O numero deve ter 3 ou 4 digitos.\n");
        if (N2 == N1) printf("Erro: N2 deve ser diferente de N1.\n");
    }

    ll f1 = pollard_rho_factorization(N1);
    ll other1 = N1 / f1;
    if (f1 > other1) { ll tmp = f1; f1 = other1; other1 = tmp; }

    ll f2 = pollard_rho_factorization(N2);
    ll other2 = N2 / f2;
    if (f2 > other2) { ll tmp = f2; f2 = other2; other2 = tmp; }

    ll p = f1;
    ll q = (f1 != f2) ? f2 : other2;

    if (p == q) {
        fprintf(stderr, "Erro: nao foi possivel obter primos distintos.\n");
        exit(EXIT_FAILURE);
    }
    if (!isPrime(p) || !isPrime(q)) {
        fprintf(stderr, "Erro: um dos fatores nao e primo.\n");
        exit(EXIT_FAILURE);
    }

    printf("\nPrimos encontrados: p = %lld, q = %lld\n\n", p, q);

    ll n = p * q;
    ll z = (p - 1) * (q - 1);
    printf("n = %lld\nphi(n) = %lld\n", n, z);

    ll e;
    for (e = 2; e < n; e++)
        if (gcd(e, z) == 1) break;

    ll x, y;
    extended_euclid(e, z, &x, &y);
    ll d = (x % z + z) % z;

    printf("Chave Publica: (n, e) = (%lld, %lld)\n", n, e);
    printf("Chave Privada: (n, d) = (%lld, %lld)\n", n, d);

    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    char message[512];
    printf("\nDigite a mensagem a ser criptografada:\n");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    ll encrypted_blocks[512];
    int valid = 0;
    int len = (int)strlen(message);
    printf("\n--- INICIANDO CRIPTOGRAFIA ---\n");

    for (int i = 0; i < len; i++) {
        ll M = char_to_code(message[i]);
        if (M == -1) continue;

        printf("\nCriptografando '%c' -> M = %02lld\n", message[i], M);
        ll reduced_e = e;

        // Usa a nova função para checar Fermat
        if (podeAplicarFermat(M, n)) {
            reduced_e = e % (n - 1);
        } else if (gcd(M, n) == 1) {
            printf("   Aplicando Teorema de Euler: reduzir e mod phi(n)\n");
            reduced_e = e % z;
        } else {
            printf("   Aplicando Divisao Euclidiana: nao reduz expoente\n");
        }

        ll C = modular_pow(M, reduced_e, n);
        encrypted_blocks[valid++] = C;
        printf("   Bloco cifrado C = %lld\n", C);
    }

    printf("\n--- INICIANDO DESCRIPTOGRAFIA ---\n");
    char decrypted[512];
    int di = 0;
    for (int i = 0; i < valid; i++) {
        ll C = encrypted_blocks[i];
        printf("\nDescriptografando C = %lld\n", C);
        ll reduced_d = d;

        if (podeAplicarFermat(C, n)) {
            reduced_d = d % (n - 1);
        } else if (gcd(C, n) == 1) {
            printf("   Aplicando Teorema de Euler: reduzir d mod phi(n)\n");
            reduced_d = d % z;
        } else {
            printf("   Aplicando Divisao Euclidiana: nao reduz expoente\n");
        }

        ll M = modular_pow(C, reduced_d, n);
        char cc = code_to_char(M);
        decrypted[di++] = cc;
        printf("   Bloco decifrado = %02lld -> '%c'\n", M, cc);
    }
    decrypted[di] = '\0';

    printf("\n----------------------------------------\n");
    printf("Mensagem original : %s\n", message);
    printf("Mensagem decifrada: %s\n", decrypted);
    printf("----------------------------------------\n");

    return 0;
}
