#include <bits/stdc++.h>
#include <string>
#include <math.h>
#define CODE 256


long unsigned int tamanhoLimite;
using tipoCodigo = std::uint16_t;

namespace globais {
    int k;
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}

struct fileImg{
    std::vector<unsigned char> data;
    std::vector<unsigned char> header;
}tImage;

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

fileImg openFile(std::string fileName){

    std::ifstream myfile(fileName, std::ios_base::in | std::ios_base::binary);
    myfile.seekg(0,myfile.end);
    std::streampos length = myfile.tellg();
    myfile.seekg(0,myfile.beg);

    struct fileImg img;
    img.data.resize(length);

    myfile.read((char *)&img.data[0],length);

    int i = 0;
    int j = 0;
    while( i < 3){

        if( img.data[j] == '\n'){
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

}

void lzw_treino_unitario(std::string fileName) {
    int code = CODE;
    std::vector<int> mensagemCodificada;

    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::string seccion = "";

    struct fileImg img = openFile(fileName);

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

void fileDeTreinamento(){

    for(int i = 1 ; i < 41 ; i++){
        for(int j = 1 ; j < 11 ;j ++){

            std::string filePath = "faces/";
            filePath = filePath + "s" + std::to_string(i) + "/" + std::to_string(j) + ".pgm";
            
            lzw_treino_unitario(filePath);

        }
    }
}

int main(){

    tamanhoLimite = std::pow(2,9);

    fileDeTreinamento();

    return 0;
}

/*
P5 \n
altura largura \n
dimensão \n
DATA


*/