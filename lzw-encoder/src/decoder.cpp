#include "../libs/decoder.hpp"

#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

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
    // FILE *fp;
    // fp = fopen("./mensagem_decodificada.txt", "w");

    std::ofstream myfile;
    myfile.open ("./mensagem_decodificada_2linhas.txt");

    std::cout << "\nDescomprimindo arquivo..." << std::endl;

    int tamanhoReferencia = 256;
    std::unordered_map<int, std::string> dicionario = getDicDecode(tamanhoReferencia);

    int caractereAnterior = arquivoComprimido[0];
    int proximoCaractere;
    std::string msgDecodificada = dicionario[caractereAnterior]; 
    std::string traducaoCaractereAnterior = "";
    traducaoCaractereAnterior += msgDecodificada[0];

    //std::cout << msgDecodificada;

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

        // fprintf(fp, "%s", msgDecodificada);
    }
    
    std::cout << "Arquivo descomprimido com sucesso" << std::endl;
    myfile.close();
    // fclose(fp);
}
