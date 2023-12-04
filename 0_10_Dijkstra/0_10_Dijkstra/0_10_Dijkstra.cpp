// 0_10_Dijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int main()
{   
    int n;
    int m;
    int** arr;
    int* d;
    bool* p;
    priority_queue<pair<int, int>, vector<pair<int, int>, greater<pair<int, int>>>> pq;
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

    pq.push(make_pair(start, 0));
    for (int i = 1; i <= m; i++) {
        arr[i] = new int[3];

        inputFile >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }


    while (!pq.empty()) {
        auto v = pq.top();
        pq.pop();
        if (p[v.first])
            continue;
        p[v.first] = true;
        d[v.first] = v.second;

        for (int i = 0; i < m; i++) {
            if (!p[arr[i][1]])
                pq.push(make_pair(arr[i][1], arr[i][2] + v.second));
        }
    }
}
