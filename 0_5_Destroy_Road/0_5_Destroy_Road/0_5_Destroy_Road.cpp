// 0_5_Destroy_Road.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

struct DSU {
public:

    DSU(int _n) {
        n = _n;
        parents = new int[n];
        weights = new int[n];

        initArray();
    }

    int findSet(int el) {
        return parents[el];
    }

    void makeUnion(int a, int b) {
        if (parents[a] != a && parents[b] != b) {
            parents[b] = a;
            weights[a]++;
        } else 
            if (parents[a] != a) {
                parents[]
            }
    }
    
private:
    int n;

    int* parents;
    int* weights;

    void initArray() {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
            weights[i] = 1;
        }
    }
};

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

    for (int i = 0; i < q; i++) {
        
    }
}