// 18_Hackers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main()
{
    int n;
    int* terminal;
    vector<int>* listSm;


    ifstream inputFile("input.txt");

    inputFile >> n;
    terminal = new int[n];
    listSm = new vector<int>[n];
    for (int i = 0; i < n; i++)
        inputFile >> terminal[i];

    int a, b;
    int k = 0;
    while(true) {
        inputFile >> a >> b;
        if (a == 0 && b == 0)
            break;
        listSm[a - 1].push_back(b - 1);
        k++;
    }

    
        

}
