#include <iostream>
#include <string>
#include <stdio.h>
#include "simplecanvas/simplecanvas.h"
using namespace std;

class TreeNode {
    public:
        int key;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int key) {
            this->key = key;
            left = NULL;
            right = NULL;
        }
        void draw(int res) {

        }
};

TreeNode* addRecursive(TreeNode* node, int key) {
    if (node == NULL) {
        return new TreeNode(key);
    }
    else {
        if (key < node->key) {
            node->left = addRecursive(node->left, key);
        }
        else if (key > node->key) {
            node->right = addRecursive(node->right, key);
        }
        return node;
    }
}

class BinaryTree {
    private:
        void cleanup(TreeNode* N) {
            if (N != NULL) {
                cleanup(N->left);
                cleanup(N->right);
                delete N;
            }
        }
    public:
        TreeNode* root;
        BinaryTree() {
            root = NULL;
        }
        ~BinaryTree() {
            cleanup(root);
        }
        /**
        * @param key: key I'm looking for
        * @return true if key is in the tree, 
        *         or false otherwise
        */
        bool contains(int key) {
            bool found = false;
            TreeNode* node = root;
            //while (!found && node != NULL) {
            while (!(found || node == NULL)) { 
                if (key < node->key) {
                    node = node->left;
                }
                else if (key > node->key) {
                    node = node->right;
                }
                else {
                    found = true;
                }
            }
            return found;
        }


        /**
        * @param key: key I'm looking for
        * @return true if key is in the tree, 
        *         or false otherwise
        */
        void add(int key) {
            root = addRecursive(root, key);
        }

        void draw(int res) {
            SimpleCanvas canvas(res, res);
            canvas.clearRect(255, 255, 255);
            canvas.drawString("A Tree!", 10, 10, "simplecanvas/");
            root->draw(res);
            canvas.write("tree.png");
        }
};

BinaryTree* makeTree() {
    BinaryTree* T = new BinaryTree();
    T->root = new TreeNode(9);
    T->root->left = new TreeNode(4);
    // TODO: Finish this
    T->root->left->left = new TreeNode(1);
    T->root->left->right = new TreeNode(8);
    T->root->right = new TreeNode(20);
    T->root->right->left = new TreeNode(15);
    T->root->right->right = new TreeNode(25);

    return T;
}



void traverse(TreeNode* N) {
    if (N != NULL) {
        traverse(N->left);
        printf("%i ", N->key);
        traverse(N->right);
    }
}

int main() {
    BinaryTree* T = new BinaryTree();//makeTree();
    T->add(1);
    T->add(7);
    T->add(4);
    T->add(3);
    T->add(10);
    T->add(2);
    traverse(T->root);
    T->draw(400);
    printf(".\n");
    delete T;
    return 0;
}