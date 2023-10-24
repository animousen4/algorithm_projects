// 93_lcs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>


using namespace std;


int main()
{   
	int size;

	int* s1;
	int* s2;

	int** matrix;

	cin >> size;

	s1 = new int[size];
	s2 = new int[size];

	for (int i = 0; i < size; i++)
		cin >> s1[i];
	for (int i = 0; i < size; i++)
		cin >> s2[i];

	matrix = new int* [size + 1];
	for (int i = 0; i < size + 1; i++)
		matrix[i] = new int[size + 1];


	for (int i = 0; i < size + 1; i++) {
		matrix[0][i] = 0;
		matrix[i][0] = 0;
	}

	for (int j = 1; j < size + 1; j++) {
		for (int i = 1; i < size + 1; i++) {
			if (s1[i - 1] == s2[j - 1])
				matrix[i][j] = matrix[i - 1][j - 1] + 1;
			else
				if (matrix[i - 1][j] > matrix[i][j - 1])
					matrix[i][j] = matrix[i - 1][j];
				else
					matrix[i][j] = matrix[i][j - 1];
				
		}
	}
	int i = size;
	int j = size;

	
	int maxSubSize = matrix[size][size];

	int* w1 = new int[maxSubSize];
	int* w2 = new int[maxSubSize];

	int r = maxSubSize - 1;
	while (j > 0 && i > 0) {
		if (s1[i - 1] == s2[j - 1]) {
			w1[r] = i - 1;
			w2[r] = j - 1;
			r--;
			i--;
			j--;
		}
		else {
			if (matrix[i][j] == matrix[i - 1][j])
				i--;
			else
				j--;
		}
			
	}

	cout << maxSubSize << endl;

	for (int i = 0; i < maxSubSize; i++)
		cout << w1[i] << ((i == maxSubSize - 1) ? "" : " ");

	cout << endl;
	for (int i = 0; i < maxSubSize; i++)
		cout << w2[i] << ((i == maxSubSize - 1) ? "" : " ");

}
