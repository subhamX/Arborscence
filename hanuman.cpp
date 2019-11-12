#include<iostream>
#include<vector>
#include<map>

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
    newNode->visible = false;
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
void removeNode(point* &head, int index){
    // Head is NULL
    if(head==NULL){
        return;
    }
    // Head index equals given index [WORKS FOR BOTH SINGLE NODE AND MULIPLE NODES]
    if(((head->data).index==index)){
        point* h1 = head->next;
        free(head);
        head = h1;
        return ;
    }
    // General Case
    point* prev = head;
    point* t1 = head->next;
    while(t1){
        if((t1->data).index==index){
            prev->next = t1->next;
            free(t1);
            return;
        }
        prev = t1;
        t1=t1->next;
    }
    cout<<"COMMENT - NOT FOUND";
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
void removepNode(point* &head, point* &j){
    if(j==NULL){
        return;
    }
    if(head==NULL){
        return;
    }
    if((head==j)){
        point* t1 = head->next;
        free(head);
        head=j=t1;
        return;
    }
    point* prev = head;
    point* t1 = head->next;
    while(t1!=NULL){
        if(t1==j){
            j = j->next;
            prev->next = j;
            free(t1);   
            return;
        }
        cout<<"EHEHE";
        prev = t1;
        t1 = t1->next;
    }

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
void getSCC(vector<point*> &Adj, vector<point*> &AdjT, int n, vector< vector<int> > &comps){
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


void driver(vector<point*> &AdjT, int n, int start){
    point* t1;
    for(int i=0; i<n; i++){
        t1 = AdjT[i];
        int minWt = INT_MAX;
        while(t1){
            minWt = min(minWt, t1->data.weight);
            t1 = t1->next;
        }
        t1 = AdjT[i];
        // Changing in Traspose List
        while(t1){
            t1->data.weight -=minWt;
            // Making it visible only if Weight is true
            if(t1->data.weight==0){
                t1->visible = true;
            }
            t1=t1->next;
        }
    }
    cout<<"WORKING"<<endl;
    // Creating Transpose List
    vector<point*> Adj(n);
    node temp;
    int source;
    for(int i=0; i<n; i++){
        t1 = AdjT[i];
        while(t1){
            temp.index = t1->data.index;
            temp.vertex = i;
            temp.weight = t1->data.weight;
            source = t1->data.vertex;
            Adj[source] = addNode(Adj[source], temp);
            // If t1 edge is not visible in AdjT then it is not visible in Adj
            Adj[source]->visible = t1->visible;
            t1 = t1->next;
        }
    }

    vector< vector<int> > comps;
    getSCC(Adj, AdjT, n, comps);

    // Copying Data to newAdjT
    vector<point*> newAdjT(n);
    for(int i=0; i<n; i++){
        t1 = AdjT[i];
        while(t1){
            temp.index = t1->data.index;
            temp.vertex = t1->data.vertex;
            temp.weight = t1->data.weight;
            source = i;
            newAdjT[source] = addNode(newAdjT[source], temp);
            // If t1 edge is not visible in AdjT then it is not visible in newAdjT
            newAdjT[source]->visible = t1->visible;
            t1 = t1->next;
        }
    }

    /*
        SUMMARY TILL NOW.
        Adj and AdjT are my potential arborescence.(consider only those with visible=true)
    */

    // Making SuperNode, in newAdjT
    int node_transfer[n] = { -1 };
    int name_change[n] = { -1 };
    int flag=0;
    for(int i=0; i<comps.size(); i++){
        if(comps[i].size()==1){
            continue;
        }
        flag=1;
        // min_index will have minimum index in the cycle. We will reduce the supernode to that index.
        int min_index = INT_MAX;
        int size = comps[i].size();
        for(int j=0; j<size; j++){
            min_index = min(min_index, comps[i][j]);
        }
        for(int j=0; j<size; j++){
            int num = comps[i][j];
            if(comps[i][j]==min_index){
                continue;
            }
            point* k = newAdjT[num];
            while(k){
                node_transfer[k->data.index] = num;
                // min_index ko ADD kiya and khud ki visibility ZERO
                newAdjT[min_index] = addNode(newAdjT[min_index], k->data);
                k->visible = false;
                cout<<"CALLING 1: "<<num<<" "<<k->data.vertex<<endl;
                int foo = k->data.index;
                k = k->next;

                removeNode(newAdjT[num], foo);

            }
            // Till Now num k nodes min ko transfer kar diye.
            for(int u1=0; u1<n; u1++){
                point* k = newAdjT[u1];
                while(k){
                    if(k->data.vertex==num){
                        name_change[k->data.index] = k->data.vertex;
                        k->data.vertex = min_index;
                    }
                    k = k->next;
                }
            }
        }
    }

    // Till Now SuperNode Ban Chuka h. And it is in newAdjT
    if(flag==0){
        // There is no cycle. i.e No SuperNode. It means AdjT and newAdjT is Arborescence. 
        // return AdjT;
        return;
    }
    driver(newAdjT, n, start);
    
    // Changing Names
    for(int i=0; i<newAdjT.size(); i++){
        point* j = newAdjT[i];
        while(j){
            if(name_change[j->data.index]!=-1){
                // There was some name change
                j->data.vertex = name_change[j->data.index];
            }
            j = j->next;
        }
    }
    // Transferred Nodes ki visibility true karni h
    for(int i=0; i<newAdjT.size(); i++){
        point* j = newAdjT[i];
        while(j){
            if(node_transfer[j->data.index]!=-1){
                int original_vertex = node_transfer[j->data.index];
                newAdjT[original_vertex] = addNode(newAdjT[original_vertex], j->data);
                cout<<"CALLING 2: "<<i<<" "<<j->data.vertex<<endl;
                int foo = j->data.index;
                j = j->next;
                removeNode(newAdjT[i], foo);
            }else{
                // Moving the pointer 1 step only if there is no deletion
                j = j->next;
            }
        }
    }
    // Removing 1 edge(inside of cycle) and adding 1 edge(outside of cycle)
    // SUMMARY - adjT is where I need to give final Answer. Right Now newAdjT has 1 extra edge. 
    // I need to give that edge to adjT and remove one from it.

    for(int i=0; i<n; i++){
        int size = 0;
        point* j = newAdjT[i];
        while(j){
            size++;
            j = j->next;
        }
        if(size==2){
            cout<<"SIZE IS 2"<<endl;
        }else if(size>2){
            cout<<"SIZE IS NOT 2, LOGIC FAILURE. SIZE IS "<<size<<endl;
        }else{
            cout<<"SIZE IS NOT 2, IT IS "<<size<<endl;
        }
        // Indegree is less than or equal to 1. NO PROBLEM
        if(size<=1){
            continue;
        }
        if(i==start){
            continue;
        }
        int index = newAdjT[i]->data.index;
        int index1 = (newAdjT[i]->next)->data.index;
        int cycle_index = AdjT[i]->data.index;
        if(cycle_index==index){
            AdjT[i]->visible = false;
        }else if(cycle_index==index){
            (AdjT[i]->next)->visible = false;
        }else{
            cout<<"WRONG LOGIC! KISI EKK KO TOH SAME HONA THA."<<endl;
        }
    }
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
        vector<point*> AdjT(n, NULL);
        for(int i=0; i<m; i++){
            cin>>source>>dest>>wt;
            source-=1;
            dest-=1;
            payload.index = i;
            payload.vertex = source;
            payload.weight = wt;
            AdjT[dest] = addNode(AdjT[dest], payload);
        }
        // TODO : Check if all nodes has atleast 1 indegree.(except start). If No print -1;
        int flag=0;
        for(int i=0; i<n; i++){
            int size=0;
            point* j = AdjT[i];
            while(j){
                j = j->next;
                size++;
            }
            if(i==start){
                if(size!=0){
                    cout<<"-1"<<endl;
                    flag=1;
                    break;
                }
            }
            if(size==0){
                cout<<"UNREACHABILITY"<<endl;
                // flag=1;
                // break;`
            }
        }
        if(flag==1){
            continue;
        }
        driver(AdjT, n, start);
        for(int i=0; i<n; i++){
            cout<<i+1<<": "<<endl;
            point* j = AdjT[i];
            while(j){
                cout<<j->data.vertex+1<<" "<<j->data.index<<" "<<j->data.weight<<endl;
                j= j->next;
            }
        }
        deallocateDriver(AdjT, n);
    }

    return 0;
}