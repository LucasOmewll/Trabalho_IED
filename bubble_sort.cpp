#include <iostream>
#include <fstream>
#include <vector>

// Obtendo as linhas do arquivo e transformando elas em vetor
std::vector<int> ler_arquivo_para_vetor(const std::string& nome_arquivo){
    std::vector<int> linhas;
    std::string linha;

    std::ifstream fonte;
    fonte.open(nome_arquivo);

    while (std::getline(fonte, linha)){
        if(linha != " "){
            linhas.push_back(std::stoi(linha)); //Adiciona o conteúdo da linha no final do vetor
        }
    }

    return linhas;
}

void bubble_sort(std::vector<int>& vetor){
    int tamanho = vetor.size();

    for (int i = 0; i < tamanho-1; i++){
        for (int j = 0; j < tamanho-i-1; j++){
            if (vetor[j] > vetor[j+1]){
                // Troca os elementos se eles estiverem na ordem errada
                int temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]){

    // nums age como ponteiro para o vetor criado na função abaixo
    std::vector<int> numeros = ler_arquivo_para_vetor(argv[1]); // Passando o argumento da linha de comando para a função

    bubble_sort(numeros);
    for (int i = 0; i < numeros.size(); i++){
        std::cout << numeros[i] << '\n';
    } 
}