#include "../libs/encoder.hpp"

#include <cstdlib>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <fstream>

long unsigned int tamanhoLimite;
using tipoCodigo = std::uint16_t;
namespace globais {
    int k;
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}

//TODO organizar estrutura do código
void Encoder::printHello() {
    std::cout << "Hello world! \n" << std::endl;
    std::cout << "Tamanho máximo do dicionário: " << globais::tamanhoMaxDic << std::endl;
    std::cout << "Para valores cada vez maiores de 'k', o tempo de execução do programa irá aumentar!" << std::endl;
    std::cout << "Insira um valor para 'k' entre 9 e 16: ";
    std::cin >> globais::k;

    if (globais::k < 9 || globais::k > 16) {
        std::cerr << "Valor de k diferente do permitido!" << std::endl;
        printHello();
    }

    long int tamanhoMaximo = std::pow(2, globais::k);
    
    tamanhoLimite = tamanhoMaximo;
    std::cout << "k = " << globais::k << std::endl;
    std::cout << "{2^k}: " << tamanhoMaximo << std::endl;

    std::vector<std::string> mensagemCodificada;
    std::string mensagemDecodificada = "";
}

/**
 * @brief Get the Dic Code object
 * 
 * @param tamanho será o nosso 2^k
 * @return std::vector<char> 
 */

std::unordered_map<std::string, int> getDicCode(std::uint16_t tamanho) {
    std::unordered_map<std::string, int> tabela;

    for (int i = 0; i < tamanho; i++) {
        std::string ch = "";
        ch += char(i);
        tabela[ch] = i;
        // for (auto const &pair: tabela) {
        //     std::cout << "{" << pair.first << ":" << pair.second << "}";
        // }
    }

    return tabela;
}


/**
 * @brief método responsável por realizar a compressão multmídia
 * 
 */
std::vector<int> comprimeArquivo() {
    int code = 256;
    std::unordered_map<std::string, int> dictionary = getDicCode(code);
    std::vector<int> mensagemCodificada;
  
    // std::cout << "Quantidade de caracteres no arquivo: " << fp << std::endl;

    std::cout << "\nComprimindo o arquivo... " << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::string seccion = "";

    std::ifstream myfile("disco.mp4", std::ios_base::in | std::ios_base::binary);
    myfile.seekg(0, myfile.end);
    std::streampos length = myfile.tellg();
    myfile.seekg(0, myfile.beg);

    std::vector<unsigned char> discoBytes(length);

    myfile.read((char *)&discoBytes[0],length);

    myfile.close();

    for(long unsigned int i = 0 ; i < discoBytes.size() ; i++){
        seccion += discoBytes[i];
    } 
    
    caractereAnterior = seccion[0];
    std::ofstream dicionarioFile("dicionario.txt", std::ios_base::out | std::ios_base::binary);

    for (long unsigned int i = 0; i < (seccion.length()-1); i++){
        if (i != (seccion.length()-1)) {
            caractereAtual += seccion[i+1];
        }
        std::string compare = caractereAnterior + caractereAtual;
        if (dictionary.find(compare) != dictionary.end()){
            caractereAnterior = caractereAnterior + caractereAtual;
        } else {
            // std::cout << caractereAnterior << "\t" << dictionary[caractereAnterior] << "\t\t"
            //  << compare << "\t" << code << std::endl;
            mensagemCodificada.push_back(dictionary[caractereAnterior]);
            if (dictionary.size() <= tamanhoLimite){
                dictionary[compare] = code;
                code++;
            }
            caractereAnterior = caractereAtual;

        }
        caractereAtual = "";
    }

    dicionarioFile.close();
    mensagemCodificada.push_back(dictionary[caractereAnterior]);

    FILE *exit_file = fopen("mensagem_codificada.bin", "wb");

    for (long unsigned int i = 0; i < mensagemCodificada.size(); i++) {
        fwrite(&mensagemCodificada[i], 1, 1,exit_file);
    }

    printf("\n");
    std::cout << "Arquivo comprimido com sucesso!" << std::endl;

    fclose(exit_file);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    std::cout << "Duração da compressão: " << duration.count() << " milisegundos." << std::endl;   
    return mensagemCodificada;
}