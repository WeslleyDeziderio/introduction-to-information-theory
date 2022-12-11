#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <chrono>

#define CODE 256

class fileImg {
public:
    std::vector<unsigned char> header;
    std::vector<unsigned char> data;
};

long unsigned int tamanhoLimite;
using tipoCodigo = std::uint16_t;

namespace globais {
    int k;
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}

std::unordered_map<std::string, int> getDicCode(std::uint16_t tamanho) {
    std::unordered_map<std::string, int> tabela;

    for (int i = 0; i < tamanho; i++) {
        std::string ch = "";
        ch += char(i);
        tabela[ch] = i;
    }

    return tabela;
}

std::unordered_map<std::string, int> globalDictionary = getDicCode(CODE);

fileImg openFile(std::string fileName) {
    std::ifstream myfile(fileName, std::ios_base::in | std::ios_base::binary);
    myfile.seekg(0,myfile.end);
    std::streampos length = myfile.tellg();
    myfile.seekg(0,myfile.beg);

    fileImg img;
    img.data.resize(length);

    myfile.read((char *)&img.data[0],length);

    int i = 0;
    int j = 0;
    while ( i < 3){
        if (img.data[j] == '\n'){
            img.header.push_back(img.data[j]);

            i++;
        }else{
            img.header.push_back(img.data[j]);
        }

        j++;
    }
    img.data.erase(img.data.begin(),img.data.begin()+j);

    myfile.close();
    return img;

};

void lzw_treino_unitario(std::unordered_map<std::string, int>dicionario, std::string fileName) {
    int code = CODE;
    std::vector<int> mensagemCodificada;

    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::string seccion = "";

    fileImg img = openFile(fileName);

    for(long unsigned int i = 0 ; i < img.data.size() ; i++){
        seccion += img.data[i];
    } 
    
    caractereAnterior = seccion[0];
    // std::ofstream dicionarioFile("dicionario.txt", std::ios_base::out | std::ios_base::binary);

    for (long unsigned int i = 0; i < (seccion.length()-1); i++){
        if (i != (seccion.length()-1)) {
            caractereAtual += seccion[i+1];
        }
        std::string compare = caractereAnterior + caractereAtual;
        if (globalDictionary.find(compare) != globalDictionary.end()){
            caractereAnterior = caractereAnterior + caractereAtual;
        } else {
            mensagemCodificada.push_back(globalDictionary[caractereAnterior]);
            if (globalDictionary.size() <= tamanhoLimite){
                // dicionarioFile << caractereAnterior << "\t" << globalDictionary[caractereAnterior] << "\t\t"
                // << compare << "\t" << code << "\n";
                globalDictionary[compare] = code;
                code++;
            }
            caractereAnterior = caractereAtual;

        }
        caractereAtual = "";
    }

    // dicionarioFile.close();
    mensagemCodificada.push_back(globalDictionary[caractereAnterior]);

}


/**
 * @brief 
 * 
 * @param dicionario 
 * @param amostraTeste 
 */
 int TestaLzw(std::unordered_map<std::string, int> dicionario, std::string amostraTeste) {
    std::string path = "orl_faces/";
    unsigned long int size = dicionario.size();
    std::cout << "Tamanho do dicionário de entrada: " << size << std::endl;

    // TODO: input para o k

    // unsigned int code = CODE;
    // unsigned int tamanhoMaximo = std::pow(2, 9);

    std::vector<int> mensagemCodificada;
    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::string proximoCaractere = "";
    std::string secao = "";
    std::string compare = caractereAnterior + caractereAtual;

    // TODO: compress

    fileImg file = openFile(amostraTeste);
    for (unsigned long int i = 0; i < file.data.size();++i) {
        secao += file.data[i];
    } 
    caractereAnterior = secao[0];

     for (long unsigned int i = 0; i < (secao.length()-1); i++){
        if (i != (secao.length()-1)) {
            caractereAtual += secao[i+1];
        }
        if (globalDictionary.find(compare) != globalDictionary.end()) {
            caractereAnterior = caractereAnterior + caractereAtual;
        } else {
            mensagemCodificada.push_back(globalDictionary[caractereAnterior]);
            caractereAnterior = file.data[i];
        }

    }

    if (globalDictionary.find(compare) == globalDictionary.end()) {
        mensagemCodificada.push_back(globalDictionary[caractereAnterior]);
    }

    return mensagemCodificada.size();

}

int main(void) {
    auto inicio = std::chrono::high_resolution_clock::now();

    tamanhoLimite = std::pow(2, 9);
    // fileDeTreinamento();

    int testLzwU = TestaLzw(globalDictionary, "./orl_faces/s1/1.pgm");
    std::cout << "Tamanho do dicionário de teste: " << testLzwU << std::endl;
    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim-inicio);

    std::cout << "Tempo de execução do programa: " << duracao.count() << " ms" << std::endl;
    return 0;
}