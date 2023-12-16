// 18_Hackers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct Mark {
    int f = -1;
    int s = -1;
    bool dS = false;
    bool notVisitedF() {
        return f == -1;
    }

    bool notVisitedS() {
        return s == -1;
    }

    bool isBlack() {
        return s != -1;
    }

    bool isGray() {
        return f != -1;
    }

    bool pushMark(int m) {
        if (notVisitedF()) {
            f = m;
            return true;
        }
        else
            if (notVisitedS()) {
                s = m;
                return true;
            }
        return false;
    }

    bool bothVisited() {
        return !notVisitedF() && !notVisitedS();
    }
};

Mark* marks;
int globalMark = 1;
void dfs1(int i, vector<vector<int>>& listSm) {

    marks[i].f = globalMark;
    globalMark++;

    for (int j = 0; j < listSm[i].size(); j++)
        if (!marks[listSm[i][j]].isGray())
            dfs1(listSm[i][j], listSm);
    marks[i].s = globalMark;
    globalMark++;

}

void dfs2(int i, vector<vector<int>>& listSm, vector<int>& visited) {

    marks[i].dS = true;
    visited.push_back(i);

    for (int j = 0; j < listSm[i].size(); j++)
        if (!marks[listSm[i][j]].dS)
            dfs2(listSm[i][j], listSm, visited);

}
int main()
{
    int n;
    
    


    ifstream inputFile("input.txt");

    inputFile >> n;
    vector<int> terminal(n);
    vector<vector<int>> listSm(n);
    vector<vector<int>> reverseListSm(n);
    marks = new Mark[n];
    for (int i = 0; i < n; i++)
        inputFile >> terminal[i];

    int a, b;
    int k = 0;
    while(true) {
        inputFile >> a >> b;
        if (a == 0 && b == 0)
            break;
        listSm[a - 1].push_back(b - 1);
        reverseListSm[b - 1].push_back(a - 1);
        k++;
    }

    inputFile.close();

    /*bool haveCondensation = true;

    while (haveCondensation) {
        
    }*/

    for (int i = 0; i < n; i++)
        if (!marks[i].isGray()) {
            dfs1(i, listSm);
        }

    vector<int> vv;
    for (int i = 0; i < n; i++)
        if (!marks[i].dS) {
            vv.clear();
            dfs2(i, reverseListSm, vv);
            for (auto versh : vv)
                cout << versh + 1 << "\t";
            cout << endl;
        }
   /* for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << marks[i].f << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << marks[i].s << "\t";
    }*/
    
        

}
