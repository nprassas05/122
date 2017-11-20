#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    if (argc <= 1) {
        fprintf(stderr, 
                 "please supply an integer at the command line\n");
    } else {
        int a = atoi(argv[1]);
        switch(a % 2) {
            case 0:
                puts("x is even!");
                break;
            default:
                puts("x is odd!");
                break;
        }
    }
    return 0;
}
