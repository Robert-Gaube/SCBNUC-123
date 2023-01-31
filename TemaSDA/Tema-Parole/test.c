#include <stdio.h>
#include <string.h>

char sol[1000];

char alfabet[] = "abc";
char litere[] = "abc";

int n;
int lu;

FILE *f;

int solutie() {
    int i;
    for(i = 0; i < lu; ++i) {
        if(!strchr(sol, litere[i])) return 0;
    }
    return 1;
}

void Back(int k) {
    printf("%d\n", k);
    if(k == 4) {
        if(solutie()) {
            puts("Sol");
            fprintf(f, "%s\n", sol);
            puts("After sol");
        }
    }
    else {
        for(int i = 0; i < n; ++i) {
            printf("%d: %c\n", k, alfabet[i]);
            sol[k] = alfabet[i];
            Back(k + 1);
        }
    }
}

int main() {
    n = strlen(alfabet);
    lu = strlen(litere);

    sol[n] = 0;

    f = fopen("text.txt", "w");

    lu = 0;
    Back(0);

    fclose(f);

    return 0;
}