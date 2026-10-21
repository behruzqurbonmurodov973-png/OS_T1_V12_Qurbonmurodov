#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 100

/* Xavfsiz butun son o'qish: harf, chegaradan tashqari qiymatni rad etadi */
int oqi_int(const char *taklif, int min, int max, int *natija)
{
    char buf[64];
    char *oxiri;
    long v;

    printf("%s", taklif);
    if (fgets(buf, sizeof buf, stdin) == NULL) {
        printf("Xato: kiritish o'qilmadi.\n");
        return 0;
    }
    errno = 0;
    v = strtol(buf, &oxiri, 10);
    if (oxiri == buf) {
        printf("Xato: son o'rniga boshqa belgi kiritildi.\n");
        return 0;
    }
    while (*oxiri == ' ' || *oxiri == '\t')
        oxiri++;
    if (*oxiri != '\n' && *oxiri != '\0') {
        printf("Xato: son oxirida ortiqcha belgilar bor.\n");
        return 0;
    }
    if (errno == ERANGE || v < min || v > max) {
        printf("Xato: qiymat %d..%d oralig'ida bo'lishi kerak.\n", min, max);
        return 0;
    }
    *natija = (int)v;
    return 1;
}

/* 2-masala: natijalar pointerlar orqali qaytadi */
void statistika(const int *a, int n, double *ort, int *mx, int *mn)
{
    const int *p;
    long summa = 0;

    *mx = *a;
    *mn = *a;
    for (p = a; p < a + n; p++) {
        summa += *p;
        if (*p > *mx) *mx = *p;
        if (*p < *mn) *mn = *p;
    }
    *ort = (double)summa / n;
}

/* O'rtachadan yuqori talabalar soni */
int yuqori_soni(const int *a, int n, double ort)
{
    int soni = 0;
    for (const int *p = a; p < a + n; p++)
        if (*p > ort)
            soni++;
    return soni;
}

int main(void)
{
    int baholar[MAX];
    int n, mx, mn;
    double ort;

    if (!oqi_int("Talabalar soni (1..100): ", 1, MAX, &n))
        return 1;

    for (int i = 0; i < n; i++) {
        char taklif[40];
        snprintf(taklif, sizeof taklif, "%d-talaba bahosi (0..100): ", i + 1);
        if (!oqi_int(taklif, 0, 100, &baholar[i]))
            return 1;
    }

    statistika(baholar, n, &ort, &mx, &mn);

    printf("\nO'rtacha baho : %.2f\n", ort);
    printf("Eng yuqori    : %d\n", mx);
    printf("Eng past      : %d\n", mn);
    printf("O'rtachadan yuqori talabalar soni: %d\n", yuqori_soni(baholar, n, ort));

    /* %p namunasi: hisobotda izohlang */
    printf("\nMassiv boshi (baholar)   : %p\n", (void *)baholar);
    printf("O'rtacha (ort) manzili   : %p\n", (void *)&ort);
    printf("Elementlar orasidagi masofa: %zu bayt (sizeof(int))\n", sizeof(int));
    return 0;
}