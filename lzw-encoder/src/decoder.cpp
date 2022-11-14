#include "../libs/decoder.hpp"

#include <vector>
#include <unordered_map>
#include <string>

Decoder::Decoder() {

}

/**
 * @brief Get the Dic Decode object
 * 
 * @param tamanho 2^k
 */
void getDicDecode(std::uint16_t tamanho) {
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

void descomprimeArquivo() {
    
}