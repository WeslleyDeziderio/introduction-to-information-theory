#include "../libs/encoder.hpp"

#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using tipoCodigo = std::uint16_t; // tipo de dado utilizado para armazenar os dados
namespace global {
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}

void Encoder::printHello() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Tamanho máximo do dicionário {2^K}:" <<  global::tamanhoMaxDic << std::endl;
}

Encoder::Encoder() {

}