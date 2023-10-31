
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    long long n;
    vector<long long> powers;
    long long curPow = 0;

    inputFile >> n;

    inputFile.close();

    // 1 1 0 1 = 1*2^3 + 1*2^2 + 0*2^1 + 1*2^0 = 13
    while (n != 0) {
        if (n % 2 > 0)
            powers.push_back(curPow);
        n /= 2;
        curPow++;
    }

    if (powers.size() == 0) {
        outputFile << -1;
        outputFile.close();
        return 0;
    }

    for (int i = 0; i < powers.size(); i++) {
        outputFile << powers[i];
        if (i < powers.size() - 1) {
            outputFile << "\n";
        }
    }

    outputFile.close();
    
    
    
    return 0;
}
