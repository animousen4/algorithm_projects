// 0_5_Destroy_Road.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

struct CityPair {
    int a;
    int b;

    friend istream& operator>>(istream& stream, CityPair& pair) {
        stream >> pair.a >> pair.b;
        return stream;
    }
};

int main()
{
    int n;
    int m;
    int q;

    CityPair* roads;
    int* destroyedRoads;

    ifstream inputFile("input.txt");
    inputFile >> n >> m >> q;

    roads = new CityPair[m];
    destroyedRoads = new int[q];

    for (int i = 0; i < m; i++) {
        inputFile >> roads[i];
    }

    for (int i = 0; i < q; i++) {
        inputFile >> destroyedRoads[i];
    }

    inputFile.close();


}