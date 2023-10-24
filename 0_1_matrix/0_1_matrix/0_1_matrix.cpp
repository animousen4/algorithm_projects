#include <iostream>
#include <fstream>

using namespace std;

struct Matrix {
    int m;
    int n;

    friend ifstream& operator>>(ifstream& s, Matrix& matrix) {
        s >> matrix.m >> matrix.n;
        return s;
    }
};

int main()
{
    ifstream inputFile("input.txt");
    int amount;

    inputFile >> amount;

    Matrix* matrixChain = new Matrix[amount];
    int* matrixOp = new int[amount];

    for (int i = 0; i < amount; i++) {
        inputFile >> matrixChain[i];
        matrixOp[i] = matrixChain[i].m * matrixChain[i].n;
    }
    inputFile.close();
    
    int** dp = new int*[amount];
    for (int i = 0; i < amount; i++) {
        dp[i] = new int[amount];
        dp[i][i] = 0;
    }

    for (int i = 0; i < amount - 1; i++) {
        dp[i][i+1] = matrixChain[i].m * matrixChain[i].n * matrixChain[i+1].n;
    }

    int min = INT_MAX;
    int p;
    for (int j = 2; j < amount; j++) {
        for (int i = j - 1; i >= 0; i--) {
            min = INT_MAX;
            for (int b = i; b < j; b++) {
                p = dp[i][b] + dp[b + 1][j] + (matrixChain[i].m * matrixChain[b].n * matrixChain[j].n);
                if (p < min) {
                    min = p;
                }
            }

            dp[i][j] = min;   
            
        }
    }
    ofstream outputFile("output.txt");
    outputFile << dp[0][amount - 1];
    outputFile.close();
}

