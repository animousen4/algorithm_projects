// 0_1_Build_tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;


struct Node {
    int* element = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    void pushElement(int el) {
        if (element == nullptr)
            element = new int(el);
        else
            if (el == *element)
                return;
            else
            if (el < *element) {
                if (left == nullptr)
                    left = new Node;
                left->pushElement(el);
            }
            else {
                if (right == nullptr)
                    right = new Node;
                right->pushElement(el);
            }

    }

};

class Tree {
public:
    Tree() {
        root = new Node;
    }
    Node* root;

    friend istream& operator >> (istream& in, Tree& tree) {
        int element;
        in >> element;
        tree.root->pushElement(element);
        return in;
    }

};

ofstream outputFile;
int elementAmount = 0;
int curElement = 0;
void goForward(Node* n) {
    if (n != nullptr) {
        curElement++;
        outputFile << *n->element;
        if (curElement != elementAmount) {
            outputFile << "\n";
        }
        goForward(n->left);
        goForward(n->right);
    }

}

int main()
{
    ifstream inputFile("input.txt");
    
    Tree tree;
    while (!(inputFile.peek() == EOF)) {
        inputFile >> tree;
        elementAmount++;
    }

    outputFile.open("output.txt");
    outputFile << elementAmount << "\n\n";
    goForward(tree.root);

    inputFile.close();
    outputFile.close();
}