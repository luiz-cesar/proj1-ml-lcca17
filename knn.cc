#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <math.h>

using namespace std;

bool findClass(vector<float> lineData, vector<vector<float>> trainingData)
{
    float closestDiff = std::numeric_limits<float>::max();
    float closestClass = 0.0;

    for (auto &trainingLine : trainingData)
    {
        float acc = 0.0;
        for (std::vector<float>::size_type i = 1; i < lineData.size(); i++)
            acc += pow(lineData[i] - trainingLine[i], 2);
        acc = sqrt(acc);
        if (acc < closestDiff)
        {
            closestDiff = acc;
            closestClass = trainingLine[0];
        }
    }
    return closestClass == lineData[0];
}

int main(int argc, char *argv[])
{

    vector<vector<float>> trainingData;

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
        while (iss >> word)
        {
            lineData.push_back(stof(word.substr(word.find(":") + 1)));
        }
        trainingData.emplace_back(std::begin(lineData), std::end(lineData));
    }

    trainingFile.close();

    std::ifstream testFile(argv[2]);

    int all = 0;
    int correct = 0;
    while (std::getline(testFile, line))
    {
        vector<float> lineData;
        stringstream iss(line);
        // int i = 0;
        iss >> word;
        lineData.push_back(stof(word));
        while (iss >> word)
        {
            lineData.push_back(stof(word.substr(word.find(":") + 1)));
        }
        if (findClass(lineData, trainingData))
            ++correct;
        ;
        ++all;
        // break;
    }
    cout << correct / all << endl;
}