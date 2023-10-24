// 0_2_OneP1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{   

    int n;
    int k;
    
    int** arr;

    cin >> n >> k;
    n = n + 1;
    k = k + 1;
    arr = new int*[n];

    for (int i = 0; i < n; i++) {
        arr[i] = new int[k];
        arr[i][0] = 1;
        if (i < n && i < k) {
            arr[i][i] = 1;
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; i - j > 0; j++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }

    cout << arr[n-1][k-1];

    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    return 0;
    
}
