#include "../libs/decoder.hpp"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>

Decoder::Decoder() {

}

/**
 * @brief Get the Dic Decode object
 * 
 * @param tamanho equivalente ao 2^k que é tomado como entrada no programa
 */
std::unordered_map<int, std::string> getDicDecode(std::uint16_t tamanho) {
    std::unordered_map<int, std::string> tabela;

    for (int i = 0; i < tamanho; i++) {
        std::string ch = "";
        ch += char(i);
        tabela[i] = ch;
        // mostra a tabela
        // for (auto const &pair: tabela) {
        //     std::cout << "{" << pair.first << ":" << pair.second << "}";
        // }
    }

    return tabela;
}

/**
 * @brief Método responsável por receber o arquivo comprimido e realizar a sua descompressão
 * 
 * @param arquivoComprimido resultado da chamada do método comprimeArquivo
 */
void descomprimeArquivo(std::vector<int> arquivoComprimido) {
    std::ofstream myfile;
    myfile.open ("./mensagem_decodificada.mp4");

    std::cout << "\nDescomprimindo arquivo..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    int tamanhoReferencia = 256;
    std::unordered_map<int, std::string> dicionario = getDicDecode(tamanhoReferencia);

    int caractereAnterior = arquivoComprimido[0];
    int proximoCaractere;
    std::string msgDecodificada = dicionario[caractereAnterior]; 
    std::string traducaoCaractereAnterior = "";
    traducaoCaractereAnterior += msgDecodificada[0];

    std::string test = "";
    myfile << msgDecodificada;
    test += msgDecodificada;

    for (long unsigned int i = 0; i < arquivoComprimido.size()-1; i++) {
        proximoCaractere = arquivoComprimido[i+1];
        
        if (dicionario.find(proximoCaractere) == dicionario.end()) {
            msgDecodificada = dicionario[caractereAnterior];
            msgDecodificada += traducaoCaractereAnterior;
        } else {
            msgDecodificada = dicionario[proximoCaractere];
        }

        //std::cout << msgDecodificada;
        traducaoCaractereAnterior = "";
        traducaoCaractereAnterior += msgDecodificada[0];

        dicionario[tamanhoReferencia] = dicionario[caractereAnterior] + traducaoCaractereAnterior;
        tamanhoReferencia++;
        caractereAnterior = proximoCaractere;

        myfile << msgDecodificada;
        test += msgDecodificada;
    }


    myfile.close();

    std::cout << "Arquivo descomprimido com sucesso!" << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    std::cout << "Duração da descompressão: " << duration.count() << " milisegundos" << std::endl;
}
