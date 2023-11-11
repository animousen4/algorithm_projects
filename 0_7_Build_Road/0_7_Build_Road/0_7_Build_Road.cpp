// 0_5_Destroy_Road.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct DSU {
public:

    DSU(int _n) {
        n = _n;
        parents = new int[n];

        selfPointers = n;

        initArray();
    }

    int findSet(int el) {
        if (parents[el] == el)
            return el;
        else {
            parents[el] = findSet(parents[el]);
            return parents[el];
        }
    }

    void makeUnion(int a, int b) {
        int bSource = findSet(b);
        int aSource = findSet(a);

        if (aSource != bSource) {
            selfPointers--;

            parents[bSource] = aSource;
        }


    }

    int getSelfPointer() {
        return selfPointers;
    }

private:
    int n;

    int selfPointers;

    int* parents;

    void initArray() {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
    }
};

struct CityPair {
    int a;
    int b;

    friend istream& operator>>(istream& stream, CityPair& pair) {
        stream >> pair.a >> pair.b;
        pair.a--;
        pair.b--;
        return stream;
    }
};

int main()
{
    int n;
    int q;


    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    inputFile >> n >> q;

    DSU dsu(n);

    CityPair p;

    for (int i = 0; i < q; i++) {
        inputFile >> p;
        dsu.makeUnion(p.a, p.b);
        outputFile << dsu.getSelfPointer() << endl;
    }

    inputFile.close();

    outputFile.close();

    return 0;
}