// 69_2_WayOfJaba.cpp : Defines the entry point for the application.
//

#include "69_2_WayOfJaba.h"

#include <iostream>
#include <vector>
using namespace std;

int main()
{	

	int n;
	int* inpArr;
	int* komar;
	vector<int> jabaWay;

	cin >> n;

	inpArr = new int[n];
	komar = new int[n];

	for (int i = 0; i < n; i++)
		cin >> inpArr[i];

	if (n == 1) {
		cout << inpArr[0] << endl << 1;
		return 0;
	}
	if (n < 3) {
		cout << -1;
		return 0;
	}

	komar[0] = inpArr[0];
	komar[1] = INT_MIN;
	komar[2] = komar[0] + inpArr[2]; // !

	for (int i = 3; i < n; i++) {
		int n2 = komar[i - 2] + inpArr[i];
		int n3 = komar[i - 3] + inpArr[i];
		if (n3 >= n2) {
			komar[i] = n3;
		}
		else {
			komar[i] = n2;
		}
	}

	cout << komar[n-1] << endl;

	int i = n - 1;

	jabaWay.push_back(i + 1);

	while (i > 0) {
		int p = komar[i] - inpArr[i];
		if (p == komar[i - 3]) {
			i = i - 3;
		}
		else {
			i = i - 2;
		}

		jabaWay.push_back(i + 1);

	}

	for (int i = jabaWay.size() - 1; i > 0; i--)
		cout << jabaWay[i] << " ";
	cout << jabaWay[0];
	return 0;
}
