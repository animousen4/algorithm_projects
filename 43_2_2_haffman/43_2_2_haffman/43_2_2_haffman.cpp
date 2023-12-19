// 43_2_2_haffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>



using namespace std;

int main()
{
    const long long avgMax = 1e18;
    long long res = 0;
    long long* firstArr;
    long long* secondArr;
    int pointerFirst = 0;
    int pointerSecond = 0;
    int secondSize = 0;
    int firstSize;
    int leftElements;
    ifstream inputFile("huffman.in");

    inputFile >> firstSize;
    leftElements = firstSize - 1;
    firstArr = new long long[firstSize + 7];
    secondArr = new long long[firstSize + 7];

    for (int i = firstSize; i < firstSize + 7; i++) {
        firstArr[i] = avgMax;
        secondArr[i] = avgMax;
    }
    for (int i = 0; i < firstSize; i++) {
        inputFile >> firstArr[i];
        secondArr[i] = avgMax;
    }

    inputFile.close();

    secondArr[0] = firstArr[0] + firstArr[1];

    pointerFirst = 2;
    pointerSecond = 0;
    secondSize = 1;
    

    long long s1;
    long long s2;
    long long s3;
    long long totalSum = 0;
    long long minElement;
    int operType = 0;
    while (true) {

        s1 = firstArr[pointerFirst] + firstArr[pointerFirst + 1];

        s2 = secondArr[pointerSecond] + firstArr[pointerFirst];
        
        s3 = secondArr[pointerSecond] + secondArr[pointerSecond + 1];
        

        minElement = s1;
        operType = 1;

        if (s2 < minElement) {
            operType = 2;
            minElement = s2;
        }

        if (s3 < minElement) {
            operType = 3;
            minElement = s3;
        }

        if (minElement > avgMax)
            break;

        if (operType == 1) {
            pointerFirst += 2;
        }

        else
            if (operType == 2) {
                pointerFirst++;
                pointerSecond++;
            }
                else {
                    pointerSecond += 2;
                }

        secondArr[secondSize] = minElement;
        secondSize++;

    }


    for (int i = 0; i < secondSize; i++)
        totalSum += secondArr[i];

    ofstream outputFile("huffman.out");

    outputFile << totalSum;

    outputFile.close();


}
