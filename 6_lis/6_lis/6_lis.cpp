// 6_lis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <vector>

using namespace std;
int getInsertionIndex(vector<int>& v, int num) {
    
    int q = 0;
    int r = v.size();
    int k;
    while (q < r) {
        k = (r + q) / 2;
        if (num <= v[k]) {
            r = k;
        }
        else {
            q = k + 1;
        }
    }

    return q;
    

}
int main()
{   

    ifstream inputFile("input.txt");

    int n;
    int* s;

    inputFile >> n;

    s = new int[n];
    for (int i = 0; i < n; i++) {
        inputFile >> s[i];
    }

    inputFile.close();

    vector<int> v;

    v.push_back(s[0]);
    int j;
    for (int i = 1; i < n; i++) {
        
        if (s[i] > v[v.size() - 1]) {
            v.push_back(s[i]);
            continue;
        }
        
        j = getInsertionIndex(v, s[i]);
        v[j] = s[i];
        
    }

    ofstream outputFile("output.txt");
    outputFile << v.size();
    outputFile.close();

}