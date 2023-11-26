// 0_6_HashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;
int m, c, n;
int leftKeys;
long long** table = nullptr;

int prob(long long key, int i) {
    int pos = ((key % m) + c * i) % m;
    if (table[pos] == nullptr)
        return pos;
    return prob(key, i + 1);
    
}

bool probFound(long long key, int i) {
    int pos = ((key % m) + c * i) % m;
    if (table[pos] == nullptr)
        return false;
    if (*table[pos] == key)
        return true;
    return probFound(key, i + 1);

}
bool hasEmptyContainers() {
    return leftKeys > 0;
}

int main()
{   
    ifstream inputFile("input.txt");
    inputFile >> m >> c >> n;
    leftKeys = m;
    
    table = new long long* [m];

    for (int i = 0; i < m; i++)
        table[i] = nullptr;

    long long key;
    for (int i = 0; i < n; i++) {
        inputFile >> key;

        if (!probFound(key, 0) && hasEmptyContainers()) {
            int toPut = prob(key, 0);
            table[toPut] = new long long(key);
            leftKeys--;
        }
    }

    inputFile.close();

    ofstream outputFile("output.txt");
    for (int i = 0; i < m; i++)
        if (table[i] == nullptr)
            outputFile << "-1 ";
        else
            outputFile << *table[i] << " ";

    outputFile.close();
}

