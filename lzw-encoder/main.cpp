#include <iostream>
#include <stdio.h>

#include "./src/encoder.cpp"
#include "./src/decoder.cpp"

void mostraUso() {
    std::cerr << "./main <nome_do_arquivo.extensao_do_arquivo> <nome_do_arquivo.lzw>" << std::endl;
    std::cerr << "./main <nome_do_arquivo.lzw> <nome_do_arquivo.extensao_do_arquivo>" << std::endl;
}

int main(int argc, char *argv[]) {
    // if(argc != 2) {
    //     std::cerr << "Erro: número de argumentos inválidos! \n" << std::endl;
    //     std::cout << "Veja modo de uso abaixo...\n \n" << std::endl;
    //     mostraUso();
    // }

    Encoder enc;
    enc.printHello();

    return 0;
}