#include <iostream>
using namespace std;

typedef struct node{
    int val;
    int min2 = -1;
    node* first = NULL;
    node* second = NULL;
    node* third = NULL;
}node;

typedef struct returnVal{ //Struct used only when multiple variables had to be returned in a single return statement
    node* firstTemp = NULL;
    node* secondTemp = NULL;
    int minimum = -1;
}returnVal;

class Tree23{
    public:
        node* root = NULL;
};

void Extract(node* r){ //Same as in problem statement
    if(r->first == NULL){
        cout << r->val<< " ";
    }else{
        if(r->first) Extract(r->first);
        if(r->second) Extract(r->second);
        if(r->third) Extract(r->third);
    }
}

int Height(node* r){ //Returns height of a node. Height of a leaf is taken to be 0
    if(r == NULL) return 0;
    int h = 0;
    while(r->first != NULL){
        h++;
        r = r->first;
    }
    return h;
}

int Min(node *r){ //Returns the minimum value stored in the tree/ sub-tree rooted at node r
    if(r == NULL) return -1;

    while(r->first != NULL){
        r = r->first;
    }

    return r->val;
}

node* twoNode(int val, node* first, node* second){ //Initialises and returns a twoNode, same as that in lectures
    node* temp = new node;
    temp->val=val;
    temp->first=first;
    temp->second=second;
    temp->third=NULL;
    return temp;
}

node* MakeSingleton(int val){ //Makes and returns a single node carrying value val
    node* temp = new node;
    temp->val = val;
    return temp;
}

returnVal MergeNode(node* S1, node* S2, int dh, node* thisRoot);

node* Merge(node* S1, node* S2){
    /* Takes two root nodes as input and returns 
    the root of the tree obtained on merging them */

    if(S1 == NULL) return S2; //Edge cases when a Tree is empty/ NULL
    if(S2 == NULL) return S1;

    int h1 = Height(S1);
    int h2 = Height(S2);

    returnVal v;

    if(h1 == h2){ //Another edge case, when the height of the trees is same, there is an easier way to return the resultant tree
        node* x = new node;
        if(S2->val > S1->val){
            x->first = S1;
            x->second = S2; 
            x->third = NULL;
            x->val = Min(S2);
        }else{
            x->first = S2;
            x->second = S1; 
            x->third = NULL;
            x->val = Min(S1);
        }
        return x;
    }else if(h1 > h2){ //S2 is supposed to be merged on the right side of S1
        v = MergeNode(S1, S2, h1-h2, S1);
    }else{ //h1<h2 => S1 is supposed to be merged on the left side of S2
        v = MergeNode(S2, S1, h2-h1, S2);
    }

    if(v.secondTemp == NULL){
        return v.firstTemp;
    }else{
        return twoNode(v.minimum, v.firstTemp, v.secondTemp);
    }
}

void Test(){
    Tree23 T;
    
    //T is the resultant tree, hence its root is updated after merge
    T.root = MakeSingleton(1);
    for(int i = 2; i <= 500; i++){
        T.root = Merge(T.root, MakeSingleton(i));
    }

    Tree23 U; //Same as T
    U.root = MakeSingleton(777);
    for(int i = 778; i <= 1000; i++){
        U.root = Merge(U.root, MakeSingleton(i));
    }
    
    Tree23 V;
    V.root = Merge(T.root, U.root);
    Extract(V.root);
}

int main(){

    Test();
    
    return 0;
}

returnVal MergeNode(node* S1, node* S2, int dh, node* thisRoot){
    if(S2->val > S1->val){ //S2 is to be inserted on the right of S1 at some appropriate height
        if(dh == 1){ //dh = Delta H = 1 is the candidate height for insertion/ merging
            if(thisRoot->third == NULL){ //Case where the appropriate node is a twoNode
                returnVal X;
                X.firstTemp = new node;
                X.firstTemp->first = thisRoot->first;
                X.firstTemp->second = thisRoot->second;
                X.firstTemp->third = S2;

                X.firstTemp->val = thisRoot->val;
                X.firstTemp->min2 = Min(S2);
                X.secondTemp = NULL;
                return X;
            }else{ //Case where the appropriate node is a threeNode
                returnVal X;
                X.firstTemp = new node;
                X.secondTemp = new node;

                X.firstTemp->first = thisRoot->first;
                X.firstTemp->second = thisRoot->second;
                X.firstTemp->third = NULL;
                X.secondTemp->first = thisRoot->third;
                X.secondTemp->second = S2;
                X.secondTemp->third = NULL;
                X.firstTemp->val = thisRoot->val;
                X.firstTemp->min2 = -1;
                X.secondTemp->val = Min(S2);
                X.secondTemp->min2 = -1;
                X.minimum = thisRoot->min2;
                return X;
            }
        }else{

            if(thisRoot->third == NULL){ //Case when the node is taller than the appropriate node and is a twoNode
                returnVal X;
                X = MergeNode(S1, S2, dh -1, thisRoot->second);

                if(X.secondTemp == NULL){
                    thisRoot->second = X.firstTemp;
                    X.firstTemp = thisRoot;
                    X.secondTemp = NULL;
                    return X;
                }else{
                    thisRoot->second = X.firstTemp;
                    thisRoot->third = X.secondTemp;
                    thisRoot->min2 = X.minimum;

                    X.firstTemp = thisRoot;
                    X.secondTemp = NULL;
                    return X;
                }
            } 
            else { //Case when the node is taller than the appropriate node and is a threeNode
                returnVal X;
                X = MergeNode(S1, S2, dh -1, thisRoot->third);

                if(X.secondTemp == NULL){
                    thisRoot->third = X.firstTemp;
                    X.firstTemp = thisRoot;
                    X.secondTemp = NULL;
                    return X;
                }else{
                    node* temp = twoNode(X.minimum, X.firstTemp, X.secondTemp);
                    thisRoot->third = NULL;

                    X.minimum = thisRoot->min2;
                    thisRoot->min2 = -1;
                    X.firstTemp = thisRoot;
                    X.secondTemp = temp;
                    return X;
                }
            }     
        }
    }else{ //S2 is to be inserted on the left of S1 at an appropriate height
        if(dh == 1){ //dh = Delta H = 1 is the candidate height for insertion/ merging
            returnVal X;
            if(thisRoot->third == NULL){ //Case where the appropriate node is a twoNode
                X.firstTemp = new node;
                X.firstTemp->third = thisRoot->second;
                X.firstTemp->second = thisRoot->first;
                X.firstTemp->first = S2;

                X.firstTemp->val = Min(S1);
                X.firstTemp->min2 = thisRoot->val;

                X.secondTemp = NULL;
                return X;
            }else{ //Case where the appropriate node is a threeNode
                X.firstTemp = new node;
                X.firstTemp->first = S2;
                X.firstTemp->second = thisRoot->first;
                X.firstTemp->val = Min(S1);
                X.firstTemp->third = NULL;
                X.firstTemp->min2 = -1;

                X.minimum = thisRoot->val;

                X.secondTemp = new node;
                X.secondTemp->first = thisRoot->second;
                X.secondTemp->second = thisRoot->third;
                X.secondTemp->val = thisRoot->min2;
                X.secondTemp->third = NULL;
                X.secondTemp->min2 = -1;
                return X;
            }
        }else{ //Case when the node is taller than the appropriate node and is a twoNode
            returnVal X;
            X = MergeNode(S1, S2, dh - 1, thisRoot->first);
            
            if(X.secondTemp == NULL){
                thisRoot->first = X.firstTemp;
                X.firstTemp = thisRoot;
                X.secondTemp = NULL;
                return X;
            }else{
                if(thisRoot->third == NULL){
                    thisRoot->third = thisRoot->second;
                    thisRoot->second = X.secondTemp;
                    thisRoot->first = X.firstTemp;
                    thisRoot->min2 = thisRoot->val;
                    thisRoot->val = X.minimum;
                    
                    X.firstTemp = thisRoot;
                    X.secondTemp = NULL;
                    return X;
                }else{
                    node* temp = twoNode(X.minimum, X.firstTemp, X.secondTemp);
                    thisRoot->first = thisRoot->second;
                    thisRoot->second = thisRoot->third;
                    thisRoot->third = NULL;

                    X.minimum = thisRoot->val;
                    thisRoot->val = thisRoot->min2;
                    thisRoot->min2 = -1;

                    X.firstTemp = temp;
                    X.secondTemp = thisRoot;
                    return X;
                }
            }
        }
    }
}
