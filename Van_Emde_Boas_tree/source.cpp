#include  <iostream>
#include <vector>
#include <cmath>

using  namespace std;
struct VEBtree {
    int U;                  //   the size of  the Currnet Universe
    int min, max;          // min, max value of the current VBE tree
     vector<VEBtree*> children;
     VEBtree* summary;

     VEBtree(int u): U(u), min(-1),  max(-1), summary(nullptr)  {
        if (U > 2) {
            int child_U = ceil(sqrt(U));
            summary = new VEBtree(child_U);
            children.resize(child_U, nullptr);
            for (int i =  0;  i  < child_U; ++i)
                children[i] = new VEBtree(child_U);
        }
     }
};
VEBtree* buildTree(int U) {
    if (U <= 1) return nullptr;
    return new VEBtree(U);
}


void Insert(VEBtree *T,int key) {
    if (T->min == -1) {T->min =  T->max  =  key; return;}      // Inert to an Empty Tree
    if (key < T->min) swap(T->min, key);
    if (key >  T->max) T->max = key;

    if (T->U > 2) {
        int child_U = ceil(sqrt(T->U));
        int idx =  key / child_U;
        int low =  key % child_U;


        if (T->children[idx]->min == -1)
            Insert(T->summary, low);
        Insert(T->children[idx], low);
    }
}


int FindNext(VEBtree* T, int key) {
    // successor is min
    if ( key < T->min) return T->min;
    // Out of range
    if (key > T->max || key < 0) return T->U;
    // Base case
    if (T->U == 2) {
        if (key == 0 && T->max == 1) return 1;
        return T->U;
    } 

    int child_U = ceil(sqrt(T->U));
    int idx = floor(key / child_U);
    int sub_key = floor(key % child_U);

    // key Between min & max
    if (T->children[idx] != nullptr && T->children[idx]->min != -1 && sub_key < T->children[idx]->max)
        return idx * child_U + FindNext(T->children[idx], sub_key);

    // find the value in the Summary tree for faster searching
    int nxt_sub_key = FindNext(T->summary, idx);
    if (nxt_sub_key ==  T->summary->U) return T->max;
    
    return T->U * nxt_sub_key + T->children[idx]->min;
}


void Erase(VEBtree* T, int key) {
    // Out of Range
    if (key < 0 || key < T->min || key > T->max) return;
    // Tree has  only 1 num left
    if (T->min == T->max && T->min == key) {
        T->min = T->max = -1;
        return;
    }
    
    int child_U = ceil(sqrt(T->U));

    if (key ==   T->min) {
        // Find the first child idx not empty
        int idx = FindNext(T->summary, -1);

        if (idx == T->summary->U)
            T->min = T->max;
        else 
            T->min = idx* child_U + T->children[idx]->min;
        key = idx * child_U + T->children[idx]->min;
    }


    int i =  floor(key / child_U);
    int sub_key = floor( key % child_U);
    Erase(T->children[i], sub_key);
    
    if (T->children[i]->min == -1)
        Erase(T->summary, i);
    
    if (key  == T->max) {
        // The child tree  is  empty
        if (T->summary->min == -1)
            T->max = T->min;
        else {
            int idx = T->summary->max;
            T->max =  T->children[idx]->max + idx * child_U;
        }
    }
}


int main() {
    VEBtree* T =   buildTree(64);
    Insert(T, 10);
    Insert(T,11);
    Insert(T,12);
    cout << "- Before Delete 12:\n";
    cout << FindNext(T,10) << endl;
    cout << FindNext(T,11) <<  endl;
    
    Erase(T,12);
    cout << "- After Delete 12:\n";
    cout << FindNext(T,10) << endl;
    cout << FindNext(T,11) <<  endl;
}