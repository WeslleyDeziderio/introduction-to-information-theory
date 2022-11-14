#include <istream>
#include <ostream>
#include <fstream>
#include <list>
#include <string.h>
#include <vector>
#include <limits>
#include <cmath>
#include <chrono>
#include <iostream>

int compareDictionary(int quant, std::vector<std::string> dicionario, std::string current){

 for( int i = 0; i < dicionario.size(); i++){
  
        if( current.size() == dicionario.size()){
            if( ( current.compare(dicionario[i]) ) == 0 ){
                
                return i;
            }
        }
 }

 return -1;
}

int main(){
    std::string msg = "BANANA";
    std::string previous = "";
    std::string current = "";
    std::vector<std::string> dictionary;
    int coded_msg[100];
    int count = 0;

    dictionary.push_back("A");
    dictionary.push_back("B");
    dictionary.push_back("N");

    for(int i = 0,j = 1; i < msg.size() ; i++){

        current = previous + msg[i];
        std::cout << current << std::endl;
        
        int indice = compareDictionary(current.size(), dictionary,current );
        
        if( indice >= 0){
            previous = current;
            coded_msg[count++] = indice;

        }else{

            coded_msg[count++] = dictionary.size();
            previous = msg[i];
            dictionary.push_back((current + msg[i+1]));
        }
        
    }

    for(int i = 0; i < dictionary.size() ; i++){
        printf("%s\n", dictionary[i].c_str());
        
    }
}