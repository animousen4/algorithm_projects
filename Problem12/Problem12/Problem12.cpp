// Problem12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;



template<class T>
struct Node {

    struct Mark {
        int h = 0;
        int l = 0;
        int msl = 0;

        Node* mPrev = nullptr;
        Node* m = nullptr;
    };

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
struct Way {
    Node<T>* s = nullptr;
    Node<T>* f = nullptr;
    vector<Node<T>*> elements;

};
template<class T>
class Tree {
public:
    Tree() {
        root = new Node<T>;
    }
    Node<T>* root;
    vector<Node<T>*> maxMSLLinks;

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
void goReverse(Node<T>* n, vector<Node<T>*>& maxMSLLinks) {
    

    if (n != nullptr) {

        goReverse<T>(n->left, maxMSLLinks);
        goReverse<T>(n->right, maxMSLLinks);

        if (n->isLeaf()) {
            n->mark.l = 1;
            n->mark.h = 0;
            n->mark.msl = 0;
            n->mark.m = n;
        }
        else {
            // h >= 1;
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


                // do
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
         
        if (maxMSLLinks.size() > 0) {
            if (maxMSLLinks[0]->mark.msl < n->mark.msl) {
                maxMSLLinks.clear();
                maxMSLLinks.push_back(n);
            } else
                if (maxMSLLinks[0]->mark.msl == n->mark.msl) {
                    maxMSLLinks.push_back(n);
                }
                
            
        }
        else {
            maxMSLLinks.push_back(n);
        }
    }
}

template<class T>
void goForwardG(Node<T>* n, Way<T>& curWay) {
    // n != nullptr

    curWay.elements.push_back(n);

    if (n->hasLeft() && n->left->mark.h == n->mark.h - 1)
        goForwardG(n->left, curWay);
    else
        if (n->hasRight())
            goForwardG(n->right, curWay);
        else
            curWay.f = n;
}

template<class T>
void search(Node<T>* root, vector<Node<T>*>& maxMSLLinks) {

    // root

    if (maxMSLLinks[maxMSLLinks.size() - 1] == root) {
        Way<T> way;
        way.s = root;

        goForwardG(root, way);

        cout << "S: " << *way.s->element << "\nF: " << *way.f->element << "\n";
        for (Node<T>* el : way.elements) {
            cout << *el->element << " ";
        }
        // root wins;

    }

    /*for (auto el : maxMSLLinks) {
        cout << el->mark.msl << " ";
    }*/


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

    goReverse(tree.root, tree.maxMSLLinks);

    search(tree.root, tree.maxMSLLinks);

    goForward(tree.root);

    inputFile.close();
    outputFile.close();
}