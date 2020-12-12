#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    if (a > b)return a;
    else return b;
}


void prebmbc(char* str, int strlen, int* bmBc) {
    int i;

    for (i = 0; i < 256; ++i)
        bmBc[i] = strlen;
    for (i = 0; i < strlen - 1; ++i)
        bmBc[str[i]] = strlen - 1 - i;
}


void suffixes(char* str, int strlen, int* suff) {
    int f, g, i;

    suff[strlen - 1] = strlen;
    g = strlen - 1;
    for (i = strlen - 2; i >= 0; --i) {
        if (i > g && suff[i + strlen - 1 - f] < i - g)
            suff[i] = suff[i + strlen - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && str[g] == str[g + strlen - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void prebmgs(char* str, int strlen, int bmGs[]) {
    int i, j;
    int* suff = (int*)malloc(strlen * sizeof(int));

    suffixes(str, strlen, suff);

    for (i = 0; i < strlen; ++i)
        bmGs[i] = strlen;
    j = 0;
    for (i = strlen - 1; i >= 0; --i)
        if (suff[i] == i + 1)
            for (; j < strlen - 1 - i; ++j)
                if (bmGs[j] == strlen)
                    bmGs[j] = strlen - 1 - i;
    for (i = 0; i <= strlen - 2; ++i)
        bmGs[strlen - 1 - suff[i]] = strlen - 1 - i;
    free(suff);
}


int boyermur(char* substr, int substrlen, char* str, int strlen) {
    int i, j, bmBc[256];

    int* bmGs = (int*)malloc(substrlen * sizeof(int));
    prebmgs(substr, substrlen, bmGs);
    i = 0;
    prebmbc(substr, substrlen, bmBc);
    i = 0;
    j = 0;
    int o = 0;
    while (j <= strlen - substrlen) {
        for (i = substrlen - 1; i >= 0 && substr[i] == str[i + j]; --i);
        if (i < 0) {
            o++;
            j += bmGs[0];
        }
        else {
            
            j += max(bmGs[i], bmBc[str[i + j]] - substrlen + 1 + i);
        }
    }
    return o;
}

int strlen(char* str) {
    int i = 0;
    for (i = 0; str[i] != '\n'; i++);
    return i;
}
void upheaval(char* str, char* temp) {
    int total = strlen(str);
    for (int i = total - 1, j = 0; i >= 0; i-- && j++) {
        temp[j] = str[i];
    }
}
int main() {
    printf("Imput string: ");
    char x = 0;
    int v = 0, n = 5;

    char* str = (char*)malloc(n * sizeof(char));
    do {
        scanf("%c", &x);
        str[v] = x;
        v++;
        if (v == n - 2) {
            n *= 3;
            realloc(str, n * sizeof(char));
        }
    } while (x != '\n');
    x = 0;
    v = 0;
    printf("Imput substring: ");
    char* substr = (char*)malloc(n * sizeof(char));
    do {
        scanf("%c", &x);
        substr[v] = x;
        v++;
        if (v == n - 2) {
            n *= 3;
            realloc(substr, n * sizeof(char));
        }
    } while (x != '\n');


    int strl = strlen(str);
    int substrl = strlen(substr);

    char* substr1 = (char*)malloc(n * sizeof(char));

    upheaval(substr, substr1);

   
    if (str[0] != '\n' && substr[0] != '\n') {
        int k = boyermur(substr1, substrl, str, strl);
        printf("%d", k);
    }

   
    if (str[0] == '\n' || substr[0] == '\n') printf("empty string or empty substring\n");

    free(str);
    free(substr);

    return 0;
}
