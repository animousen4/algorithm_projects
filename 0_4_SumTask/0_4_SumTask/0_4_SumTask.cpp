
// 0_4_SumTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
    int n = 0;
    int 
    long long* numbers = 0;
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


    scanf_s("%d", &commandsAmount);
    res = new long long[commandsAmount];

    for (int i = 0; i < commandsAmount; i++) {
        scanf_s("%s", temp, 9);
        scanf_s("%lld", &arg1);
        scanf_s("%lld", &arg2);

        command = temp;

        if (command == "FindSum") {
            sum = 0;
            for (int j = arg1; j < arg2; j++)
                sum += numbers[j];

            res[resSize] = sum;
            resSize++;
            
        }
        else {

            numbers[arg1] = numbers[arg1] + arg2;
        }
    }


    for (int i = 0; i < resSize; i++) {
        printf_s("%lld ", res[i]);
    }
    return 0;

}
