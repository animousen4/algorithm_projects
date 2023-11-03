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

    Node* getPriorityChild() {
        // only if has at least 1 child
        if (hasBoth()) {
            if (left->mark.h >= right->mark.h)
                return left;
            else
                return right;
        }
        else {
            if (hasLeft()) {
                return left;
            } else {
                return right;
            }
        }
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
template<class T> struct PointPair
{
    Node<T>* a;
    Node<T>* b;

    Node<T>* localRoot;
    //static PointPair& minRoot(PointPair& p1, PointPair& p2) {
    //    
    //}
    T getSum() {
        return *a->element + *b->element;
    }

    bool operator<(PointPair<T>& o2) {
        return getSum() < o2.getSum();
    }

    bool operator==(PointPair<T>& o2) {
        return getSum() == o2.getSum();
    }
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


            auto pC = n->getPriorityChild();

            if (n->mark.h == 1) {
                n->mark.m = pC->mark.m;
                n->mark.mPrev = n;
            }
            else {
                n->mark.m = pC->mark.m;
                n->mark.mPrev = pC->mark.mPrev;
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

//template<class T>
//void goForwardG(Node<T>* n, Way<T>& curWay) {
//    // n != nullptr
//
//    curWay.elements.push_back(n);
//
//    if (n->hasLeft() && n->left->mark.h == n->mark.h - 1)
//        goForwardG(n->left, curWay);
//    else
//        if (n->hasRight())
//            goForwardG(n->right, curWay);
//        else
//            curWay.endElements.push_back(n);
//}

template<class T>
void search(Node<T>* root, vector<Node<T>*>& maxMSLLinks) {

    //cout << *root->mark.m->element << " " << *root->mark.mPrev->element;

    if (root->mark.msl + 1 > maxMSLLinks[0]->mark.msl) {
        cout << *root->element << " <-> " << *root->mark.m->element;
        return;
    } 

    int undefCount = 0;
    Node<T>* node = maxMSLLinks[0];
    PointPair<T> minPair = PointPair<T>{ node->left->mark.m, node->right->mark.mPrev, node};
    PointPair<T> p{ node->left->mark.mPrev, node->right->mark.m, node};

    if (p < minPair)
        minPair = p;
    else
        if (minPair == p)
            if (*p.localRoot->element == *minPair.localRoot->element)
                undefCount++;
        
    for (int i = 1; i < maxMSLLinks.size(); i++) {
        Node<T>* node = maxMSLLinks[i];
        if (node->hasBoth()) {

            PointPair<T> p1{ node->left->mark.m, node->right->mark.mPrev, node};
                

            if (p1 < minPair) {
                minPair = p1;
                undefCount = 0;
            }
            else
                if (p1 == minPair) {
                    if (*p1.localRoot->element == *minPair.localRoot->element )
                        undefCount++;
                }

            PointPair<T> p2{ node->left->mark.mPrev, node->right->mark.m, node };

            if (p2 < minPair) {
                minPair = p2;
                undefCount = 0;
            }
            else
                if (p2 == minPair) {
                    if (*p2.localRoot->element == *minPair.localRoot->element)
                        undefCount++;
                }
            /*cout << "[" << *node->left->mark.m->element << "<->" << *node->right->mark.mPrev->element << "]" << endl;
            cout << "[" << *node->left->mark.mPrev->element << "<->" << *node->right->mark.m->element << "]" << endl;*/
        }
    }

    if (root->mark.msl + 1 == maxMSLLinks[0]->mark.msl) {
        // !!!!!
    }
    if (undefCount > 0) {
        cout << "UNDEFINED, NOTHING TO DO";
    }
    else {
        cout << *minPair.a->element << "<->" << *minPair.b->element;
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

    goReverse(tree.root, tree.maxMSLLinks);

    search(tree.root, tree.maxMSLLinks);

    goForward(tree.root);

    inputFile.close();
    outputFile.close();
}