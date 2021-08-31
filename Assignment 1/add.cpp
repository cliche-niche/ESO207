#include <iostream>
using namespace std;


class node{
    public:
        long long coef; //co-efficient
        long long expo; //exponent
        node* next;
        node* prev;
};


node* createSentinel(void){
    // Creates a sentinel node
    node* senti = new node;
    senti->coef = 0;
    senti->expo = -1; // Because each exponent is positive in the given polynomials
    senti->next = senti;
    senti->prev = senti;

    return senti;
}


node* createNode(long long coeff, long long exp){
    // Creates a new node with given coeff and exp
    node* temp = new node;
    temp->coef = coeff;
    temp->expo = exp;
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}



class poly{ //polynomial class
    public:
        long long size; // Number of terms in the polynomial
        node* sent = createSentinel(); //Each poly has a sentinel node of its own
        node* head = sent; // Initialisation

        void init(long long size); // Take input in a poly
        poly add(poly other); // Add "this" polynomial with "other" polynomial
        poly mul(poly other); // Multiply "this" polynomial with "other" polynomial
        void print(); // Prints a polynomial
        void deleteNode(node* del); // Deletes a polynomial
        void deleteZeroes(); // Deletes all terms with a zero co-efficient in a polynomial

};



int main(){
    
    long long n, m;
    cin >> n >> m;

    poly p, q;

    p.init(n);
    q.init(m);

    poly r = p.add(q);
    r.deleteZeroes(); // Remove any nodes with zero co-efficient in r
    r.print();

    return 0;
}



void poly::init(long long size){

    node* moving_head;
    
    for(long long i = 0; i < size; i++)
    {
        long long ai, ei;
        cin >> ai >> ei;
        node* termi = createNode(ai, ei);

        if(head == sent)
        {
            termi->prev = sent;
            head = termi;
            moving_head = head;
        }
        else
        {
            moving_head->next = termi;
            termi->prev = moving_head;
            moving_head = moving_head->next;
        }
    }

    moving_head->next = sent;
}


poly poly::add(poly other){
    
    poly r;
    
    // p=*this, q=other
    node * p = this->head;
    node * q = other.head;
    node * temp; // temporarily store the sum of two nodes in p and q
    node * move; // iterates over the resultant polynomial

    while(p != this->sent || q != other.sent){
        // iterate until end of both polynomials is reached
        
        // if end of one polynomial is reached, simply insert others' nodes in result until its end is reached 
        if(p == this->sent) 
        {
            temp = createNode(q->coef, q->expo);
            q = q->next;
            temp->prev = move;
            move->next = temp;
            move = move->next;
        }
        else if(q == other.sent)
        {
            temp = createNode(p->coef, p->expo);
            p = p->next;
            temp->prev = move;
            move->next = temp;
            move = move->next;
        }
        else{
            // make nodes in r in increasing order of exponent as both p and q 
            // have nodes in increasing order of exponents too
            if(p->expo > q->expo){
                temp = createNode(q->coef, q->expo);
                q = q->next;
            }else if(p->expo < q->expo){
                temp = createNode(p->coef, p->expo);
                p = p->next;
            }else{
                if(p->coef+q->coef == 0){ //don't make a node if resulting coefficient is zero.
                    p = p->next;
                    q = q->next;
                    continue;
                }
                temp = createNode(p->coef + q->coef, p->expo);
                p = p->next;
                q = q->next;
            }
            
            if(r.head == r.sent){
                temp->prev = r.sent;
                r.head = temp;
                move = r.head;
            }else{
                temp->prev = move;
                move->next = temp;
                move = move->next;
            }
        }
        
    }
    move->next = r.sent;

    return r;
}


poly poly::mul(poly other){
    poly r;
    long long c, e;
    
    // p=*this, q=other
    node* p = this->head;
    node* q = other.head;
    node* iter; // iterates over terms in the resultant polynomial r
    node* temp; // temporarily stores the resultant node made by multiplication of two nodes in p and q

    while(p != this->sent){
        q = other.head;
        while(q != other.sent){

            c = (p->coef)*(q->coef);
            e = p->expo + q->expo;

            if(r.head == r.sent){
                // Edge case for (first term of p) * (first term of q)
                temp = createNode(c, e);
                temp->next = r.sent;
                temp->prev = r.sent;
                r.head = temp;
                iter = r.head;
            }else{
                // we need to reach to the node (in r) which has exponent just <= e
                if(q == other.head){
                    // travelling backward is required only when it is first node in q
                    while(e < iter->expo){
                        iter = iter->prev;
                    } // reached to a node whose exponent is just less than or equal to e
                }
                else{
                    // otherwise travelling forward is required until we reach last node (not sentinel) or 
                    // we reach to a node (in r) whose exponent is just less than or equal to e
                    while(1){
                        if(iter->next == r.sent) break;
                        if(iter->next->expo <= e)
                            iter = iter->next;
                        else break;
                    }
                }
                
                if(e==iter->expo){
                    // If the exponent already exists in r, then just update the co-efficient
                    iter->coef += c;
                }else{
                    // Else, create a new node with the given co-efficients and exponent
                    temp = createNode(c, e);
                    temp->prev = iter;
                    temp->next = iter->next;
                    iter->next->prev = temp;
                    iter->next = temp;
                    iter = temp;
                }
            }
            q = q->next;
        }
        p = p->next;
    }

    return r;
}


void poly::print(){
    node* temp = head;
    while(temp != sent){
        cout << temp->coef << " " << temp->expo << " ";
        temp = temp->next;
    }
}


void poly::deleteNode(node* del){
    node* temp = this->head;

    del->next->prev = del->prev;
    del->prev->next = del->next;
    delete del;
}


void poly::deleteZeroes(){
    node *temp = this->head;
    while(temp != sent){
        if(temp->coef == 0){
            temp = temp->next;
            deleteNode(temp->prev);
        }else{
            temp = temp->next;
        }
    }
}