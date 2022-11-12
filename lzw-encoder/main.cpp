#include <iostream>
#include <stdio.h>

#include "./src/encoder.cpp"
#include "./src/decoder.cpp"

void mostraUso () {
    
}

int main(int argc, char *argv[]) {

    if(argc != 1) {
        std::cout << "Erro: número de argumentos inválidos!" << std::endl;
    }

    Encoder enc;
    enc.printHello();

    return 0;
}