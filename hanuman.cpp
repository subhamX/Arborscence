#include<iostream>
#include<vector>

using namespace std;

struct node{
    int index, vertex, weight;
};

struct point{
    node data;
    bool visible;
    point* next;
};


// Function to Create Nodes
point* createNode(node payload){
    // Can use keyword new too
    point* newNode = (point*)malloc(sizeof(point));
    newNode->data = payload;
    newNode->visible = true;
    newNode->next = NULL;
    return newNode;
}


// Function to Add Nodes
point* addNode(point* head, node payload){
    point* newNode = createNode(payload);
    if(head==NULL){
        return newNode;
    }
    newNode->next = head;
    // Now newNode is new Head
    head = newNode;
    return newNode;
}

// Function to Remove Nodes
point* remove(point* head, int index){
    // Head is NULL
    if(head==NULL){
        return head;
    }
    // Head index equals given index [WORKS FOR BOTH SINGLE NODE AND MULIPLE NODES]
    if(((head->data).index==index)){
        point* h1 = head->next;
        free(head);
        return h1;
    }
    // General Case
    point* prev = head;
    point* t1 = head->next;
    while(t1){
        if((t1->data).index==index){
            prev->next = t1->next;
            free(t1);
            return head;
        }
        prev = t1;
        t1=t1->next;
    }
    cout<<"COMMENT - NOT FOUND";
    return head;
}

// Function to Check if Node with index exist
bool isPresent(point* head, int index){
    if(head==NULL){
        return false;
    }

    // Traversing
    while(head){
        if((head->data).index==index){
            // CASE - Found
            return true;
        }
        head = head->next;
    }
    // CASE - Not Found
    return false;
}


// STACK FUNCTIONS START
struct Stack{
    int data;
    Stack* next;
};

Stack* insertStackNode(Stack* top, int data){
    if(top==NULL){
        Stack* temp = (Stack*)malloc(sizeof(Stack));
        temp->data = data;
        temp->next=NULL;
        return temp;
    }
    Stack* temp = insertStackNode(NULL, data);
    temp->next = top;
    return temp;
}

Stack* deleteStackNode(Stack*top){
    if(top==NULL){
        return NULL;
    }else if(top->next==NULL){
        free(top);
        return NULL;
    }
    Stack* t = top->next;
    free(top);
    return t;
}
bool isStackEmpty(Stack* top){
    if(top==NULL){
        return true;
    }
    return false;
}
int getStackTop(Stack* top){
    if(top==NULL){
        return INT_MIN;
    }
    return top->data;
}

// STACK FUNCTIONS END





void deallocate(point* head){
    while(head){
        point* t1 = head->next;
        free(head);
        head = t1;
    }
}

void deallocateDriver(vector<point*> &Adj, int n){
    for(int i=0; i<n; i++){
        deallocate(Adj[i]);
    }
}

void traversePoints(point* head){
    while(head){
        cout<<head->data.index<<" "<<head->data.vertex<<" "<< head->data.weight<<endl;
        head = head->next;
    }
    cout<<endl;
}

void dfs(vector<point*> &Adj, int n, Stack* &top, int* visited, int start){
    visited[start] = 1;
    point* head = Adj[start];
    while(head){
        // Checking if the 
        if(head->visible){
            int vertex = head->data.vertex;
            if(visited[vertex]==0){
                dfs(Adj, n, top, visited, vertex);
                // cout<<"INSERTING"<<start<<endl;
            }
        }
        head = head->next;
    }
    top = insertStackNode(top, start);
}

void dfs2(vector<point*> &AdjT, int n, int* visited, int start, vector<int> &comp){
    visited[start] = 1;
    point* head = AdjT[start];
    comp.push_back(start);
    while(head){
        if(head->visible){
            int vertex = head->data.vertex;
            if(visited[vertex]==0){
                dfs2(AdjT, n, visited, vertex, comp);
            }
        }
        head= head->next;
    }
}
void getSCC(vector<point*> &Adj, int n, vector< vector<int> > &comps){
    vector<point*> AdjT(n);
    point* t1;
    node temp;
    int source;
    for(int i=0; i<n; i++){
        t1 = Adj[i];
        while(t1){
            temp.index = t1->data.index;
            temp.vertex = i;
            temp.weight = t1->data.weight;
            source = t1->data.vertex;
            AdjT[source] = addNode(AdjT[source], temp);
            t1 = t1->next;
        }
    }
    int visited[n] = { 0 };
    Stack* top = NULL;
    for(int i=0; i<n; i++){
        if(visited[i] == 0){
            // Sending top of stack by reference
            dfs(Adj, n, top, visited, i);
        }
    }
    for(int i=0; i<n; i++){
        visited[i] = 0;
    }
    vector<int> comp;
    while(!isStackEmpty(top)){
        int start = getStackTop(top);
        top = deleteStackNode(top);
        if(visited[start]==0){
            dfs2(AdjT, n, visited, start, comp);
            comps.push_back(comp);
            comp.clear();
        }
    }
}


void driver(vector<point*> &Adj, int n, int start){
    vector< vector<int> > comps;
    getSCC(Adj, n, comps);


    cout<<"PRINTING SCC:"<<endl;
    for(int i=0; i<comps.size(); i++){
        for(int j=0; j<comps[i].size(); j++){
            cout<<comps[i][j]<<endl;
        }
        cout<<endl;
    }
}


int main(){
    point* head = NULL;
    node payload;
    int t;
    cin>>t;
    int n, start, m, source, dest, wt;
    while(t--){
        cin>>n>>start>>m;
        vector<point*> Adj(n, NULL);
        for(int i=0; i<m; i++){
            cin>>source>>dest>>wt;
            source-=1;
            dest-=1;
            payload.index = i;
            payload.vertex = dest;
            payload.weight = wt;
            Adj[source] = addNode(Adj[source], payload);
        }
        // TODO : Check if all nodes has atleast 1 indegree.(except start). If No print -1;

        driver(Adj, n, start);
        deallocateDriver(Adj, n);
    }

    return 0;
}