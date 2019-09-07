#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <math.h>
#include <set>

using namespace std;

float findClass(vector<float> lineData, vector<vector<float>> trainingData, int k)
{
    /* Encontra a classe de uma linha de dados */

    // Vetor de classes proximas
    float closestClasses[k];
    // Vetor de diferencas proximas
    float closestDiffs[k];
    // Inicia vetor de diferencas com infinito
    std::fill(closestDiffs, closestDiffs + k, std::numeric_limits<float>::max());

    float *max_elem;
    // Para cada vetor de treinamento
    for (auto &trainingLine : trainingData)
    {
        // Calcula a distancia euclidiana
        float acc = 0.0;
        for (std::vector<float>::size_type i = 1; i < lineData.size(); i++)
            acc += pow(lineData[i] - trainingLine[i], 2);
        acc = sqrt(acc);
        // Encontra o maior elemento do vetor de diferencas
        max_elem = std::max_element(closestDiffs, closestDiffs + k);
        // Se a distancia for menor substitui o maior elemento em ambos os vetores, classes e diferencas
        if (acc < *max_elem)
        {
            *max_elem = acc;
            closestClasses[std::distance(closestDiffs, max_elem)] = trainingLine[0];
        }
    }
    // Encontra a classe mais frequente
    int mostFrequentClassIndex = 0;
    int mostFrequentClassValue = -1;
    int count;
    for (int i = 0; i < k; ++i)
        if ((count = std::count(closestClasses, closestClasses + k, closestClasses[i])) > mostFrequentClassValue)
        {
            mostFrequentClassValue = count;
            mostFrequentClassIndex = i;
        }
    // Retorna a classe mais frequente do vetor de classes
    return closestClasses[mostFrequentClassIndex];
}

int main(int argc, char *argv[])
{

    // Lista de vetores de dados
    vector<vector<float>> trainingData;
    // Set de classes
    set<float> classes;

    // Abre o arquivo de treinamento
    std::ifstream trainingFile(argv[1]);

    std::string line;
    std::string word;
    // Para cada linha le o vetor de atributos
    while (std::getline(trainingFile, line))
    {
        vector<float> lineData;
        stringstream iss(line);
        // Inicialmente le a classe
        iss >> word;
        lineData.push_back(stof(word));
        classes.insert(stof(word));
        // Le os atributos
        while (iss >> word)
        {
            lineData.push_back(stof(word.substr(word.find(":") + 1)));
        }
        // Adiciona o vetor na lista de vetores
        trainingData.emplace_back(std::begin(lineData), std::end(lineData));
    }

    trainingFile.close();

    // Abre o arquivo de teste
    std::ifstream testFile(argv[2]);

    int k = atoi(argv[3]);

    int all = 0;
    int correct = 0;
    float predictedClass = 0;
    int numberOfClasses = classes.size();
    vector<int> confusionMatrix(numberOfClasses * numberOfClasses);
    confusionMatrix = {0};

    // Para cada linha do arquivo de teste
    while (std::getline(testFile, line))
    {
        // Le a classe e os atributos
        vector<float> lineData;
        stringstream iss(line);
        iss >> word;
        lineData.push_back(stof(word));
        while (iss >> word)
            lineData.push_back(stof(word.substr(word.find(":") + 1)));

        // Se a predicao for correta acrescenta na quantidade de predicoes corretas
        if (lineData[0] == (predictedClass = findClass(lineData, trainingData, k)))
            ++correct;

        // Atualiza matriz de confusao
        confusionMatrix[predictedClass + numberOfClasses * lineData[0]] += 1;

        ++all;
    }

    // Imprime os resultados
    cout << "Acurácia: " << (float)correct / (float)all << endl;
    cout << "Matriz de confusão:" << endl;
    for (int i = 0; i < numberOfClasses; ++i)
    {
        for (int j = 0; j < numberOfClasses; ++j)
            cout << confusionMatrix[i + numberOfClasses * j] << ", ";
        cout << endl;
    }
    testFile.close();
}