#include "../libs/encoder.hpp"

#include <istream>
#include <ostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <sstream>
#include <chrono>

using tipoCodigo = std::uint16_t; // tipo utilizado para armazenar os dados
namespace globais {
    int k;
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}


//TODO organizar estrutura do código
void Encoder::printHello() {
    std::cout << "Hello world! \n" << std::endl;
    std::cout << "Tamanho máximo do dicionário: " << globais::tamanhoMaxDic << std::endl;
    std::cout << "Insira um valor para 'k' [valores entre 9 e 16]: ";
    std::cin >> globais::k;

    if (globais::k > 16) {
        std::cerr << "Valor de k maior que o permitido!" << std::endl;
        printHello();
    }

    long int tamanhoMaximo = std::pow(2, globais::k);

    std::cout << "k = " << globais::k << std::endl;
    std::cout << "{2^k}: " << tamanhoMaximo << std::endl;

    std::list<std::string> mensagemCodificada = {};
    std::string mensagemDecodificada = "";
}

/**
 * @brief Get the Dic Code object
 * 
 * @param tamanho será o nosso 2^k
 * @return std::vector<char> 
 */

std::vector<std::string> getDicCode(int tamanho) {
    std::vector<std::string> dicionario;

    for (int i = 0; i < tamanho; i++) {
        dicionario.push_back(std::to_string(i));
        std::cout << dicionario[i];
    }

    return dicionario;
}

/**
 * @brief Get the Dic Decode object
 * 
 * @param tamanho será o nosso 2^k
 * @return std::vector<char> 
 */

std::vector<wchar_t> getDicDecode(std::uint16_t tamanho) {
    std::vector<wchar_t> dicionario;

    for (int i = 0; i < tamanho; i++) {

    }

    return dicionario;
}

/**
 * @brief método responsável por realizar a compressão de multmídia
 * 
 */

void comprimeArquivo() {
    std::ifstream myFile("./files/corpus16MB.txt", std::ios_base::in | std::ios_base::ate | std::ios_base::binary);
    if (!myFile.is_open()) {
        std::cerr << "Falha ao abrir o arquivo!" << std::endl;
    } else {
        // std::cout << myFile.rdbuf(); // mostra texto do arquivo
    }


    std::string caractereAtual;
    std::string anterior = "";
    std::cout << "Quantidade de caracteres no arquivo: " << myFile.tellg() << std::endl;

    getDicCode(std::pow(2, 8));

    for (long long int i = 0; i < myFile.tellg(); i++) {
        std::string temp;
        std::getline(myFile, temp);
        std::cout << "achou" << temp[i] << std::endl;
    }


    // auto start = std::chrono::high_resolution_clock::now();

    std::cout << "\nPara valores cada vez maiores de 'k', o tempo de execução do programa irá aumentar!" << std::endl;
    std::cout << "Comprimindo o arquivo... " << std::endl;

    // std::cout << "Arquivo comprimido com sucesso!" << std::endl;

    myFile.close();
    // auto stop = std::chrono::high_resolution_clock::now();
}  