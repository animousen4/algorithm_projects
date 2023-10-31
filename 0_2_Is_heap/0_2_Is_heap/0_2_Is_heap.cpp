// 0_2_Is_heap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;
int main()
{   
    int* arr;
    int n;
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    inputFile >> n;

    arr = new int[n];

    for (int i = 0; i < n; i++)
        inputFile >> arr[i];
    inputFile.close();
    
    for (int i = 0; i < n; i++) {
        if (2*(i+1)-1 < n)
            if (arr[i] > arr[2 * (i+1)-1]) {
                outputFile << "NO";
                outputFile.close();
                return 0;
            }
        if (2*(i+1) < n)
            if (arr[i] > arr[2 * (i+1)]) {
                outputFile << "NO";
                outputFile.close();
                return 0;
            }
    }

    outputFile << "YES";
    outputFile.close();
}
