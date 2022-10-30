#include <iostream>

#include "./src/encoder.cpp"
#include "./src/decoder.cpp"

int main(int argc, char *argv[]) {

    printf("Agr foi\n");
    if(argc != 1) {
        std::cout << "Erro: número de argumentos inválidos!" << std::endl;
    }

    Encoder enc;
    enc.printHello();

    return 0;
}