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
    // float closestDiff = std::numeric_limits<float>::max();
    // float closestClass = 0.0;

    float closestClasses[k];
    float closestDiffs[k];
    std::fill(closestClasses, closestClasses + k, 0.0);
    std::fill(closestDiffs, closestDiffs + k, std::numeric_limits<float>::max());
    float *max_elem;

    for (auto &trainingLine : trainingData)
    {
        float acc = 0.0;
        for (std::vector<float>::size_type i = 1; i < lineData.size(); i++)
            acc += pow(lineData[i] - trainingLine[i], 2);
        acc = sqrt(acc);
        max_elem = std::max_element(closestDiffs, closestDiffs + k);
        if (acc < *max_elem)
        {
            *max_elem = acc;
            closestClasses[std::distance(closestDiffs, max_elem)] = trainingLine[0];
        }
    }
    int mostFrequentClassIndex = 0;
    int mostFrequentClassValue = -1;
    int count;
    for (int i = 0; i < k; ++i)
        if ((count = std::count(closestClasses, closestClasses + k, closestClasses[i])) > mostFrequentClassValue)
        {
            mostFrequentClassValue = count;
            mostFrequentClassIndex = i;
        }

    return closestClasses[mostFrequentClassIndex];
}

int main(int argc, char *argv[])
{

    vector<vector<float>> trainingData;
    set<float> classes;

    std::ifstream trainingFile(argv[1]);
    std::string line;
    std::string word;
    while (std::getline(trainingFile, line))
    {
        vector<float> lineData;
        stringstream iss(line);
        // int i = 0;
        iss >> word;
        lineData.push_back(stof(word));
        classes.insert(stof(word));
        while (iss >> word)
        {
            lineData.push_back(stof(word.substr(word.find(":") + 1)));
        }
        trainingData.emplace_back(std::begin(lineData), std::end(lineData));
    }

    trainingFile.close();

    std::ifstream testFile(argv[2]);

    int k = atoi(argv[3]);

    int all = 0;
    int correct = 0;
    float predictedClass = 0;
    int numberOfClasses = classes.size();
    vector<int> confusionMatrix(numberOfClasses * numberOfClasses);
    confusionMatrix = {0};
    while (std::getline(testFile, line))
    {
        vector<float> lineData;
        stringstream iss(line);
        // int i = 0;
        iss >> word;
        lineData.push_back(stof(word));
        while (iss >> word)
            lineData.push_back(stof(word.substr(word.find(":") + 1)));

        if (lineData[0] == (predictedClass = findClass(lineData, trainingData, k)))
            ++correct;

        confusionMatrix[predictedClass + numberOfClasses * lineData[0]] += 1;
        ++all;
        // break;
    }
    cout << "Acurácia: " << (float)correct / (float)all << endl;
    cout << "Matriz de confusão:" << endl;
    for (int i = 0; i < numberOfClasses; ++i)
    {
        for (int j = 0; j < numberOfClasses; ++j)
            cout << confusionMatrix[i + numberOfClasses * j] << ", ";
        cout << endl;
    }
}