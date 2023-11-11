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

        selfPointers = n;

        initArray();
    }

    int findSet(int el) {
        if (parents[el] == el)
            return el;
        else
            findSet(parents[el]);
    }

    void makeUnion(int a, int b) {
        int bSource = findSet(b);
        int aSource = findSet(a);

        if (aSource != bSource) {
            selfPointers--;
        }
        
        weights[aSource] += bSource;
        parents[bSource] = aSource;

        
    }

    int getSelfPointer() {
        return selfPointers;
    }
    
private:
    int n;

    int selfPointers;

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
        pair.a--;
        pair.b--;
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
    ofstream outputFile("output.txt");
    inputFile >> n >> m >> q;

    roads = new CityPair[m];
    destroyedRoads = new int[q];

    for (int i = 0; i < m; i++) {
        inputFile >> roads[i];
    }

    for (int i = 0; i < q; i++) {
        inputFile >> destroyedRoads[i];
        destroyedRoads[i]--;
    }

    inputFile.close();

    DSU dsu(n);
    int i;

    string res = "";

    for (i = q - 1; i >= 0; i--) {
        dsu.makeUnion(roads[destroyedRoads[i]].a, roads[destroyedRoads[i]].b);

        res += "0";

        if (dsu.getSelfPointer() == 1)
            break;
    }

    for (; i > 0; i--) {
        res.insert(0, "1");
    }

    outputFile << res;

    outputFile.close();

    return 0;
}