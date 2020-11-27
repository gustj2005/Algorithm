#include <stdio.h>
#include<iostream>
#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef struct Node {
    int key, bf;
    struct Node* left, * right;
}Node;

typedef Node* Tree;

Node* getNode();
int height(Node* T);
int noNodes(Node* T);
Node* maxNode(Node* T);
Node* minNode(Node* T);
void rotateLL(Tree* T, Node* x, Node* p);
void rotateLR(Tree* T, Node* x, Node* p);
void rotateRR(Tree* T, Node* x, Node* p);
void rotateRL(Tree* T, Node* x, Node* p);
Node* searchParentNode(Tree* T, Node* n);
Node* insertBST(Tree* T, int newKey);
Node* deleteBST(Tree* T, int deleteKey);
Node* updateBF(Tree* T, Node* y, Node** x, Node** f);
void deleteAVL(Tree* T, int deleteKey);
void insertAVL(Tree* T, int newKey);
void inorderAVL(Tree T);


Node* getNode() {
    Node* newNode = new Node();
    newNode->key = 0;
    newNode->bf = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int height(Node* T) {
    if (T == nullptr) return 0;
    else {
        int lb = height(T->left);
        int rb = height(T->right);
        return max(lb, rb) + 1;
    }
}

int noNodes(Node* T) {
    if (T == NULL) {
        return 0;
    }else {
        return noNodes(T->left) + noNodes(T->right) + 1;
    }
}

Node* maxNode(Node* T) {
    if (T->right == NULL) return T;
    else{
        return maxNode(T->right);
    }
}

Node* minNode(Node* T) {
    if (T->left == NULL) return T;
    else {
        return minNode(T->left);
    }
}

void rotateLL(Tree* T, Node* x, Node* p) {
    p->left = x->right;
    x->right = p;
    return;
}

void rotateRR(Tree* T, Node* x, Node* p) {
    p->right = x->left;
    x->left = p;
    return;
}

void rotateLR(Tree* T, Node* x, Node* p) {
    rotateRR(T, x->right, x);
    return rotateLL(T, x, p);
}

void rotateRL(Tree* T, Node* x, Node* p) {
    rotateLL(T, x->left, x);
    return rotateRR(T, x, p);
}

Node* insertBST(Tree* T, int newKey) {
    Node* p = *T;
    if (p != NULL) {
        if (p->key == newKey)  return p;
        if (p->key > newKey) insertBST(&p->left, newKey);
        else insertBST(&p->right, newKey);
    }
    else {
        Node* newNode = getNode();
        newNode->key = newKey;  
        *T = newNode;
        return *T;
    }
}

Node* searchParentNode(Tree* T, Node* n) {
    Node* q = NULL;
    Node* p = *T;
    while (p != NULL) {
        if (p->key == n->key) return q;
        q = p;
        if (p->key < n->key) {
            p = p->left;
        }
        else  {
            p = p->right;
        }
    }
    return q;
}


Node* deleteBST(Tree* T, int deleteKey) {
    Node* p = *T;
    Node* q = NULL; 
    while (p != NULL && p->key != deleteKey) {
        q = p;
        if (p->key > deleteKey)  p = p->left;
        else  p = p->right;
    }
    if (p == NULL)  return p;
    if (p->left == NULL && p->right == NULL) {
        if (q != NULL) {
            if (q->left == p)  q->left = NULL;
            else  q->right = NULL;   
        }
        else {
            *T = NULL;
        }
    }
    else if (p->left == NULL || p->right == NULL) {
        if (q != NULL) {
            if (p->left != NULL) {
                if (q->left == p)  q->left = p->left;
                else   q->right = p->left;
            }
            else {
                if (q->left == p) q->left = p->right;
                else  q->right = p->right; 
            }
        }
        else {
            if (p->left != NULL)  *T = p->left;
            else  *T = p->right;
        }
    }
    else {
        Node* r;
        string flag = "";
        if (height(p->left) > height(p->right)) {
            r = maxNode(p->left);
            flag = "LEFT";
        }
        else if (height(p->left) < height(p->right)) {
            r = minNode(p->right);
            flag = "RIGHT";
        }
        else {
            if (noNodes(p->left) >= noNodes(p->right)) {
                r = maxNode(p->left);
                flag = "LEFT";
            }
            else {
                r = minNode(p->right);
                flag = "RIGHT";
            }
        }
        p->key = r->key;
        if (flag=="LEFT") {
            deleteBST(&p->left, r->key);
        }
        else {
            deleteBST(&p->right, r->key);
        }

    }
    return p;
}



Node* updateBF(Tree* T, Node* y, Node** x, Node** f) {
    Node* p = y;
    if (p == nullptr)  return p;

    if (p->right == NULL && p->left == NULL) p->bf = 0;
    else if (p->left == NULL)  p->bf = -height(p->right);
    else if (p->right == NULL)   p->bf = height(p->left);
    else   p->bf = height(p->left) - height(p->right);

    if (p->bf == 2 || p->bf == -2)  return p;
    else {
        updateBF(T, p->left, x, f);
        updateBF(T, p->right, x, f);
    }
}



void insertAVL(Tree* T, int newKey) {
    Node* n = insertBST(T, newKey);
    Node* p = searchParentNode(T, n);
    Node* q = updateBF(T, n, &n, &p);
    if (p == nullptr) cout<< "NO";
    else {
        if (p->bf == 2) {
            if (p->left->key > newKey) cout << "LL";
            else   cout << " LR";
        }
        else if (p->bf == -2) {
            if (p->right->key < newKey)   cout << "RR";
            else cout << " RL";
        }
        else {
            cout << "NO";
        }
    }


}

void deleteAVL(Tree* T, int deleteKey) {
    Node* n = deleteBST(T, deleteKey);
    Node* P = searchParentNode(T, n);
    Node* p = updateBF(T, *T, &n, &P);
    if (p == nullptr) cout<<"NO";
    else {
        if (p->bf == 2) {
            if (p->left->bf < 0)  cout << "LR";
            else cout << "LL";        
        }
        else if (p->bf == -2) {
            if (p->right->bf > 0)  cout << "RL";
            else  cout << "RR";    
        }
        else {
            cout << "NO";
        }
    }
    
}

void inorderAVL(Tree T) {
    if (T != NULL)
    {
        inorderAVL(T->left);
        cout << T->key << " ";
        inorderAVL(T->right);
    }
}

int main() {
    int testcase[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49 };
   
    Tree T = NULL;
    cout << "20175161";
    // insertion
    for (int i = 0; i < 20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

    // deletion
    for (int i = 0; i < 20; i++) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

    T = NULL;

    // reinsertion
    for (int i = 0; i < 20; i++) { printf("%d ", testcase[i]); insertAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }

    // redeletion
    for (int i = 19; 0 <= i; i--) { printf("%d ", testcase[i]); deleteAVL(&T, testcase[i]); printf(" : "); inorderAVL(T); printf("\n"); }
}