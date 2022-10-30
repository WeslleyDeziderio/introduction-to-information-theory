#include <iostream>

int main(int argc, char *argv[]) {

    printf("Agr foi\n");
    if(argc != 1) {
        std::cout << "Erro: número de argumentos inválidos!" << std::endl;
    }

    return 0;
}