// 0_10_Dijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Element {
    int el;
    int prior;
};


class PComparator {
public:
    bool operator() (const Element& a, const Element& b) const {
        return a.prior < b.prior;
    }
};

int main()
{   
    int n;
    int m;
    int** arr;
    int* d;
    bool* p;
    priority_queue<Element, vector<Element>, PComparator> pq;
    ifstream inputFile("input.txt");

    inputFile >> n >> m;

    int start = 1;
    int end = n;

    arr = new int*[m + 1];
    d = new int[n + 1];
    p = new bool[n + 1];

    for (int i = 1; i <= n; i++) {
        d[i] = INT_MAX;
        p[i] = false;
    }

    d[start] = 0;

    pq.push({start, 0});
    for (int i = 1; i <= m; i++) {
        arr[i] = new int[3];

        inputFile >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }


    while (!pq.empty()) {
        auto v = pq.top();
        pq.pop();

        if (!p[v.el]) {
            
            p[v.el] = true;
            d[v.el] = v.prior;

            for (int i = 1; i <= m; i++) {
                if (!p[arr[i][1]] && (v.prior + arr[i][2] < d[arr[i][1]]))
                    pq.push({ arr[i][1], arr[i][2] + v.prior });
            }
        }
    }

    ofstream outputFile("output.txt");
    outputFile << d[n];
}
