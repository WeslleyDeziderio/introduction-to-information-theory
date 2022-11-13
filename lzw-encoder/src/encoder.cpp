#include "../libs/encoder.hpp"

#include <istream>
#include <ostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

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
}

/**
 * @brief lê o conteúdo do parâmetro arquivoEntrada e escreve parâmetro arquivoSaida
 * 
 */

void coder(std::istream &arquivoEntrada, std::ostream &arquivoSaida) {
    std::cout << "Para valores cada vez maiores de 'k', o tempo de execução do programa irá aumentar!" << std::endl;
    std::cout << "Comprimindo o arquivo... " << std::endl;

    
}