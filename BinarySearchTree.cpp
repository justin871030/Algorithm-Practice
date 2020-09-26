#include <iostream>
#include <string>
#include <queue>
using namespace std;


class BST;
class TreeNode {
public:
    TreeNode* leftchild;
    TreeNode* rightchild;
    TreeNode* parent;
    int key;

    TreeNode(int key = 0, TreeNode* leftchild = NULL, TreeNode* rightchild = NULL, TreeNode* parent = NULL) {
        this->leftchild = leftchild;
        this->rightchild = rightchild;
        this->parent = parent;
        this->key = key;
    };
    friend class BST;
};

class BST {
public:
    TreeNode* root;
    TreeNode* Successor(TreeNode* current);
    TreeNode* Predecessor(TreeNode* current);

    BST() { this->root = NULL; };//constructor of null tree
    BST(TreeNode* node) { this->root = node; };//constructor with root of tree

    TreeNode* TreeSearch(int key); //find key from root.
    TreeNode* TreeSearch(TreeNode* x, int key);//find key from node.
    TreeNode* TreeMinimum(); // find minimum node from root.
    TreeNode* TreeMaximum(); // find maximum node from root.
    TreeNode* TreeMinimum(TreeNode* x); // find minimum node
    TreeNode* TreeMaximum(TreeNode* x); // find maximum node
    void Transplant(TreeNode* u, TreeNode* v);// implement transplat for delete function.

    void TreeInsert(TreeNode* node); // insert the node.
    void TreeInsert(int key); // insert the node with key.
    void TreeDelete(TreeNode* node); // delete the node.
    void TreeDelete(int key); // delete the node with key.
    void InorderPrint();        // print the tree inorder.
    void LevelorderPrint();          // print the tree levelorder.
};

TreeNode* BST::TreeSearch(int key) {

    if (root == NULL || key == root->key) {
        return root;
    }
    if (key < root->key) {
        return TreeSearch(root->leftchild, key);
    }
    else {
        return TreeSearch(root->rightchild, key);
    }
}

TreeNode* BST::TreeSearch(TreeNode* x, int key) {
    if (x == NULL || key == x->key) {
        return x;
    }
    if (key < x->key) {
        return TreeSearch(x->leftchild, key);
    }
    else {
        return TreeSearch(x->rightchild, key);
    }
}

TreeNode* BST::TreeMinimum() {
    return TreeMinimum(root);
}

TreeNode* BST::TreeMaximum() {
    return TreeMaximum(root);;
}

TreeNode* BST::TreeMinimum(TreeNode* x) {
    while (x->leftchild != NULL) {
        x = x->leftchild;
    }
    return x;
}

TreeNode* BST::TreeMaximum(TreeNode* x) {
    while (x->rightchild != NULL) {
        x = x->rightchild;
    }
    return x;
}

TreeNode* BST::Predecessor(TreeNode* current) {
    if (current->leftchild != NULL) {
        return TreeMaximum(current->leftchild);
    }

    TreeNode* new_node = current->parent;

    while (new_node != NULL && current == new_node->leftchild) {
        current = new_node;
        new_node = new_node->parent;
    }
    return new_node;
}

TreeNode* BST::Successor(TreeNode* current) {

    if (current->rightchild != NULL) {
        return TreeMinimum(current->rightchild);
    }

    TreeNode* new_node = current->parent;

    while (new_node != NULL && current == new_node->rightchild) {
        current = new_node;
        new_node = new_node->parent;
    }

    return new_node;
}

void BST::TreeInsert(TreeNode* insert_node) {

    TreeNode* y = NULL; //parent of the new node.
    TreeNode* x = this->root; //the start point of the new node.

    x = root;
    while (x != NULL) {                // down the tree recursively until down to the leaf.       
        y = x;
        if (insert_node->key < x->key) {
            x = x->leftchild;
        }
        else {
            x = x->rightchild;
        }
    }                                  // out of while loop, x is NULL
                                       // y is the parent of insert_node
    insert_node->parent = y;           // insert_node's parent pointer point to y

    if (y == NULL) {                    // insert_node connect to BST.
        this->root = insert_node;
    }
    else if (insert_node->key < y->key) {
        y->leftchild = insert_node;
    }
    else {
        y->rightchild = insert_node;
    }
}

void BST::TreeInsert(int key) {
    // the same with the insert_node version function, but here new a node first.
    TreeNode* y = NULL;
    TreeNode* x = this->root; 
    TreeNode* insert_node = new TreeNode(key);

    x = root;
    while (x != NULL) {                       
        y = x;
        if (insert_node->key < x->key) {
            x = x->leftchild;
        }
        else {
            x = x->rightchild;
        }
    }                        
                                    
    insert_node->parent = y;         

    if (y == NULL) {              
        this->root = insert_node;
    }
    else if (insert_node->key < y->key) {
        y->leftchild = insert_node;
    }
    else {
        y->rightchild = insert_node;
    }
}


void BST::InorderPrint() {
    TreeNode* current = new TreeNode;
    current = TreeMinimum(root);
    while (current) {
        cout << "(" << current->key << ")" << " ";
        current = Successor(current);
    }
}

void BST::LevelorderPrint() {

    queue<TreeNode*> q;
    q.push(this->root);					    // root is start point of level-order traversal, put into queue.

    while (!q.empty()) {                     // if queue isn't null.
        TreeNode* current = q.front();      // take the node.
        q.pop();
        cout << "(" << current->key << ")" << " ";

        if (current->leftchild != NULL) {    // if there is leftchild, put it into queue.
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL) {   // if there is righttchild, put it into queue.
            q.push(current->rightchild);
        }
    }
}

void BST::Transplant(TreeNode* u, TreeNode* v) {

    if (u->parent == NULL) {
        root = v;
    }
    else if(u == u->parent->leftchild) 
    {
        u->parent->leftchild = v;
    }
    else 
    {
        u->parent->rightchild = v;
    }
    if (v != NULL) 
    {
        v->parent = u->parent;
    }
}

void BST::TreeDelete(TreeNode* node) {   // delete node

    if (node->leftchild == NULL) {
        Transplant(node, node->rightchild);
    }
    else if (node->rightchild == NULL)
    {
        Transplant(node, node->leftchild);
    }
    else 
    {
        TreeNode* y = TreeMinimum(node->rightchild);//the node use to replace node.
        if (y->parent != node) 
        {
            Transplant(y, y->rightchild);
            y->rightchild = node->rightchild;
            y->rightchild->parent = y;
        }
        Transplant(node, y);
        y->leftchild = node->leftchild;
        y->leftchild->parent = y;
    }
}

void BST::TreeDelete(int KEY) { // find the node of the input key,delete it.

    TreeNode* delete_node = TreeSearch(root,KEY);// find the node
    if (delete_node == NULL) {// if NULL ,return.
        return;
    }
    else //else, delete it.
    {
        TreeDelete(delete_node);
    }
}

int main() {

    BST T;

    cout << "[ Insert {8,1000,2,513,5} ]\n\n";
    T.TreeInsert(8);
    T.TreeInsert(1000);
    T.TreeInsert(2);
    T.TreeInsert(513);
    T.TreeInsert(5);

    cout << "Inorder Traversal:\n";
    T.InorderPrint();
    cout << endl << endl;
    cout << "Level-order Traversal:\n";
    T.LevelorderPrint();
    cout << endl << endl;

    cout << "[ Maximum node of the tree ]\n\n(" << T.TreeMaximum()->key << ")" << endl << endl;

    cout << "[ Minimum node of the tree ]\n\n(" << T.TreeMinimum()->key << ")" << endl << endl;

    cout << "[ Predecessor of maximum node in the tree ]\n\n(" << T.Predecessor(T.TreeMaximum())->key << ")" << endl << endl;

    cout << "[ Successor of minimum node in the tree ]\n\n(" << T.Successor(T.TreeMinimum()) << ")" << endl << endl;

    cout << "[ Delete 8,513 ]\n\n";
    T.TreeDelete(8);
    T.TreeDelete(513);

    cout << "Inorder Traversal:\n";
    T.InorderPrint();
    cout << endl << endl;
    cout << "Level-order Traversal:\n";
    T.LevelorderPrint();
    cout << endl << endl;


    cout << "[ Search 1000 ]\n\n";
    TreeNode* node = T.TreeSearch(1000);
    if (node != NULL) {
        cout << "There is " << "(" << node->key << ")\n" << endl;
    }
    else {
        cout << "no element with Key(1000)\n" << endl;
    }

    cout << "[ Search 8 ]\n\n";
    node = T.TreeSearch(8);
    if (node != NULL) {
        cout << "There is " << "(" << node->key << ")\n" << endl;
    }
    else {
        cout << "no element with Key(8)\n" << endl;
    }

    return 0;
}