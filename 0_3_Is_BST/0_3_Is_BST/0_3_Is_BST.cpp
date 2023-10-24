// 0_3_Is_BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;

void markError() {
    ofstream outputFile("bst.out");
    outputFile << "NO";
    outputFile.close();
}

void markOk() {
    ofstream outputFile("bst.out");
    outputFile << "YES";
    outputFile.close();
}

struct NubmerRange {
    long long left;
    long long right;
    
    bool isInRange(int number) {
        return left < number && right > number;
    }
};
int main()
{   

    int amount;
    int root;

    int* element;
    bool* side;
    int* link;
    NubmerRange* allowedRange;

    ifstream inputFile("bst.in");

    inputFile >> amount >> root;

    element = new int[amount];
    element[0] = root;
    
    link = new int[amount];
    link[0] = -1;

    allowedRange = new NubmerRange[amount];
    allowedRange[0] = { LLONG_MIN, LLONG_MAX };

    char s;
    int parentLink;
    for (int i = 1; i < amount; i++) {
        inputFile >> element[i] >> link[i] >> s;
        parentLink = link[i] - 1;

        if (s == 'R') { // R
            allowedRange[i] = { element[parentLink] - 1, allowedRange[parentLink].right};
        }
        else { // L
            allowedRange[i] = { allowedRange[parentLink].left, element[parentLink] };
        }

        if (!allowedRange[i].isInRange(element[i])) {
            markError();
            return 0;
        }
    }

    markOk();

    return 0;
}
