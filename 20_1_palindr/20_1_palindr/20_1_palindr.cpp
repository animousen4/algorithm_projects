// 20_1_palindr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{   
    ifstream inputFile("input.txt");

    ofstream outputFile("output.txt");

    string s;
    int size;
    int** arr;

    inputFile >> s;

    inputFile.close();

    size = strlen(s.c_str());

    if (size == 1) {
        outputFile << size << "\n" << s;
        outputFile.close();
        return 0;
    }

    arr = new int*[size];

    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];

        for (int j = 0; j < size; j++)
            arr[i][j] = 0;
        arr[i][i] = 1;
        if (i < size - 1)
            if (s[i] == s[i + 1])
                arr[i][i + 1] = 2;
            else
                arr[i][i + 1] = 1;
    }

    for (int j = 2; j < size; j++) {
        for (int i = j - 2; i >= 0; i--) {
            if (s[i] == s[j])
                arr[i][j] = arr[i + 1][j - 1] + 2;
            else
                arr[i][j] = max(arr[i + 1][j], arr[i][j - 1]);
        }
    }

    int pLen = arr[0][size - 1];
    int toCount = pLen / 2 + ((pLen % 2 == 0) ? 0 : 1);

    char* res = new char[pLen];
    int saveIter = 0;
    int i = 0;
    int j = size - 1;
    while (saveIter < toCount) {
        if (s[i] == s[j]) {
            res[saveIter] = s[i];
            saveIter++;
            i++;
            j--;
        }
        else
            if (arr[i + 1][j] > arr[i][j - 1])
                i++;
            else
                j--;
        
    }

    i = 0;
    string outString;
    string revString;
    while (i < saveIter) {
        outString += res[i];
        revString.insert(0, 1, res[i]);
            i++;
    }


    if (pLen % 2 != 0)
        revString.erase(0, 1);
    
    outString += revString;

    outputFile << pLen << "\n" << outString;

    outputFile.close();
}
