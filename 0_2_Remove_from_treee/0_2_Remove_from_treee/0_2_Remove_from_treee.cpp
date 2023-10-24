

#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;


struct Node {
    int* element = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    bool isLeaf() {
        return (left == nullptr) && (right == nullptr);
    }

    bool hasLeft() {
        return left != nullptr;
    }
    
    bool hasRight() {
        return right != nullptr;
    }

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

    int* getMaxElement(Node* n) {
        if (n->right == nullptr) {
            return n->element;
        }
        return getMaxElement(n->right);
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
struct NodeChain {
    Node* n;
    Node* parent;
    bool l = 1;
};
class TreeManipulator {
public:
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
    NodeChain getMinNode(NodeChain n) {

        if (n.n->left == nullptr)
            return n;

        return getMinNode({n.n->left, n.n});

    }

    int ejectMin(Node* n) {
        int v;
        NodeChain nodeChain = getMinNode({n->right, n, 0});
        v = *nodeChain.n->element;

        removeElement(nodeChain);

        return v;
    }

    void removeElement(NodeChain nodeChain) {
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
    void removeElement(Node* n, Node* parent, bool l, int value) {
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

    void removeElement(Tree& tree, int value) {
        if (value == *tree.root->element) {
                if (tree.root->right != nullptr) {
                    if (tree.root->left == nullptr) {
                        tree.root = tree.root->right;
                    }
                    else {
                        int min = ejectMin(tree.root);
                        *tree.root->element = min;
                    }
                    
                } else
                    if (tree.root->left != nullptr) {
                        tree.root = tree.root->left;
                    }
                    else
                        tree.root = nullptr;
            
        } else
            removeElement(tree.root, nullptr, 0, value);
    }

};

int main()
{
    ifstream inputFile("input.txt");

    int keyElement;
    inputFile >> keyElement;

    Tree tree;
    TreeManipulator treeManipulator;
    while (!(inputFile.peek() == EOF)) {
        inputFile >> tree;
        elementAmount++;
    }

    treeManipulator.removeElement(tree, keyElement);
    outputFile.open("output.txt");
    treeManipulator.goForward(tree.root);

    inputFile.close();
    outputFile.close();
}