#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

map<char, char> convertVoc = {
    {'I', '1'}, {'J', '1'},
    {'A', '2'}, {'B', '2'}, {'C', '2'},
    {'D', '3'}, {'E', '3'}, {'F', '3'},
    {'G', '4'}, {'H', '4'},
    {'K', '5'}, {'L', '5'},
    {'M', '6'}, {'N', '6'},
    {'P', '7'}, {'R', '7'}, {'S', '7'},
    {'T', '8'}, {'U', '8'}, {'V', '8'},
    {'W', '9'}, {'X', '9'}, {'Y', '9'},
    {'O', '0'}, {'Q', '0'}, {'Z', '0'},
};

vector<string> getNu­mVoc(vector<string> voc) {
    vector<string> numVoc(voc.size());
    char k;
    for (int i = 0; i < voc.size(); i++) {
        for (int j = 0; j < voc[i].size(); j++) {
            numVoc[i] += convertVoc[voc[i][j]];
        }
    }

    return numVoc;
}

string numToWord(string num, vector<string>& voc, vector<string>& numVoc) {
    auto f = find(numVoc.begin(), numVoc.end(), num);
    int index = f - numVoc.begin();
    return voc[index];
}

bool exists(string& number, vector<string>& numVoc, int i, int j) {
    auto subStr = number.substr(i, j - i + 1);
    return find(numVoc.begin(), numVoc.end(), subStr) != numVoc.end();
}

void printV(vector<string>& v) {
    for (auto c : v)
        cout << c << " ";
}

void printD(string& number, int* s, int& numberSize) {
    system("cls");
    for (char t : number)
        cout << t << "\t";
    cout << endl;
    for (int i = 0; i < numberSize + 1; i++)
        cout << s[i] << "\t";
}
int main()
{

    string number;
    int numberSize;

    vector<string> vocabulary;
    int vocabulary­Size;
    int* s;

    ifstream input­File("in.txt");
    ofstream outputFile("out.txt");

    input­File >> number >> vocabulary­Size;

    numberSize = number.size();

    vocabulary.resize(vocabulary­Size);

    for (int i = 0; i < vocabulary­Size; i++)
        input­File >> vocabulary[i];

    input­File.close();

    auto translate­dVocabulary = getNu­mVoc(vocabulary);

    s = new int[numberSize + 1];

    s[numberSize] = 0;


    int m;
    int mV;
    for (int i = numberSize - 1; i >= 0; i--) {
        mV = INT_MAX;
        for (int j = i; j < numberSize; j++) {
            if (exists(number, translate­dVocabulary, i, j)) {
                if (s[j + 1] >= 0 && mV > s[j + 1]) {
                    m = j - i + 1;
                    mV = s[i + m];
                }
            }
               
        }
        if (mV == INT_MAX)
            s[i] = INT_MIN;
        else
            s[i] = 1 + s[i + m];
        printD(number, s, numberSize);
    }

    int wordsAmount = s[0];

    if (wordsAmount < 0) {
        outputFile << "No solution";
        outputFile.close();
        return 0;
    }
    vector<string> numWords;

    int cur = wordsAmount;
    int pPos = 0;

    int latestIndex = 0;
    int mb = 0;
    while(pPos < numberSize) {
        for (int j = pPos; j <= numberSize; j++) {
            if (s[j] == cur - 1 && exists(number, translate­dVocabulary, pPos, j - 1)) {
                latestIndex = j;
                break; //!
            }
        }

        cur--;
        numWords.push_back(number.substr(pPos, latestIndex - pPos));
        pPos = latestIndex;
    }

    outputFile << wordsAmount << "\n";

    for (int i = 0; i < wordsAmount; i++) {
        outputFile << numToWord(numWords[i], vocabulary, translate­dVocabulary);
        if (i < wordsAmount - 1) {
            outputFile << " ";
        }
    }

    outputFile.close();
    return 0;


}
