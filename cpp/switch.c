#include <stdio.h>

int main() {
    int num = 2;
    int num2 = 2;
    // "case" must be a constant value
    switch (num) {
        case 1 || 3: {
            int localVar;
            localVar = 10;
            printf("Case 1: localVar = %d\n", localVar);
            break;
        }
        case 2: {
            int localVar = 20;
            printf("Case 2: localVar = %d\n", localVar);
            break;
        }
    }
    return 0;
}