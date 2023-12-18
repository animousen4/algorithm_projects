// 43_2_2_haffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    long long res = 0;
    long long* inArr;
    long long* extraArr;
    int pointerFirst = 0;
    int pointerSecond = 0;
    int secondSize = 0;
    int n;
    int leftElements;
    ifstream inputFile("huffman.in");

    inputFile >> n;
    leftElements = n - 1;
    inArr = new long long[n];
    extraArr = new long long[n];
    for (int i = 0; i < n; i++) {
        inputFile >> inArr[i];
        extraArr[i] = LONG_MIN;
    }

    inputFile.close();

    pointerFirst += 2;
    secondSize += 1;
    
    extraArr[0] = inArr[0] + inArr[1];

    long long s1;
    long long s2;
    long long s3;
    long long totalSum = extraArr[0];
    long long min;
    int operType = 0;
    while (leftElements != 1) {
        s1 = LONG_MAX;
        s2 = LONG_MAX;
        s3 = LONG_MAX;


        if (pointerFirst + 1 < n)
            s1 = inArr[pointerFirst] + inArr[pointerFirst + 1];
        if (pointerSecond < secondSize && pointerFirst < n)
            s2 = extraArr[pointerSecond] + inArr[pointerFirst];
        if (pointerSecond + 1 < secondSize)
            s3 = extraArr[pointerSecond] + extraArr[pointerSecond + 1];
        

        min = s1;
        operType = 1;

        if (s2 < min) {
            operType = 2;
            min = s2;
        }

        if (s3 < min) {
            operType = 3;
            min = s3;
        }

        if (operType == 1) {
            pointerFirst += 2;
            extraArr[secondSize] = min;
            secondSize++;
        }
        else
            if (operType == 2) {
                pointerFirst++;
                pointerSecond++;
                extraArr[secondSize] = min;
                secondSize++;
            }
                else {
                    pointerSecond += 2;
                    extraArr[secondSize] = min;
                    secondSize++;
                
                }

        totalSum += min;
        leftElements--;

    }

    ofstream outputFile("huffman.out");

    outputFile << totalSum;

    outputFile.close();


}
