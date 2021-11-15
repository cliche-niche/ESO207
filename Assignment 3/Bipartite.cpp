#include <iostream>
#include <cassert> // Used assert function from the library to check the stack overflow/underflow
using namespace std;


class graph;

class node{ // A simple class for a node in a singly linked list
    private:
        int val;
        node* next=NULL;

    public:
        node(int v){
            val=v;
        }
        ~node(){ // Deletes the whole linked list
            if(this->next != NULL){
                delete this->next;
            }
        }

        // Declared to access private variables
        friend class graph;
        friend bool Bipartite(graph(&g), int vset[]);
        friend void dfs(int x, graph (&g), bool visited[], int distance[]);
};


class graph{
    private:
        int size=0; // Size of the Vertices set, used interchangeably with set of vertices and size
        node** adj_list; // Adjacency list of all the vertices in the graph. Just an array of linked lists
    public:
        graph(int n){ // Initialisation
            size = n;
            adj_list = new node*[size];
            for(int i=0; i<size; i++){
                adj_list[i] = NULL;
            }
        }
        ~graph(){ // Deletes each node in each linked list
            for(int i=0; i<size; i++){
                if(adj_list[i] != NULL){
                    delete adj_list[i];
                }
            }
            delete[] adj_list;
        }
        void insert(int x, int y){ // Inserts the undirected edge in the respective adjacency lists of the graph
            node* temp;
            temp = new node(y); temp->next = adj_list[x]; adj_list[x] = temp;
            temp = new node(x); temp->next = adj_list[y]; adj_list[y] = temp;
        }
        
        // Declared to access private variables
        friend bool Bipartite(graph (&g), int vset[]);
        friend void dfs(int x, graph (&g), bool visited[], int distance[]);
};

class Stack{ // Simple Implementation of a Stack 
    private:
        int top=0, size=0;
        int* stack;
    public:
        Stack(int n){ // Initialisation
            size = n+5; // Just a safe measure
            stack = new int[size];
        }
        ~Stack(){
            delete[] stack;
        }
        
        // Member functions that a stack supports
        void push(int v){
            assert(top+1<size); // Checks for Stack Overflow
            top++;
            stack[top]=v;
        }
        int pop(){
            assert(top); // Checks for Stack Underflow
            top--;
            return stack[top+1];
        }
        bool is_empty(){
            return (top==0);
        }
};


void dfs(int x, graph (&g), bool visited[], int distance[]){ 
    // Ordinary Dfs, assigns each node minimum distance from the vertex with minimum value in the connected component
    
    Stack dfs_stack(g.size); // Stack used to implement a non-recursive version of Depth-first search
    int y;

    dfs_stack.push(x); // Initialisation of the stack
    
    visited[x] = true; // Same array as Bipartite function

    while(!dfs_stack.is_empty()){
        y = dfs_stack.pop();

        for(node* iter = g.adj_list[y]; iter != NULL; iter=iter->next){
            if(visited[iter->val] == false){ // Ensures that each node in the connected component pushed into the stack exactly once
                visited[iter->val] = true;
                dfs_stack.push(iter->val);
            }
            if(distance[iter->val] > distance[y]+1){ // Assigns the minimum distance from the vertex with minimum value in the connected component
                distance[iter->val] = distance[y]+1;
            }
        }
    }

}

bool Bipartite(graph (&g), int vset[]){ 
    /*  Boolean function which returns whether a graph is Bipartite or not.
        If it is Bipartite, then the sets are assigned to each vertex in vset.  */

    int size = g.size;
    bool visited[size]; // Boolean array keeping track of whether a node is visited or not 
    int distance[size]; // Array storing the minimum distance from the vertex with minimum value in the connected component

    for(int i=0; i<size; i++){ // Initialization, each node is unvisited and gets an impossible distance (infinity)
        visited[i]=false; distance[i]=size+10;
    }

    // int connected_components = 0; // Keeps track of number of connected components in the graph
    for(int i=0; i<size; i++){
        if(visited[i] == false){ // dfs executed on each connected component exactly once
            distance[i] = 0;
            dfs(i, g, visited, distance);
            // connected_components++;
        }
    }
    /*
        Assuming the graph to be bipartite
        1. We can check if multiple bipartitions are possible in the above for loop itself.
        2. If the "connected_components" are greater than 1, 
        then there are more than 1 partitions of the graph possible.
        3. The exact number would be 2^{connected_components - 1}. (Considering partition to be unordered, i.e., {V_1, V_2} = {V_2, V_1})
    */

    for(int i=0; i<size; i++){
        for(node* iter = g.adj_list[i]; iter != NULL; iter = iter->next){
            /*
                A graph is bipartite if and only if, the distance of nodes 
                in an edge have opposite parity (in essence, odd and even)
            */
            if(distance[i]%2 == distance[iter->val]%2){
                return false;
            }
        }
    }

    for(int i=0; i<size; i++){ // If the graph is bipartite, then each vertex is assigned a certain set (with 0 being assigned 1)
        vset[i] = 1 + (distance[i]%2);
    }

    return true;
}

int main(){

    int v, e;
    cin>>v>>e; // Input

    graph g(v); int vset[v];

    // Input
    int x, y;
    for(int i=0; i<e; i++){
        cin>>x>>y;
        g.insert(x, y);
    }

    if(Bipartite(g, vset)){
        
        cout<<"YES\n";
        for(int i=0; i<v; i++){
            cout<<vset[i]<<'\n';
        }
        
    }else{
        cout<<"NO";
    }

    return 0;
}