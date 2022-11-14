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

// int compareDictionary(std::unordered_map<std::string, int> dicionario, std::string current){

// 	for( int i = 0; i < dicionario.size(); i++){
		
//         if( current.size() == dicionario[i].size()){
//             if( ( current.compare(dicionario[i]) ) == 0 ){
                
//                 return i;
//             }
// 	    }
//     }
// 	return 0;
// }

/**
 * @brief método responsável por realizar a compressão multmídia
 * 
 */
std::vector<int> comprimeArquivo() {
    FILE *fp;
    fp = fopen("corpus16MB.txt", "rb");

    if (fp == NULL) {
        std::cerr << "Erro abrindo o arquivo " << fp << std::endl;
        exit(EXIT_FAILURE);
    }

    int code = 256;
    std::unordered_map<std::string, int> dictionary = getDicCode(code);

    char ch;
    std::vector<int> mensagemCodificada;
    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::cout << "Quantidade de caracteres no arquivo: " << fp << std::endl;

    getDicCode(std::pow(2, 8));
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Comprimindo o arquivo... " << std::endl;

    ch = fgetc(fp);
    caractereAnterior += ch;
    std::string seccion = "";

    while(ch != EOF) {
        for(int i = 0 ; i < 100 ; i++){
            if(ch == EOF){
                seccion[i-1] = '\0';
                break;
            }
            seccion = seccion + ch;
            ch = fgetc(fp);
        }

        for(int i = 0; i < (seccion.length() -1) ; i++){
        
            if( i != (seccion.length() - 1)){
                caractereAtual += seccion[i+1];
            }
            std::string compare = caractereAnterior + caractereAtual;
            if( dictionary.find(compare) != dictionary.end() ){

                caractereAnterior = caractereAnterior + caractereAtual;
            }else{
                // std::cout << caractereAnterior << "\t" << dictionary[caractereAnterior] << "\t\t"
                // << caractereAnterior + caractereAtual << "\t" << std::endl;
                mensagemCodificada.push_back(dictionary[caractereAnterior]);
                dictionary[compare] = code;
                code++;
                caractereAnterior = caractereAtual;

            }
            caractereAtual = "";
  
        }
        seccion = "";
    }
    //mensagemCodificada.push_back(dictionary[caractereAnterior]);


    FILE *exit_file = fopen("mensagem_codificada.txt", "a");

    for(int i = 0; i < mensagemCodificada.size(); i++){
        fprintf(exit_file,"%d",mensagemCodificada[i]);
    }
    fclose(exit_file);
    printf("\n");
    std::cout << "Arquivo comprimido com sucesso!" << std::endl;
    // auto start = std::chrono::high_resolution_clock::now();


    fclose(fp);
    return mensagemCodificada;
    // auto stop = std::chrono::high_resolution_clock::now();
}  