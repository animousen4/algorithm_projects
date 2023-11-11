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

            //weights[aSource] += bSource;
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
    int m;
    int q;

    CityPair* roads;
    int* destroyedRoads;
    bool* staticRoad;

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    inputFile >> n >> m >> q;

    roads = new CityPair[m];
    staticRoad = new bool[m];
    destroyedRoads = new int[q];

    for (int i = 0; i < m; i++) {
        inputFile >> roads[i];
        staticRoad[i] = true;
    }

    for (int i = 0; i < q; i++) {
        inputFile >> destroyedRoads[i];
        destroyedRoads[i]--;

        staticRoad[destroyedRoads[i]] = false;
    }

    inputFile.close();

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        if (staticRoad[i]) {
            dsu.makeUnion(roads[i].a, roads[i].b);
        }
    }

    int i;

    string res = "";

    for (i = q - 1; i >= 0; i--) {
        dsu.makeUnion(roads[destroyedRoads[i]].a, roads[destroyedRoads[i]].b);

        res += "0";

        if (dsu.getSelfPointer() == 1) {
            i--;
            break;

        }
        
    }

    for (; i >= 0; i--) {
        res.insert(0, "1");
    }

    outputFile << res;
    outputFile.close();

    return 0;
}