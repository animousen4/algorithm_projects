// 0_5_Destroy_Road.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct DSU {
public:

    DSU(long long _n) {
        n = _n;
        parents = new long long[n];
        weights = new long long[n];
        selfPointers = n;

        initArray();
    }

    long long findSet(long long el) {
        if (parents[el] == el)
            return el;
        else {
            parents[el] = findSet(parents[el]);
            return parents[el];
        }
    }

    void makeUnion(long long a, long long b) {
        long long bSource = findSet(b);
        long long aSource = findSet(a);

        if (aSource != bSource) {
            if (weights[aSource] > weights[bSource]) {
                parents[bSource] = aSource;
                weights[aSource] += weights[bSource];
            }
            else {
                parents[aSource] = bSource;
                weights[bSource] += weights[aSource];
            }

            selfPointers--;

        }


    }

    long long getSelfPointer() {
        return selfPointers;
    }

private:
    long long n;

    long long selfPointers;

    long long* weights;
    long long* parents;

    void initArray() {
        for (long long i = 0; i < n; i++) {
            parents[i] = i;
            weights[i] = 1;
        }
    }
};

struct CityPair {
    long long a;
    long long b;

    friend istream& operator>>(istream& stream, CityPair& pair) {
        stream >> pair.a >> pair.b;
        pair.a--;
        pair.b--;
        return stream;
    }
};

int main()
{
    long long n;
    long long q;


    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    inputFile >> n >> q;

    DSU dsu(n);

    CityPair p;

    for (long long i = 0; i < q; i++) {
        inputFile >> p;
        dsu.makeUnion(p.a, p.b);
        outputFile << dsu.getSelfPointer() << endl;
    }

    inputFile.close();

    outputFile.close();

    return 0;
}