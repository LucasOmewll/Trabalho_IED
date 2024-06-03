#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // Para std::chrono

using namespace std;

// Obtendo as linhas do arquivo e transformando elas em vetor
std::vector<int> ler_arquivo_para_vetor(const std::string& nome_arquivo){
    std::vector<int> linhas;
    std::string linha;

    std::ifstream fonte;
    fonte.open(nome_arquivo);

    while (std::getline(fonte, linha)){
        if(linha != " "){
            linhas.push_back(stoi(linha)); // Adiciona o conteúdo da linha no final do vetor
        }
    }

    return linhas;
}

// Shell sort
void shellSort(std::vector<int>& array) {
    int n = array.size();
    // Rearrange elements at each n/2, n/4, n/8, ... intervals
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}

// Print an array
void printArray(const std::vector<int>& array) {
    for (int i = 0; i < array.size(); i++)
        cout << array[i] << '\n';
}

// Driver code
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now(); // Marca de tempo inicial

    std::vector<int> numeros = ler_arquivo_para_vetor(argv[1]);
    shellSort(numeros);
    printArray(numeros);

    auto end = std::chrono::high_resolution_clock::now(); // Marca de tempo final

    // Criando arquivo ordenado
    std::string nome_dados = "";
    nome_dados.append(argv[1]);
    nome_dados.erase(0, 5);
    std::ofstream dados_ordenado("ordenados/shell_ordenado_"+nome_dados);

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

    // Calcula o tempo decorrido em microsegundos
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Exibe o tempo de execução em microsegundos
    cout << "Tempo total de processamento: " << duration << " microsegundos\n";

    return 0;
}
