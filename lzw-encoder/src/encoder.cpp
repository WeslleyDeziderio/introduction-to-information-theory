#include "../libs/encoder.hpp"

#include <istream>
#include <ostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <chrono>

using tipoCodigo = std::uint16_t; // tipo utilizado para armazenar os dados
namespace globais {
    int k;
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}

void Encoder::printHello() {
    std::cout << "Hello world! \n" << std::endl;
    std::cout << "Tamanho máximo do dicionário: " << globais::tamanhoMaxDic << std::endl;
    std::cout << "Insira um valor para 'k' [valores entre 9 e 16]: ";
    std::cin >> globais::k;

    long int tamanhoMaximo = std::pow(2, globais::k);

    std::cout << "k = " << globais::k << std::endl;
    std::cout << "{2^k}: " << tamanhoMaximo << std::endl;

    std::list<std::string> mensagemCodificada = {};
    std::string mensagemDecodificada = "";
}

/**
 * @brief lê o conteúdo do parâmetro arquivoEntrada e escreve parâmetro arquivoSaida
 * 
 */

std::list<std::string> getDicCode(std::uint16_t tamanho) {
    std::list<std::string> dicionario = {};

    for (long long int i = 0; i < tamanho; i++) {
        
    }

    return dicionario;
}

std::list<std::string> getDicDecode(std::uint16_t tamanho) {
    std::list<std::string> dicionario = {};

    for (long long int i = 0; i < tamanho; i++) {

    }

    return dicionario;
}

void comprimeArquivo() {
    std::ifstream myFile("./files/corpus16MB.txt", std::ios_base::in | std::ios_base::ate | std::ios_base::binary);
    if (!myFile.is_open()) {
        std::cerr << "Falha ao abrir o arquivo!" << std::endl;
    } else {
        // std::cout << myFile.rdbuf();
    }

    std::string anterior = "";
    std::cout << myFile.tellg() << std::endl;

    for (long long int i = 0; i < myFile.tellg(); i++) {

    }


    // auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Para valores cada vez maiores de 'k', o tempo de execução do programa irá aumentar!" << std::endl;
    std::cout << "Comprimindo o arquivo... " << std::endl;

    myFile.close();
    // auto stop = std::chrono::high_resolution_clock::now();
}  