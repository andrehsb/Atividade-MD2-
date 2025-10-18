#include <stdio.h>
#include <stdlib.h> // Para a função abs()
#include <string.h> // Para strlen() e outras funções de string
#include <ctype.h>  // Para toupper()

// Usar 'long long' para todas as operações numéricas para garantir segurança contra overflow.
typedef long long int ll;

// --- FUNÇÕES AUXILIARES GERAIS ---
ll gcd(ll a, ll b) { if (b == 0) return a; return gcd(b, a % b); }
void extended_euclidean_algorithm(ll a, ll b, ll *x, ll *y) { if (a == 0) { *x = 0; *y = 1; return; } ll x1, y1; extended_euclidean_algorithm(b % a, a, &x1, &y1); *x = y1 - (b / a) * x1; *y = x1; }
int isPrime(ll n) { if (n <= 1) return 0; for (ll i = 2; i * i <= n; i++) { if (n % i == 0) return 0; } return 1; }

// --- FUNÇÕES ESPECÍFICAS DE CADA ETAPA ---
ll g(ll x, ll N) { return ((__int128)x * x + 1) % N; }
ll pollard_rho_factorization(ll N) { ll tortoise = 2, hare = 2, p = 1, iter = 0; printf("\n--- Fatorando N = %lld ---\n", N); printf("Iter.\t| x_i\t\t| x_2i\t\t| |x_2i - x_i|\t| mdc\n"); printf("------------------------------------------------------------------\n"); while (p == 1) { iter++; tortoise = g(tortoise, N); hare = g(g(hare, N), N); ll diff = llabs(hare - tortoise); p = gcd(diff, N); printf("%lld\t| %-10lld\t| %-10lld\t| %-12lld\t| %lld\n", iter, tortoise, hare, diff, p); if (p == N) { printf("O fator encontrado e o proprio N. O metodo pode ter falhado.\n"); break; } } printf("------------------------------------------------------------------\n"); printf("Fator nao trivial de %lld encontrado: %lld\n", N, p); return p; }
ll char_to_code(char c) { if (c == ' ') return 0; if (isalpha(c)) return (toupper(c) - 'A' + 11); return -1; }
char code_to_char(ll code) { if (code == 0) return ' '; if (code >= 11 && code <= 36) return (char)(code - 11 + 'A'); return '?'; }
ll modular_pow(ll base, ll exp, ll mod) { ll res = 1; printf("   -> Iniciando exponenciacao modular: base=%lld, exp=%lld, mod=%lld\n", base, exp, mod); base %= mod; while (exp > 0) { if (exp % 2 == 1) { ll new_res = ((__int128)res * base) % mod; printf("      exp=%lld (impar), res = (%lld * %lld) %% %lld = %lld\n", exp, res, base, mod, new_res); res = new_res; } if (exp > 1) { ll new_base = ((__int128)base * base) % mod; printf("      exp=%lld->%lld, base = (%lld * %lld) %% %lld = %lld\n", exp, exp/2, base, base, mod, new_base); base = new_base; } exp /= 2; } printf("   -> Resultado final: %lld\n", res); return res; }

// --- FUNÇÃO PRINCIPAL COM TODAS AS ETAPAS INTEGRADAS ---
int main() {
    printf("--- André Henrique Belarmino - 241025149 ---\n");
    printf("--- Giovanna Felipe - 241038998 ---\n\n");
    
    ll N1 = 0, N2 = 0, p, q, n, z, e, d;

    // ETAPA 1: FATORAÇÃO
    printf("====================================================\n");
    printf("Parte 1: Fatoracao Rho de Pollard para encontrar p e q\n");
    printf("====================================================\n");
    while (N1 < 100 || N1 > 9999) { printf("Digite o primeiro numero composto (N1) [100 a 9999]: "); scanf("%lld", &N1); if (N1 < 100 || N1 > 9999) printf("Erro: O numero deve ter 3 ou 4 digitos.\n"); }
    while (N2 < 100 || N2 > 9999 || N2 == N1) { printf("Digite o segundo numero composto (N2), distinto de N1 [100 a 9999]: "); scanf("%lld", &N2); if (N2 < 100 || N2 > 9999) printf("Erro: O numero deve ter 3 ou 4 digitos.\n"); if (N2 == N1) printf("Erro: N2 deve ser diferente de N1.\n"); }
    p = pollard_rho_factorization(N1);
    q = pollard_rho_factorization(N2);

    // ETAPA 2: GERAÇÃO DAS CHAVES
    printf("\n\n====================================================\n");
    printf("Parte 2: Construcao do Par de Chaves RSA\n");
    printf("====================================================\n");
    printf("Primos encontrados: p = %lld, q = %lld\n\n", p, q);
    n = p * q; z = (p - 1) * (q - 1);
    printf("Passo 1: Modulo n = %lld\n", n); printf("Passo 2: Totiente z = %lld\n", z);
    for (e = 2; e < z; e++) { if (gcd(e, z) == 1) break; }
    printf("Passo 3: Expoente publico E = %lld\n", e);
    ll d_temp, y_temp; extended_euclidean_algorithm(e, z, &d_temp, &y_temp);
    d = (d_temp % z + z) % z;
    printf("Passo 4: Expoente privado D = %lld\n\n", d);
    printf("Chave Publica: (n, E) = (%lld, %lld)\n", n, e); printf("Chave Privada: (n, D) = (%lld, %lld)\n", n, d);

    // ETAPA 3: CRIPTOGRAFIA E DESCRIPTOGRAFIA
    printf("\n\n====================================================\n");
    printf("Parte 3: Criptografia e Descriptografia\n");
    printf("====================================================\n");
    
    char message[100];
    printf("Digite a mensagem a ser criptografada (A-Z, espaco): ");
    int c; while ((c = getchar()) != '\n' && c != EOF);
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    int len = strlen(message);
    ll encrypted_blocks[len];
    char decrypted_message[len + 1];
    int valid_chars = 0;
    
    // --- CODIFICAÇÃO (CRIPTOgrafia) ---
    printf("\n--- INICIANDO CRIPTOGRAFIA ---\n");
    for (int i = 0; i < len; i++) {
        ll M = char_to_code(message[i]);
        if (M == -1) continue;
        printf("\nCriptografando caractere '%c' (bloco M = %lld):\n", message[i], M);
        ll reduced_e = e;
        if (isPrime(n)) { printf("   Condicao: n=%lld e primo. Aplicando Pequeno Teorema de Fermat.\n", n); reduced_e = e % (n - 1); }
        else if (gcd(M, n) == 1) { printf("   Condicao: mdc(M,n)=mdc(%lld,%lld)=1. Aplicando Teorema de Euler.\n", M, n); if (z > 0) reduced_e = e % z; }
        else { printf("   Condicao: mdc(M,n)=mdc(%lld,%lld)!=1. Aplicando Teorema da Divisao Euclidiana.\n", M, n); }
        if (reduced_e != e) printf("   Expoente E=%lld foi reduzido para %lld.\n", e, reduced_e);
        
        encrypted_blocks[valid_chars] = modular_pow(M, reduced_e, n);
        printf("   Bloco Cifrado C: %lld\n", encrypted_blocks[valid_chars]);
        valid_chars++;
    }

    // --- DECODIFICAÇÃO (DESCRIPTOGRAFIA) ---
    printf("\n\n--- INICIANDO DESCRIPTOGRAFIA ---\n");
    for (int i = 0; i < valid_chars; i++) {
        ll C = encrypted_blocks[i];
        printf("\nDescriptografando bloco C = %lld:\n", C);

        ll reduced_d = d;
        if (isPrime(n)) { printf("   Condicao: n=%lld e primo. Aplicando Pequeno Teorema de Fermat.\n", n); reduced_d = d % (n - 1); }
        else if (gcd(C, n) == 1) { printf("   Condicao: mdc(C,n)=mdc(%lld,%lld)=1. Aplicando Teorema de Euler.\n", C, n); if (z > 0) reduced_d = d % z; }
        else { printf("   Condicao: mdc(C,n)=mdc(%lld,%lld)!=1. Aplicando Teorema da Divisao Euclidiana.\n", C, n); }
        if (reduced_d != d) printf("   Expoente D=%lld foi reduzido para %lld.\n", d, reduced_d);
        
        ll M_decrypted = modular_pow(C, reduced_d, n);
        decrypted_message[i] = code_to_char(M_decrypted);
        printf("   Bloco M decifrado: %lld ('%c')\n", M_decrypted, decrypted_message[i]);
    }
    decrypted_message[valid_chars] = '\0';

    printf("\n\n----------------------------------------\n");
    printf("Mensagem Descriptografada Final: %s\n", decrypted_message);
    printf("----------------------------------------\n");

    return 0;
}