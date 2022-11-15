/**
 * @file main.cpp
 * @author Weslley Dezidério e Nathan Rodrigues
 * @brief 
 * @version 0.4
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <stdio.h>

#include "./src/encoder.cpp"
#include "./src/decoder.cpp"

void mostraUso() {
    // std::cerr << "Compressão: g++ main.cpp -o main && ./main <nome_do_arquivo.extensao_do_arquivo>" << std::endl;
    // std::cerr << "Descompressão: g++ main.cpp -o main && ./main <nome_do_arquivo.lzw>" << std::endl;
}

int main(int argc, char *argv[]) {
    // if(argc != 2) {
    //     std::cerr << "Erro: número de argumentos inválidos! \n" << std::endl;
    //     std::cout << "Veja modo de uso abaixo...\n \n" << std::endl;
    //     mostraUso();
    // }
    
    Encoder encoder;
    encoder.printHello();

    std::vector<int> saidaComprimeArquivo = comprimeArquivo();
    descomprimeArquivo(saidaComprimeArquivo);

    return 0;
}