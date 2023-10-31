// Problem12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


struct Mark {
    int h = 0;
    int l = 0;
    int msl = 0;
};
template<class T>
struct Node {
    T* element = nullptr;

    Node* left = nullptr;
    Node* right = nullptr;

    Mark mark;

    bool hasLeft() {
        return left != nullptr;
    }

    bool hasRight() {
        return right != nullptr;
    }

    bool hasBoth() {
        return hasRight() && hasLeft();
    }

    bool isLeaf() {
        return !hasLeft() && !hasRight();
    }

    void pushElement(T el) {
        if (element == nullptr) {
            element = new T(el);
        }
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

template<class T>
class Tree {
public:
    Tree() {
        root = new Node<T>;
    }
    Node<T>* root;

    friend istream& operator >> (istream& in, Tree& tree) {
        T element;
        in >> element;
        tree.root->pushElement(element);
        return in;
    }

};

ofstream outputFile;
int elementAmount = 0;
int curElement = 0;
template<class T>
void goForward(Node<T>* n) {
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


template<class T>
void goReverse(Node<T>* n) {
    if (n != nullptr) {
        
        goReverse(n->left);
        goReverse(n->right);
        
        if (n->isLeaf()) {
            n->mark.l = 1;
            n->mark.h = 0;
            n->mark.msl = 0;
        }
        else {
            if (n->hasBoth()) {
                n->mark.h = max(n->right->mark.h, n->left->mark.h) + 1;
                n->mark.msl += n->right->mark.h + n->left->mark.msl + 2;
                if (n->right->mark.h == n->left->mark.h)
                    n->mark.l = n->right->mark.l + n->left->mark.l;
                else
                    if (n->right->mark.h > n->left->mark.h)
                        n->mark.l = n->right->mark.l;
                    else
                        n->mark.l = n->left->mark.l;
            }
            else {
                if (n->hasLeft()) {
                    n->mark.l = n->left->mark.l;
                    n->mark.h = n->left->mark.h + 1;
                }
                else {
                    n->mark.l = n->right->mark.l;
                    n->mark.h = n->right->mark.h + 1;
                }

                n->mark.msl = n->mark.h;
            }
        }

        
                        
          
    }
}

int main()
{
    ifstream inputFile("input.txt");

    Tree<int> tree;
    while (!(inputFile.peek() == EOF)) {
        inputFile >> tree;
        elementAmount++;
    }

    outputFile.open("output.txt");

    goReverse(tree.root);

    goForward(tree.root);

    cout << tree.root->right->mark.msl;

    inputFile.close();
    outputFile.close();
}