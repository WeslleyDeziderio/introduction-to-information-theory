#include "../libs/encoder.hpp"

#include <istream>
#include <cstdlib>
#include <ostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <limits>
#include <cmath>
#include <sstream>
#include <chrono>
#include <unordered_map>

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

void getDicCode(std::uint16_t tamanho) {
    std::unordered_map<std::string, int> tabela;

    for (int i = 0; i < tamanho; i++) {
        std::string ch = "";
        ch += char(i);
        tabela[ch] = i;
        // for (auto const &pair: tabela) {
        //     std::cout << "{" << pair.first << ":" << pair.second << "}";
        // }
    }

    return;
}

/**
 * @brief método responsável por realizar a compressão de multmídia
 * 
 */
std::vector<int> comprimeArquivo() {
    // std::ifstream myFile("./files/corpus16MB.txt", std::ios_base::in | std::ios_base::ate | std::ios_base::binary);
    // if (!myFile.is_open()) {
    //     std::cerr << "Falha ao abrir o arquivo!" << std::endl;
    // } else {
    //     std::cout << myFile.rdbuf(); // mostra texto do arquivo
    // }

    FILE *fp;
    fp = fopen("./files/corpus16MB.txt", "rb");

    if (fp == NULL) {
        std::cerr << "Erro abrindo o arquivo " << fp << std::endl;
        exit(EXIT_FAILURE);
    }

    char ch;
    std::vector<int> mensagemCodificada;
    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::cout << "Quantidade de caracteres no arquivo: " << fp << std::endl;

    getDicCode(std::pow(2, 8));
    std::cout << "Comprimindo o arquivo... " << std::endl;

    ch = fgetc(fp);
    while(ch != EOF) {
        printf("%s", ch);
        ch = fgetc(fp);
    }

    return mensagemCodificada;
    // auto start = std::chrono::high_resolution_clock::now();

    std::cout << "Arquivo comprimido com sucesso!" << std::endl;

    fclose(fp);
    // auto stop = std::chrono::high_resolution_clock::now();
}  