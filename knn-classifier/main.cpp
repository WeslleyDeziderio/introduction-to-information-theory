#include <bits/stdc++.h>
#include <string>
#include <math.h>
#include <time.h>
#include <iostream>
#define CODE 256
#define SEED 666
#define RANGE 10


long unsigned int tamanhoLimite;
using tipoCodigo = std::uint16_t;

namespace globais {
    int k;
    const tipoCodigo tamanhoMaxDic {std::numeric_limits<tipoCodigo>::max()}; // 2^16
}

//variavel que representa o header e o data do arquivo
struct fileImg{
    std::vector<unsigned char> data;
    std::vector<unsigned char> header;
}tImage;

//variavel que armazena o sorteio dos arquivos para treino e teste
struct randomNumb{
    std::vector<int> treinamento;
    std::vector<int> teste; 
}tRandom;

//variavel com os caminhos dos arquivos para o treinamento e testagem
struct dataSelection{
    std::vector<std::string> x_test;
    std::vector<std::string> x_train;
    std::vector<int> y_test;

}tData;


// Função que sorteia aleatoriamente os arquivos de treinamento e teste.
randomNumb randomSelect (int range){
    struct randomNumb select;
    srand(SEED);

    std::vector<int> sorteados;
    int j = (rand() % range);
    sorteados.push_back(j);

    for (int i = 1; i < range ; i++){

        while (true) {
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

    for (long unsigned int i = 0; i < sorteados.size() ; i++){
        if ( i % 2 == 0){
            select.teste.push_back(sorteados[i]);
        } else{
            select.treinamento.push_back(sorteados[i]);
        }

    }

    return select;
}

// Função que retorna uma variavel struct que contem tds os caminhos dos arquivos para treinamento e teste,
// selecionados de forma aleatoria.
dataSelection selectData(){

    randomNumb raffleNumbs;
    raffleNumbs = randomSelect(RANGE);
    dataSelection selectedData;

    for(long unsigned int i = 1 ; i < 41 ; i++){
        for(int j = 1 ; j < 6 ;j++){
            std::string filePath = "faces/";
            filePath = filePath + "s" + std::to_string(i) + "/" + std::to_string(raffleNumbs.teste[j-1]) + ".pgm";
            selectedData.y_test.push_back(i);
            selectedData.x_test.push_back(filePath);
        }
    }

    for (long unsigned int i = 1 ; i < 41 ; i++){
        for(int j = 1 ; j < 6 ;j++){
            std::string filePath = "faces/";
            filePath = filePath + "s" + std::to_string(i) + "/" + std::to_string(raffleNumbs.treinamento[j-1]) + ".pgm";
            selectedData.x_train.push_back(filePath);
        }
    }

    return selectedData;
}

std::unordered_map<std::string, int> getDicCode(std::uint16_t tamanho) {
    std::unordered_map<std::string, int> tabela;

    for (long unsigned int i = 0; i < tamanho; i++) {
        std::string ch = "";
        ch += char(i);
        tabela[ch] = i;
    }

    return tabela;
}


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
    while (i < 3){

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


//vector global de dicionarios 
std::vector<std::unordered_map<std::string, int>> multDictionary;

//Função que treina os dicionarios com base nos arquivos selecionados para treino
void lzw_treino(dataSelection paths) {

    int code = CODE;    
    std::unordered_map<std::string, int> dictionary = getDicCode(code);

    for(long unsigned int k = 1; k <= paths.x_train.size() ; k++ ){

        struct fileImg img = openFile(paths.x_train[k-1]);
        std::vector<int> mensagemCodificada;
        std::string caractereAnterior = "";
        std::string caractereAtual = "";
        std::string seccion = "";

        for(long unsigned int i = 0 ; i < img.data.size() ; i++){
            seccion += img.data[i];
        } 
        
        caractereAnterior = img.data[0];

        for (long unsigned int i = 0; i < (img.data.size()-1); i++){
            if (i != (img.data.size()-1)) {
                caractereAtual += img.data[i+1];
            }
            std::string compare = caractereAnterior + caractereAtual;
            if (dictionary.find(compare) != dictionary.end()){
                caractereAnterior = caractereAnterior + caractereAtual;
            } else {
                mensagemCodificada.push_back(dictionary[caractereAnterior]);
                if (dictionary.size() <= tamanhoLimite){
                    dictionary[compare] = code;
                    code++;
                }
                caractereAnterior = caractereAtual;

            }
            caractereAtual = "";
        }

        mensagemCodificada.push_back(dictionary[caractereAnterior]);

        if((k % 5) == 0){
            // reseta o dicionario após 5 imagens para treino
            code = CODE;
            multDictionary.push_back(dictionary);
            dictionary = getDicCode(code);
        }
    }

}

//Função que retorna o tamanho da imagem comprimida
 int TestaLzw(std::unordered_map<std::string, int> dicionario, std::string amostraTeste) {
    std::vector<int> mensagemCodificada;
    std::string caractereAnterior = "";
    std::string caractereAtual = "";
    std::string proximoCaractere = "";
    std::string secao = "";
    std::string compare = caractereAnterior + caractereAtual;

    fileImg file = openFile(amostraTeste);
    for (unsigned long int i = 0; i < file.data.size();i++) {
        secao += file.data[i];
    } 
    caractereAnterior = file.data[0];

     for (long unsigned int i = 0; i < (file.data.size()-1); i++){
        if (i != (file.data.size()-1)) {
            caractereAtual += file.data[i+1];
        }
        
        if (dicionario.find(caractereAnterior + caractereAtual) != dicionario.end()) {
            caractereAnterior = caractereAnterior + caractereAtual;
        } else {
            mensagemCodificada.push_back(dicionario[caractereAnterior]);
            caractereAnterior = file.data[i];
        }

    }

    if (dicionario.find(caractereAnterior + caractereAtual) != dicionario.end()) {
        mensagemCodificada.push_back(dicionario[caractereAnterior]);
    }

    return mensagemCodificada.size();

}

//Função que recebe o vector de dicionarios e o arquivo para o teste,
//retorna em quais dicionarios o arquivo tem maior compressão( supondo que é possivel ter a mesma taxa de compressão)
std::vector<int> predicao(std::vector<std::unordered_map<std::string, int>> train_data, std::string test_data){

    std::vector<int> size_testing;

    for(long unsigned int i = 0; i < train_data.size() ; i++){
        size_testing.push_back(TestaLzw(train_data[i], test_data));
    }

    int menorValor = *min_element(size_testing.begin(),size_testing.end());
    std::vector<int> indexValor;

    for(long unsigned int i = 1 ; i <= size_testing.size() ; i++){
        if(menorValor == size_testing[i-1]){
            indexValor.push_back(i);
        }
    }
    // returna em quais dicionarios( indice em train_data ) foram encontradas o menor valor encontrado pelo TestaLzw 
    return indexValor;
}


int main(){
    auto inicio = std::chrono::high_resolution_clock::now();
    tamanhoLimite = std::pow(2,16);

    //criando os caminhos para os arquivos
    dataSelection paths;
    paths = selectData();
    lzw_treino(paths);

    //teste
    std::cout << "Teste" << std::endl;
    std::vector<std::vector<int>> predictions;
    for(long unsigned int i = 0; i < paths.x_test.size() ; i++){
        printf("%ld\n",i);
        predictions.push_back(predicao(multDictionary,paths.x_test[i]));
    }

    //print testes
    std::cout << "Arquivos:" << std::endl;
    for(long unsigned int i = 0; i < paths.x_test.size(); i++){

        std::cout << paths.x_test[i] << "\t" << "Predição: " ;
        for(long unsigned int j = 0; j < predictions[i].size() ; j++){
            if(predictions[i].size() == 40){
                std::cout << "Todas equiprovaveis" ;
                break;
            }
            std::cout << "s" << predictions[i][j] << " ";
        }
        std::cout << "\t" << "Pasta real: s" << paths.y_test[i] << std::endl;
    }

    auto fim = std::chrono::high_resolution_clock::now();

    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);

    std::cout << "Tempo de processamento: " << dur.count() << " ms" << std::endl;

    return 0;
}
