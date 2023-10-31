// 43_2_haffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;

class MinHeap {
    int size;
    long long* elements;


public:
    MinHeap(int size, long long* elements) {
        this->size = size;
        this->elements = elements;
    }

    bool doubleExtractAllowed() {
        return size > 1;
    }

    bool extractAllowed() {
        return size > 0;
    }

    long long getMin() {
        return elements[0];
    }

    void removeMin() {
        elements[0] = elements[size - 1];
        size--;
        
        int i = 0;
        long long temp;
        int lowestIndex;
        while (true) {

            if (2 * i + 1 < size) {
                lowestIndex = 2 * i + 1;

                if (2 * i + 2 < size && elements[lowestIndex] > elements[2 * i + 2])
                    lowestIndex = 2 * i + 2;

                if (elements[lowestIndex] < elements[i]) {
                    temp = elements[lowestIndex];
                    elements[lowestIndex] = elements[i];
                    elements[i] = temp;

                    i = lowestIndex;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
            
        }

    }

    void insertElement(long long el) {
        size++;

        int i = size - 1;
        int divRes;
        long long temp;
        bool atPlace = false;
        elements[i] = el;
        while (i > 0 && !atPlace) {
            divRes = (i - 1) / 2;
            if (elements[divRes] > elements[i]) {
                temp = elements[divRes];

                elements[divRes] = elements[i];
                elements[i] = temp;

                i = divRes;
            }
            else {
                atPlace = true;
            }
        }
    }

    long long extractMin() {

        long long min = getMin();
        removeMin();

        return min;
    }

    void printHeap() {
        for (int i = 0; i < size; i++) {
            cout << elements[i] << " ";
        }
    }
};

int main()
{
    ifstream inputFile("huffman.in");
    int s;
    long long * arr;


    inputFile >> s;
    arr = new long long[s];

    for (int i = 0; i < s; i++)
        inputFile >> arr[i];

    MinHeap mHeap(s, arr);

    long long sum = 0;
    long long localSum;
        
    while (mHeap.doubleExtractAllowed()) {
        localSum = mHeap.extractMin() + mHeap.extractMin();
        mHeap.insertElement(localSum);

        sum += localSum;
    }
    
    ofstream outputFile("huffman.out");
    cout << sum;

    outputFile << sum;

    outputFile.close();

    return 0;
    
}
