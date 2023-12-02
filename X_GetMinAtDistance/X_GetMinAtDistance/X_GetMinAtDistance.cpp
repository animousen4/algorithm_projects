// X_GetMinAtDistance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int getMinAtArray(int* p, int l, int r) {
    int min = p[l];
    for (int i = l + 1; i < r; i++)
        if (p[i] < min)
            min = p[i];

    return min;
}

void modifyMin() {

}
int main()
{
    int* arr = new int[3];
    arr[0] = 4;
    arr[1] = 3;
    arr[2] = 2;

    cout << getMinAtArray(arr, 0, 2);
}
