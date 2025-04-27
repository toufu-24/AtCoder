#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void) {
    char T[11], U[11];
    scanf("%s", T);
    scanf("%s", U);
    // 始まりを探索
    for (int i = 0; i < 11; i++) {
        if (T[i] == '\0') {
            break;
        }
        bool ok = true;
        // Uが入るか見る
        for (int j = 0; j < 11; j++) {
            if (U[j] == '\0') {
                break;
            }
            if (strlen(T) <= i + j) {
                ok = false;
                break;
            }
            if (T[i + j] != '?') {
                if (T[i + j] != U[j]) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");
}
