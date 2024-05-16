#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

// Obtendo as linhas do arquivo e transformando elas em vetor
std::vector<int> ler_arquivo_para_vetor(const std::string& nome_arquivo) {
    std::vector<int> linhas;
    std::string linha;

    std::ifstream fonte(nome_arquivo);
    if (!fonte.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return linhas;
    }

    while (std::getline(fonte, linha)) {
        if (!linha.empty()) {
            linhas.push_back(std::stoi(linha)); // Adiciona o conteúdo da linha no final do vetor
        }
    }

    fonte.close();

    return linhas;
}

void merge(std::vector<int>& vetor_esq, std::vector<int>& vetor_dir, std::vector<int>& vetor) {
    int tamanho_esq = vetor_esq.size();
    int tamanho_dir = vetor_dir.size();

    int i = 0; // Ponteiro pro índice do vetor esquerdo 
    int j = 0; // Ponteiro pro índice do vetor direito
    int k = 0; // Ponteiro pro índice do vetor principal

    while (i < tamanho_esq && j < tamanho_dir) {
        if (vetor_esq[i] <= vetor_dir[j]) {
            vetor[k] = vetor_esq[i];
            i++;
        }
        else {
            vetor[k] = vetor_dir[j];
            j++;
        }

        k++;
    }

    while (i < tamanho_esq) {
        vetor[k] = vetor_esq[i];
        i++;
        k++;
    }

    while (j < tamanho_dir) {
        vetor[k] = vetor_dir[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<int>& vetor) {
    int tamanho = vetor.size();

    // Base case
    if (tamanho < 2) {
        return;
    }

    int meio = tamanho / 2;

    // Vetores que receberão as metades do vetor de entrada
    std::vector<int> esquerda;
    std::vector<int> direita;

    for (size_t i = 0; i < meio; i++) {
        esquerda.push_back(vetor[i]);
    }

    for (size_t i = 0; i < tamanho - meio; i++) {
        direita.push_back(vetor[meio + i]);
    }

    merge_sort(esquerda);
    merge_sort(direita);
    merge(esquerda, direita, vetor);
}

int main(int argc, char* argv[]) {
    // Verificar se o argumento do arquivo foi fornecido
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>" << std::endl;
        return 1;
    }

    // Iniciar o cronômetro
    auto start = std::chrono::high_resolution_clock::now();

    // nums age como ponteiro para o vetor criado na função abaixo
    std::vector<int> numeros = ler_arquivo_para_vetor(argv[1]); // Passando o argumento da linha de comando para a função

    // Ordenar o vetor
    merge_sort(numeros);

    // Parar o cronômetro
    auto stop = std::chrono::high_resolution_clock::now();

    // Calcular o tempo de execução em microsegundos
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();


    // Imprimir o vetor ordenado
    for (int i = 0; i < numeros.size(); i++) {
        std::cout << numeros[i] << '\n';
    }

    // Calcular o tempo total de processamento em microsegundos
    auto total_duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    // Imprimir o tempo total de processamento
    std::cout << "Tempo total de processamento: " << total_duration << " microsegundos" << std::endl;

    return 0;
}
