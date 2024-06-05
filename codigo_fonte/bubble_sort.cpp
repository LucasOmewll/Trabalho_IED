#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

// Obtendo as linhas do arquivo e transformando elas em vetor
std::vector<int> ler_arquivo_para_vetor(const std::string& nome_arquivo) {
    std::vector<int> linhas;
    std::string linha;

    std::ifstream fonte;
    fonte.open(nome_arquivo);

    while (std::getline(fonte, linha)) {
        if (linha != " ") {
            linhas.push_back(std::stoi(linha)); // Adiciona o conteúdo da linha no final do vetor
        }
    }

    return linhas;
}

void bubble_sort(std::vector<int>& vetor) {
    int tamanho = vetor.size();

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                // Troca os elementos se eles estiverem na ordem errada
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    // Obtendo o tempo inicial
    auto start = std::chrono::steady_clock::now();

    // nums age como ponteiro para o vetor criado na função abaixo
    std::vector<int> numeros = ler_arquivo_para_vetor(argv[1]); // Passando o argumento da linha de comando para a função

    // Criando o nome do arquivo de texto ordenado

    bubble_sort(numeros);

    // Obtendo o tempo final
    auto end = std::chrono::steady_clock::now();

    // Calculando o tempo de execução em microsegundos
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Criando arquivo ordenado
    std::string nome_dados = "";
    nome_dados.append(argv[1]);
    nome_dados.erase(0, 5);
    std::ofstream dados_ordenado("ordenados/bubble_ordenado_"+nome_dados);

    // Preenchendo o arquivo com os dados ordenados
    if(dados_ordenado.is_open()){
        for (int i = 0; i < numeros.size(); i++) {
            dados_ordenado << numeros[i] << '\n';
        }

        dados_ordenado.close();
    }
    else{
        std::cout << "Falha ao criar arquivo ordenado.";
    }


    // Exibindo o tempo de execução
    std::cout << "Tempo total de processamento: " << duration << " microsegundos\n";

    return 0;
}
