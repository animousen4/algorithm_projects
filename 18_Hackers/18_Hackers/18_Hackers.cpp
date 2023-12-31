// 18_Hackers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Mark {
    int v = -1;
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
    vector<int> vParent(n);
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


    for (int i = 0; i < n; i++)
        if (!marks[i].isGray()) {
            dfs1(i, listSm);
        }

    vector<Mark> sortedMarks(n);
    for (int i = 0; i < n; i++) {
        sortedMarks[i] = marks[i];
        sortedMarks[i].v = i;
    }

    std::sort(sortedMarks.begin(), sortedMarks.end(), [](Mark& s1, Mark& s2) {
        return s1.s > s2.s;
    });


    cout << endl;
    vector<int> vv;
    vector<int> components;
    vector<vector<int>> componentsContainer;
    int minTerminalAmount;
    int minTerminalIndex;
    int curComp = 0;
    for (int i = 0; i < n; i++)
        if (!marks[sortedMarks[i].v].dS) {
            vv.clear();
            dfs2(sortedMarks[i].v, reverseListSm, vv);

            minTerminalAmount = INT_MAX;
            for (auto versh : vv) {
                if (minTerminalAmount > terminal[versh]) {
                    minTerminalIndex = versh;
                    minTerminalAmount = terminal[versh];
                }
                vParent[versh] = curComp;
            }
            
            curComp++;
            components.push_back(minTerminalIndex);
            componentsContainer.push_back(vv);
        }
    vector<vector<int>> nGraphSp(components.size());
    vector<int> inDougs(components.size());
    int amountC = components.size();
    for (int i = 0; i < componentsContainer.size(); i++) {
        for (int j = 0; j < componentsContainer[i].size(); j++) {
            for (int mm = 0; mm < listSm[componentsContainer[i][j]].size(); mm++) {
                if (vParent[listSm[componentsContainer[i][j]][mm]] != vParent[componentsContainer[i][j]]) {
                    if (!inDougs[vParent[listSm[componentsContainer[i][j]][mm]]]) {
                        inDougs[vParent[listSm[componentsContainer[i][j]][mm]]] = true;
                        amountC--;
                    }
                }
            }
            //cout << componentsContainer[i][j] + 1 << " ";
        }
            
        //cout << endl;
    }

    ofstream outputFile("output.txt");
    outputFile << amountC << endl;
    for (int i = 0; i < components.size(); i++) {
        if (!inDougs[i])
            outputFile << components[i] + 1 << " ";
    }

    outputFile.close();

}
