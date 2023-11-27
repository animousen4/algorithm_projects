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
template<class T>
struct PointPair {
    Node<T>* a;
    Node<T>* b;

    Node<T>* localRoot;

    int wSize = 0;


    T getSum() {
        return *a->element + *b->element;
    }


    // !! look
    bool operator<(PointPair<T>& o2) {
        /*if (wSize > o2.wSize)
            return true;
        else
            if (wSize == o2.wSize)*/
        
        return getSum() < o2.getSum();

        //return false;
       
    }

    bool operator==(PointPair<T>& o2) {
        return (wSize == o2.wSize) && (getSum() == o2.getSum());
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
        cout << "\nTARGET: " << value << endl;
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

        cout << "Remove finished. ";
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
                n->mark.msl += n->right->mark.h + n->left->mark.h + 2; // n->left->mark.msl + 2
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
vector<Node<T>*> getHalfPath(Node<T>* root, T n) {
    vector<Node<T>*> path;

    while (root != nullptr) {

        if (*root->element > n) {
            root = root->left;
        }
        else if (*root->element < n) {
            root = root->right;
        }
        else {
            break;
        }

        path.push_back(root);
    }

    return path;
}


template<class T>
vector<Node<T>*> getHalfWayPath(Node<T>* root, int n1, int n2) {
    vector<Node<T>*> res;
    vector<Node<T>*> p1 = getHalfPath(root, n1);
    vector<Node<T>*> p2 = getHalfPath(root, n2);

    for (int i = 0; i < p1.size(); i++)
        res.push_back(p1[i]);
    res.push_back(root);
    for (int i = 0; i < p2.size(); i++)
        res.push_back(p2[i]);

    return res;
}
template<class T>
Node<T>* getAvgNode(Node<T>* root, int n1, int n2) {
    vector<Node<T>*> way = getHalfWayPath(root, n1, n2);
    if (way.size() % 2 == 0)
        return nullptr;
    std::sort(
        way.begin(),
        way.end(),
        [](const Node<T>* a, const Node<T>* b)
        {
            return *a->element < *b->element;
        }
    );

    return way[way.size() / 2];
}
template<class T>
void search(Tree<T>& tree, Node<T>* root, vector<Node<T>*>& maxMSLLinks) {
    
    vector<PointPair<T>> comparable;
    TreeManipulator<T> tm;

    Node<T>* node;

    if (root->mark.h + 1 >= maxMSLLinks[0]->mark.msl) {
        comparable.push_back(PointPair<T>{root, root->mark.m, root, root->mark.h + 1});
        if (!root->hasBoth())
            maxMSLLinks.erase(remove(maxMSLLinks.begin(), maxMSLLinks.end(), root), maxMSLLinks.end());
        
    }

    PointPair<T> pp;
    for (int i = 0; i < maxMSLLinks.size(); i++) {
        node = maxMSLLinks[i];
        if (node->left->mark.m != nullptr && node->right->mark.mPrev != nullptr) {
            pp = PointPair<T>{ node->left->mark.m, node->right->mark.mPrev, node, node->mark.msl };
            if (comparable.size() > 0)
                if (comparable[0].wSize <= node->mark.msl)
                    comparable.push_back(pp);
                else {}
            else
                comparable.push_back(pp);
        }

        if (node->left->mark.mPrev != nullptr && node->right->mark.m != nullptr) {
            pp = PointPair<T>{ node->left->mark.mPrev, node->right->mark.m, node, node->mark.msl };
            if (comparable.size() > 0)
                if (comparable[0].wSize <= node->mark.msl)
                    comparable.push_back(pp);
                else {}
            else
                comparable.push_back(pp);
        }
    }

    int undefCount = 0;
    
    
    PointPair<T> minPair = comparable[0];
    PointPair<T> cur;
    Node<T>* minAvgNode = getAvgNode(minPair.localRoot, *minPair.a->element, *minPair.b->element);
    Node<T>* curAvgNode = nullptr;
    for (int i = 1; i < comparable.size(); i++) {
        cur = comparable[i];
        curAvgNode = getAvgNode(cur.localRoot, *cur.a->element, *cur.b->element);

        if (cur.wSize > minPair.wSize) {
            minPair = cur;
            undefCount = 0;
        }
        else
            if (cur.wSize == minPair.wSize) {
                if (cur < minPair) {
                    minPair = cur;
                    undefCount = 0;
                    minAvgNode = curAvgNode;
                }
                else if (cur == minPair) {
                    
                    if (*cur.localRoot->element == *minPair.localRoot->element && curAvgNode != minAvgNode)
                        undefCount++;
                    else if (*cur.localRoot->element < *minPair.localRoot->element) {
                        minPair = cur;
                        undefCount = 0;
                        minAvgNode = curAvgNode;
                    }
                }
                
            }
    }
    

    if (undefCount > 0 || minPair.wSize % 2 == 0) {
        cout << "UNDEFINED, NOTHING TO DO";
    }
    else {
        cout << *minPair.a->element << "<->" << *minPair.b->element << endl;

        auto way = getHalfWayPath(minPair.localRoot, *minPair.a->element, *minPair.b->element);

        for (int i = 0; i < way.size(); i++)
            cout << *way[i]->element << " ";

        tm.removeElement(tree, *minAvgNode->element);
       

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

    if (tree.root->left == nullptr && tree.root->right == nullptr)
        outputFile << *tree.root->element;
    else {
        goReverse(tree.root, tree.maxMSLLinks);

        search(tree, tree.root, tree.maxMSLLinks);
    }
    inputFile.close();
    outputFile.close();
}