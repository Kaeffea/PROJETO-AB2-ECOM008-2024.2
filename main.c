#include <stdio.h>
#include "utils.h"


int main(void){

    int freq[256] = {0};
    FILE* input = fopen("a.txt", "rb");

    if (input == NULL){
        perror("Erro ao abrir o arquivo.");
        return 1;
    }

    count_frequencies(input, freq);

    for (int i = 0; i < 256; i++){
        if (freq[i] > 0){
            printf("Byte %d ('%c'): %d vezes\n", i, (char)i, freq[i]);
        }
    }

    fclose(input);

    return 0;
}