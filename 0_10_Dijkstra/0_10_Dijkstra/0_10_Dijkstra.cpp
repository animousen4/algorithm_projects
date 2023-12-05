// 0_10_Dijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Element {

    Element(long long x, long long y) {
        el = x;
        prior = y;
    }

    long long el;
    long long prior;
};

class PComparator {
public:
    bool operator() (const Element& a, const Element& b) const {
        return a.prior > b.prior;
    }
};

int main()
{   
    int n;
    int m;
    long long* d;
    bool* p;
    priority_queue<Element, vector<Element>, PComparator> pq;
    ifstream inputFile("input.txt");

    inputFile >> n >> m;

    int start = 1;
    int end = n;

    d = new long long[n + 1];
    p = new bool[n + 1];

    for (int i = 1; i <= n; i++) {
        d[i] = LLONG_MAX;
        p[i] = false;
    }
    vector<vector<Element>> matrix(n + 1);

    int a, b, w;

    for (int i = 1; i <= m; i++) {
        inputFile >> a >> b >> w;

        Element newNeighbour(b, w);

        matrix[a].push_back(newNeighbour);

        newNeighbour.el = a;

        matrix[b].push_back(newNeighbour);
    }

    d[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        auto v = pq.top();
        pq.pop();

        long long curV = v.el;
        long long curD = v.prior;

        if (!p[v.el]) {
            
            p[curV] = true;
            d[curV] = curD;

            for (int i = 0; i < matrix[v.el].size(); i++) {

                long long nextNeighbour = matrix[v.el][i].el;
                long long nextNeighbourDist = matrix[v.el][i].prior;

                if (!p[nextNeighbour] && (curD + nextNeighbourDist < d[nextNeighbour]))
                    pq.push({ nextNeighbour,  curD + nextNeighbourDist });
            }
        }
    }

    ofstream outputFile("output.txt");
    outputFile << d[n];
}
