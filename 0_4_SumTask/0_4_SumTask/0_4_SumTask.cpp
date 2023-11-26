
// 0_4_SumTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
long long getSumInArray(long long* arr, int l, int r) {
    long long sum = 0;
    for (int i = l; i < r; i++)
        sum += arr[i];
    return sum;
}

int main()
{
    int n = 0;
    int 
    long long* numbers;
    long long* presumBlocs;
    int blocsAmount = 0;
    int commandsAmount = 0;

    int resSize = 0;
    long long* res;

    
    char temp[10];

    string command;
    long long arg1 = 0;
    long long arg2 = 0;
    long long sum = 0;
    scanf_s("%d", &n);
    numbers = new long long[n];
    for (int i = 0; i < n; i++) {
        scanf_s("%lld", &numbers[i]);
    }

    int k = sqrt(n);

    blocsAmount = ceil(n / (double)k);
    presumBlocs = new long long[blocsAmount];
    for (int i = 0; i < blocsAmount - 1; i++) {
        presumBlocs[i] = 0;
        for (int j = i*k; j < (i+1)*k; j++)
            presumBlocs[i] += numbers[j];
    }

    
    presumBlocs[blocsAmount - 1] = 0;
    for (int i = (blocsAmount - 1) * k; i < n; i++)
        presumBlocs[blocsAmount - 1] += numbers[i];

    scanf_s("%d", &commandsAmount);
    res = new long long[commandsAmount];

    for (int i = 0; i < commandsAmount; i++) {
        scanf_s("%s", temp, 9);
        scanf_s("%lld", &arg1);
        scanf_s("%lld", &arg2);

        command = temp;

        if (command == "FindSum") {
            sum = 0;

            int leftBorderBloc = arg1 / k;
            int rightBorderBlock = arg2 / k;

            if (leftBorderBloc == rightBorderBlock)
                sum = getSumInArray(numbers, arg1, arg2);
            else {
                sum += getSumInArray(numbers, arg1, (leftBorderBloc + 1) * k);
                sum += getSumInArray(presumBlocs, (leftBorderBloc + 1), rightBorderBlock);
                sum += getSumInArray(numbers, rightBorderBlock * k, arg2);
            }

            res[resSize] = sum;
            resSize++;
            
        }
        else {

            numbers[arg1] += arg2;
            presumBlocs[arg1 / k] += arg2;
        }
    }


    for (int i = 0; i < resSize; i++) {
        printf_s("%lld ", res[i]);
    }
    return 0;

}
