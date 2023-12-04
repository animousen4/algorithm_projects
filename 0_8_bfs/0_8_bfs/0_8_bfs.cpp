// 0_8_bfs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int main()
{   

    queue<int> q;
    ifstream inputFile("input.txt");
    int n;
    int** arr;
    int* m;
    queue<int> v;
    int globalIndex = 1;
    inputFile >> n;

    arr = new int* [n];
    m = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++) {
            inputFile >> arr[i][j];
        }
    }

    for (int i = 0; i < n; i++)
        m[i] = -1;
    
    for (int i = 0; i < n; i++) {
        if (m[i] < 0) {

                m[i] = globalIndex;
                globalIndex++;

                for (int j = 0; j < n; j++) {
                    if (arr[i][j] == 1 && m[j] < 0) {
                        v.push(j);
                        m[j] = globalIndex;
                        globalIndex++;
                    }
                }
                while (!v.empty()) {
                    int k = v.front();
                    v.pop();

                    for (int bb = 0; bb < n; bb++) {
                        if (arr[k][bb] == 1 && m[bb] < 0) {
                            v.push(bb);
                            m[bb] = globalIndex;
                            globalIndex++;
                        }
                    }
                }
        }
    }
    ofstream outputFile("output.txt");
    for (int i = 0; i < n; i++)
        outputFile << m[i] << " ";


}
