#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int op_insert = 0;
int op_find = 0;
int op_remove = 0;
int depth = 0;

struct BSTreeNode {
    string key;
     BSTreeNode* left{};
     BSTreeNode* right{};
     BSTreeNode* parent{};
};

BSTreeNode* last;

void insertNode(BSTreeNode*& root, const string& k) {

    op_insert++;
    if (root == nullptr)
    {
        root = new BSTreeNode;
        root->key = k;
        root->left = root->right = root-> parent = nullptr;
        return;
    }
        op_insert++;
        if (k < root->key)
        {
            if (root->left == nullptr)
            {
                root->left = new BSTreeNode;
                root->left->key = k;
                root->left->left = nullptr;
                root->left->right = nullptr;
                root->left->parent = root;
                last = root->left;
                depth++;
            }
            else
                insertNode(root->left, k);
        }
        else
            if (root->right == nullptr)
            {
                root->right = new BSTreeNode;
                root->right->key = k;
                root->right->left = nullptr;
                root->right->right = nullptr;
                root->right->parent = root;
                last = root->right;
                depth++;
            }
            else
                insertNode(root->right, k);
}

BSTreeNode* findNode(BSTreeNode* root, const string& k) {

    op_find++;
    if (root == nullptr) {
        return nullptr;
    }

    op_find++;
    if (k == root->key) {

        return root;
    }
    op_find++;
    if (k < root->key)
        return findNode(root->left, k);
    else
        return findNode(root->right, k);
}

void printNode(BSTreeNode* n) {
    if (n != nullptr) {
        cout << n->key << endl;
    }
    else {
        cout << "Empty" << endl;
    }
}

int sizeTree(BSTreeNode* root, int a)
{
    op_remove++;
    if (root->left == nullptr && root->right == nullptr)
    {
        if (depth < a)
            depth = a;
    }
    else
    {
        a++;
        op_remove++;
        if(root->left != nullptr)
        sizeTree(root->left, a);
        op_remove++;
        if(root->right != nullptr)
        sizeTree(root->right, a);
    }     
    return depth;
}

void removeNode(BSTreeNode* root)
{   
    op_remove++;
    if (last == nullptr)
        return;
    op_remove++;
    if (last->parent->left == last)
        last->parent->left = nullptr;    
    else
        last->parent->right = nullptr;
    delete last;
    last = nullptr;    
    sizeTree(root, 0);
}

int main() 
{

    vector<string> data;
    ifstream input;
    input.open("lista.txt");
    int d = 0;
    string bufor;
    while (!input.eof())
    {
        string text;
        getline(input, text);
        if (text.length() < 5)
        {
        data.push_back(text);
        }
    }
    input.close();
    ofstream output;
    output.open("glebokosc_lista_max4.txt");
    int losowy;
    string random;
    losowy = rand() % data.size();
    random = data[losowy];
    for (int i = 100; i <= 10000; i += 100)
    {
        
        BSTreeNode* root = nullptr;
        for (int j = 0; j <= i; j++)
        {
            op_find = 0;
            op_insert = 0;
            op_remove = 0;
            depth = 0;
            insertNode(root, data[rand() % data.size()]);
        }
        findNode(root, random);
        removeNode(root);
        output << i << "; " << depth << endl;
    }
    
    return 0;
}
