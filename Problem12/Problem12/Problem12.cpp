// Problem12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
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
template<class T>
struct NodeChain {
    Node<T>* n;
    Node<T>* parent;
    bool l = 1;
};
ofstream outputFile;

template<class T>
class TreeManipulator {
public:
    void goForwardPrint(Node<T>* n) {
        if (n != nullptr) {
            outputFile << *n->element << "\n";
            goForwardPrint(n->left);
            goForwardPrint(n->right);
        }

    }
    NodeChain<T> getMinNode(NodeChain<T> n) {

        if (n.n->left == nullptr)
            return n;

        return getMinNode({ n.n->left, n.n });

    }

    T ejectMin(Node<T>* n) {
        T v;
        NodeChain<T> nodeChain = getMinNode({ n->right, n, 0 });
        v = *nodeChain.n->element;

        removeElement(nodeChain);

        return v;
    }

    void removeElement(NodeChain<T> nodeChain) {
        if (nodeChain.n->isLeaf())
            if (nodeChain.l) {
                delete nodeChain.parent->left;
                nodeChain.parent->left = nullptr;
            }
            else {
                delete nodeChain.parent->right;
                nodeChain.parent->right = nullptr;
            }
        else if (nodeChain.n->hasLeft() && !nodeChain.n->hasRight()) {
            if (nodeChain.l) {
                nodeChain.parent->left = nodeChain.n->left;
            }
            else {
                nodeChain.parent->right = nodeChain.n->left;
            }

            delete nodeChain.n;
        }
        else if (!nodeChain.n->hasLeft() && nodeChain.n->hasRight()) {
            if (nodeChain.l) {
                nodeChain.parent->left = nodeChain.n->right;
            }
            else {
                nodeChain.parent->right = nodeChain.n->right;
            }

            delete nodeChain.n;
        }
        else {
            int v = ejectMin(nodeChain.n);
            *nodeChain.n->element = v;
        }
    }
    void removeElement(Node<T>* n, Node<T>* parent, bool l, T value) {
        if (n == nullptr)
            return;

        if (*n->element == value) {
            removeElement({ n, parent, l });
        }
        else {
            removeElement(n->left, n, 1, value);
            removeElement(n->right, n, 0, value);
        }

    }

    void removeElement(Tree<T>& tree, T value) {
        if (value == *tree.root->element) {
            if (tree.root->right != nullptr) {
                if (tree.root->left == nullptr) {
                    tree.root = tree.root->right;
                }
                else {
                    int min = ejectMin(tree.root);
                    *tree.root->element = min;
                }

            }
            else
                if (tree.root->left != nullptr) {
                    tree.root = tree.root->left;
                }
                else
                    tree.root = nullptr;

        }
        else
            removeElement(tree.root, nullptr, 0, value);
    }

};


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

template<class T>
void goForwardG(Tree<T>& tree, Node<T>* n, int& targetAmount) {
    
    if (n != nullptr) {
        if (n->mark.h == targetAmount) {
            cout << "\nTARGET: " << *n->element << endl;
            TreeManipulator<T> tm;
            tm.removeElement(tree, *n->element);
            cout << "Remove finished " << endl;
            return;
        }

        if (n->hasLeft() || n->hasRight()) {
            
            auto c = n->getPriorityChild();
            goForwardG(tree, c, targetAmount);
        }
    }
}

template<class T>
void search(Tree<T>& tree, Node<T>* root, vector<Node<T>*>& maxMSLLinks) {

    //cout << *root->mark.m->element << " " << *root->mark.mPrev->element;

    /*if (root->mark.msl + 1 > maxMSLLinks[0]->mark.msl) {
        cout << *root->element << " <-> " << *root->mark.m->element;
        return;
    }  */
    //priority_queue<PointPa> queue;

    TreeManipulator<T> tm;
    if (((root->hasLeft() || root->hasRight()) && !root->hasBoth()) && (root->mark.msl + 1 > maxMSLLinks[0]->mark.msl)) {
        cout << *root->element << " <-> " << *root->mark.m->element;
        int t = (root->mark.msl + 1) / 2;
        goForwardG(tree, root->getPriorityChild(), t);

        tm.goForwardPrint(tree.root);
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
            else if (*p.localRoot->element < *minPair.localRoot->element) {
                minPair = p;
            }
        
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
                    else if (*p1.localRoot->element < *minPair.localRoot->element) {
                        minPair = p1;
                    }
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
                    else if (*p2.localRoot->element < *minPair.localRoot->element) {
                        minPair = p2;
                    }
                }

        }
    }

    if (root->mark.msl + 1 == minPair.localRoot->mark.msl) {
        PointPair<T> rootPair{ root, root->mark.m, root };
        if (rootPair < minPair) {
            minPair = rootPair;
            undefCount = 0;
        }
        else
            if (rootPair == minPair) {
                if (*rootPair.localRoot->element == *minPair.localRoot->element)
                    undefCount++;
                else if (*rootPair.localRoot->element < *minPair.localRoot->element) {
                    minPair = rootPair;
                }
            }
                
    }
    

    if (undefCount > 0) {
        cout << "UNDEFINED, NOTHING TO DO";
    }
    else {
        cout << *minPair.a->element << "<->" << *minPair.b->element;

        if (minPair.localRoot == root ? ((minPair.localRoot->mark.msl) % 2 == 0) :
            ((minPair.localRoot->mark.msl - 1) % 2 == 0)) {
            int target = (minPair.localRoot->mark.msl + 1) / 2;

            /*if (minPair.localRoot == root) {
                tm.removeElement(tree, *root->element);
            }*/
            if (minPair.localRoot->hasLeft()) {
                goForwardG(tree, minPair.localRoot->left, target);
            }

            if (minPair.localRoot->hasRight()) {
                goForwardG(tree, minPair.localRoot->right, target);
            }
        }

    }

    tm.goForwardPrint(tree.root);

}


int main()
{
    ifstream inputFile("input.txt");

    Tree<int> tree;
    while (!(inputFile.peek() == EOF)) {
        inputFile >> tree;
    }

    outputFile.open("output.txt");

    goReverse(tree.root, tree.maxMSLLinks);

    search(tree, tree.root, tree.maxMSLLinks);

    inputFile.close();
    outputFile.close();
}