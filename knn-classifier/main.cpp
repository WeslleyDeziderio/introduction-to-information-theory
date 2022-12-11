#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <chrono>

#define CODE 256
#define SEED 666
#define RANGE 10

class fileImg {
public:
    std::vector<unsigned char> header;
    std::vector<unsigned char> data;
};

struct randomNumber{
    std::vector<int> treinamento;
    std::vector<int> teste; 
}tRandom;

randomNumber randomSelect(int range){

    struct randomNumber select;
    srand(SEED);

    std::vector<int> sorteados;
    int j = (rand() % range);
    sorteados.push_back(j);

    for (int i = 1; i < range ; i++){

        while(true){
            int flag = 0;
            j = 1 + (rand() % (range));
            for(long unsigned int k = 0; k < sorteados.size();k++){
                if(sorteados[k] == j){
                    break;
                }
                if(k == (sorteados.size()-1)){
                    flag = 1;
                }
            }
            if(flag == 1){
                break;
            }
        }
        sorteados.push_back(j);
    }
    for(long unsigned int i = 0; i < sorteados.size() ; i++){
        if( i % 2 == 0){
            select.teste.push_back(sorteados[i]);
        }else{
            select.treinamento.push_back(sorteados[i]);
        }

    }
    return select;
}

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

std::vector<std::unordered_map<std::string, int>> multDictionary;


std::unordered_map<std::string, int> lzw_treino_unitario(std::unordered_map<std::string, int>dicionario, std::string fileName) {
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
        if (dicionario.find(compare) != dicionario.end()){
            caractereAnterior = caractereAnterior + caractereAtual;
        } else {
            mensagemCodificada.push_back(dicionario[caractereAnterior]);
            if (dicionario.size() <= tamanhoLimite){
                // dicionarioFile << caractereAnterior << "\t" << globalDictionary[caractereAnterior] << "\t\t"
                // << compare << "\t" << code << "\n";
                dicionario[compare] = code;
                code++;
            }
            caractereAnterior = caractereAtual;

        }
        caractereAtual = "";
    }

    // dicionarioFile.close();
    mensagemCodificada.push_back(dicionario[caractereAnterior]);

    return dicionario;

}

void filaDeTreinamento() { 
    struct randomNumber selection;
    selection = randomSelect(RANGE);

    for(int i = 1 ; i < 41 ; i++){
        std::unordered_map<std::string, int> tempDictionary = getDicCode(CODE);

        for(int j = 1 ; j < 6 ; j++){
            std::string filePath = "faces/";
            filePath = filePath + "s" + std::to_string(i) + "/" + std::to_string(selection.treinamento[j-1]) + ".pgm";
            tempDictionary = lzw_treino_unitario(tempDictionary, filePath);

        }
        multDictionary.push_back(tempDictionary);
    }
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
        if (dicionario.find(compare) != dicionario.end()) {
            caractereAnterior = caractereAnterior + caractereAtual;
        } else {
            mensagemCodificada.push_back(dicionario[caractereAnterior]);
            caractereAnterior = file.data[i];
        }

    }

    if (dicionario.find(compare) == dicionario.end()) {
        mensagemCodificada.push_back(dicionario[caractereAnterior]);
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