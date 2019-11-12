#include<iostream>
#include<vector>
#include<map>

using namespace std;

struct node{
    int index, vertex, weight;
};

struct point{
    node data;
    point* next;
};


// Function to Create Nodes
point* createNode(node payload){
    // Can use keyword new too
    point* newNode = (point*)malloc(sizeof(point));
    newNode->data = payload;
    newNode->next = NULL;
    return newNode;
}


// Function to Add Nodes
point* addNode(point* head, node payload){
    point* newNode = createNode(payload);
    if(head==NULL){
        return newNode;
    }
    // Head exists
    if(payload.weight<head->data.weight){
        newNode->next = head;
        return newNode;
    }else if(payload.weight==head->data.weight){
        if(payload.vertex<head->data.vertex){
            newNode->next = head;
            return newNode;
        }
    }
    point* prev = head;
    point* j = head->next;
    while(j){
        if(payload.weight>j->data.weight){
            // Check Next
            prev = j;
            j= j->next;
        }else if(payload.weight<j->data.weight){
            prev->next = newNode;
            newNode->next = j;
            return head;
            break;
        }else if(payload.weight==j->data.weight){
            if(payload.vertex<j->data.vertex){
                // Insert here
                prev->next = newNode;
                newNode->next = j;
                return head;
                break;
            }else{
                prev = j;
                j= j->next;
            }
        }
    }
    prev->next = newNode;
    newNode->next = j;
    // Now newNode is new Head
    return head;
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

/*
******************************************************************    
* MERGE SORT BEGIN
*****************************************************************
*/

void merge(vector<int> &A, int l, int m, int r){
    int n1=m-l+1,n2=r-m;
    int L[n1],R[n2];
    for(int i=0;i<n1;i++){
        L[i]=A[i+l];
    }
    for(int i=0;i<n2;i++){
        R[i]=A[i+m+1];
    }
    int i=0,j=0,k=l;
    while(i<n1&&j<n2){
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }
        else{
            A[k]=R[j];
            j++;
        }
        k++;
    }
    for(i=i;i<n1;i++){
        A[k]=L[i];
        k++;
    }
    for(j=j;j<n2;j++){
        A[k]=R[j];
        k++;
    }   
}

void mergeSort(vector<int> &A,int l, int r){
    if(l<r){
        int mid=(l+r)/2;
        mergeSort(A,l,mid);
        mergeSort(A,mid+1,r);
        merge(A,l,mid,r);
    }
}

/*
******************************************************************    
* MERGE SORT END   
*****************************************************************
*/


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
        cout<<head->data.vertex+1<<" "<<head->data.weight<<" "<< head->data.index<<endl;
        head = head->next;
    }
}

void dfs(vector<point*> &Adj, int n, Stack* &top, int* visited, int start){
    visited[start] = 1;
    point* head = Adj[start];
    while(head){
        int vertex = head->data.vertex;
        if(visited[vertex]==0){
            dfs(Adj, n, top, visited, vertex);
            // cout<<"INSERTING"<<start<<endl;
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
        prev = t1;
        t1 = t1->next;
    }

}
void dfs2(vector<point*> &AdjT, int n, int* visited, int start, vector<int> &comp){
    visited[start] = 1;
    point* head = AdjT[start];
    comp.push_back(start);
    while(head){
        int vertex = head->data.vertex;
        if(visited[vertex]==0){
            dfs2(AdjT, n, visited, vertex, comp);
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

void showAdj(vector<point*> t1){
    for(int i=0; i<t1.size(); i++){
        cout<<"for: "<<i+1<<endl;
        traversePoints(t1[i]);
        cout<<endl;
    }
}


void dfs3(vector<point*> &Adj, int n, Stack* &top, int* visited, int start, vector<int> &comp){
    visited[start] = 1;
    point* head = Adj[start];
    top = insertStackNode(top, start);
    while(head){
        if(head->data.weight!=0){
            head=head->next;
            continue;
        }
        int vertex = head->data.vertex;
        if(visited[vertex]==1){
            // pop till you get vertex and put in comp
            while(!isStackEmpty(top)){
                int top_vertex = getStackTop(top);
                comp.push_back(top_vertex);
                top = deleteStackNode(top);
                if(top_vertex==vertex){
                    break;
                }
            }
            return;
        }
        if(visited[vertex]==0){
            dfs3(Adj, n, top, visited, vertex, comp);
            // cout<<"INSERTING"<<start<<endl;
        }
        head = head->next;
    }
    top = deleteStackNode(top);
    visited[start] = 2;
}

void getCycles(vector<point*> &Adj, int n, vector< vector<int> > &comps){
    int visited[n] = { 0 };
    Stack* top = NULL;
    top = deleteStackNode(top);
    vector<int> comp;
    for(int i=0; i<n; i++){
        if(visited[i]==0){
            dfs3(Adj, n, top, visited, i, comp);
            if(comp.size()){
                comps.push_back(comp);
                comp.clear();
            }
        }
    }
}


struct int_node{
    int vertex;
    node payload;
};


void removeAllNonZeroPoints(vector<point*> &AdjT){
    int n = AdjT.size();
    for(int i=0; i<n; i++){
        point* j = AdjT[i];
        while(j){
            if(j->data.weight!=0){
                int t1 = j->data.index;
                j = j->next;
                removeNode(AdjT[i], t1);
            }else{
                j = j->next;
            }
        }
    }
}

void driver(vector<point*> &AdjT, int n, int start, int no_of_edges){
    point* t1;
    // DEBUG PRINT

    for(int i=0; i<n; i++){
        // For ith point, finding min edge weight
        t1 = AdjT[i];
        int minWt = INT_MAX;
        while(t1){
            // CHECK : Handling Self Loops
            if(t1->data.vertex==i){
                t1=t1->next;
                continue;
            }
            minWt = min(minWt, t1->data.weight);
            t1 = t1->next;
        }
        t1 = AdjT[i];
        // Deleting minWt from all edges from ith point
        while(t1){
            if(t1->data.vertex==i){
                t1=t1->next;
                continue;
            }
            t1->data.weight -=minWt;
            t1=t1->next;
        }
    }
    // NOTE: NO need to worry that points are not sorted. Since I am anyhow going to make newAdjT to make sure that I send the best.

    node temp;
    int source;

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
            t1 = t1->next;
        }
    }
    vector< vector<int> > comps;
    getCycles(newAdjT, n, comps);

    /*
        SUMMARY TILL NOW.
        newAdjT and AdjT are my potential arborescence.
    */

    // Making SuperNode, in newAdjT
    vector<int_node> node_invisible;
    int node_transfer[no_of_edges];
    int name_change[no_of_edges];
    for(int capf=0; capf<no_of_edges; capf++){
        node_transfer[capf] = name_change[capf] = -1;
    }
    int flag=0;

    for(int i=0; i<comps.size(); i++){
        // Cycle of 1 length
        if(comps[i].size()<=1){
            if(comps[i].size()==0){
                cout<<"[CHECK]ZERO SIZED CYCLE1! NOT POSSIBLE!";
            }
            continue;
        }
        flag=1;
        // min_index will have minimum index in the cycle. Supernode index = min_index
        int min_index = INT_MAX;
        int size = comps[i].size();
        for(int j=0; j<size; j++){
            min_index = min(min_index, comps[i][j]);
        }

        for(int j=0; j<size; j++){
            int num = comps[i][j];
            // Excluding changes to the supernode_index
            
            point* k = newAdjT[num];
            // TODO: num ki adjacency list se saare nodes going to any node other than this SCC ko min_index mein shift karna h
            // Else unki visibility false karni h
            while(k){
                // cout<<k->data.index<<endl;
                int dest = k->data.vertex;
                int is_dest_to_cycle=0;
                for(int qwe=0; qwe<comps[i].size(); qwe++){
                    if(dest==comps[i][qwe]){
                        is_dest_to_cycle=1;
                        break;
                    }
                }
                // trying to either make the node invisible or transfer of num
                // If the edge destination is an internal point
                if(is_dest_to_cycle){
                    node payload = k->data;
                    int_node u1;
                    u1.vertex = num;
                    u1.payload = payload;
                    // Adding to node_invisible
                    node_invisible.push_back(u1);
                    k=k->next;
                    removeNode(newAdjT[num], payload.index);
                }else{
                    // If from supernode_index outer edge is going! Then Not deleting it. 
                    if(comps[i][j]==min_index){
                        k = k->next;
                        continue;
                    }
                    // If the edge destination is an not an internal point 
                    // Adding to node_transfer
                    node_transfer[k->data.index] = num;
                    newAdjT[min_index] = addNode(newAdjT[min_index], k->data);
                    int foo = k->data.index;
                    k = k->next;
                    removeNode(newAdjT[num], foo);
                }
            }

        }
    }
    // Till Now num k nodes min ko transfer/delete kar diye. It's adjacency list should be empty now.

    // Changing names of all num from num to min_index
    for(int i=0; i<comps.size(); i++){
        if(comps.size()<=1){
            continue;
        }
        int min_index = INT_MAX;
        int size = comps[i].size();
        for(int j=0; j<size; j++){
            min_index = min(min_index, comps[i][j]);
        }

        for(int j=0; j<size; j++){
            int num = comps[i][j];
            // For all points inside the component except min_vertex whose name need not be changed
            if(num==min_index){
                continue;
            }
            // Traversing whole!
            for(int u1=0; u1<n; u1++){
                point* k = newAdjT[u1];
                // DEBUG PRINT
                if(u1==num){
                    if(newAdjT[num]!=NULL){
                        cout<<"[ERROR] YOU SHOULD BE ZERO BY NOW"<<endl;
                    }
                }
                while(k){
                    // If destination is num i.e destination to cycle
                    if(k->data.vertex==num){
                        name_change[k->data.index] = num;
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
        // Deleting all edges with non-zeros weights
        removeAllNonZeroPoints(AdjT);
        return;
    }

    driver(newAdjT, n, start, no_of_edges);
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

    // Transferred Nodes ko delete karna h and original adj mein daalna h
    for(int i=0; i<newAdjT.size(); i++){
        point* j = newAdjT[i];
        while(j){
            int dest = j->data.vertex;
            int bar=0;
            if(node_transfer[j->data.index]!=-1){
                int original_vertex = node_transfer[j->data.index];
                node_transfer[j->data.index] = -1;
                // I am pushing updated data to newAdjT. Good Thing. As if there are any changes then it is retained.
                newAdjT[original_vertex] = addNode(newAdjT[original_vertex], j->data);
                int foo = j->data.index;
                j = j->next;
                removeNode(newAdjT[i], foo);
            }else{
                // Moving the pointer 1 step only if there is no deletion
                j = j->next;
            }
        }
    }
    // All edges coming from any node to cycle is made invisible.
    for(int it=0; it<node_invisible.size(); it++){
        int_node t1 = node_invisible[it];
        int_node u1;
        node payload = t1.payload;
        int vertex = t1.vertex;
        // if payload.weight is not zero it means it is not a part of arborescence and it will never be. Thus excluding them.
        if(payload.weight==0){
            newAdjT[vertex] = addNode(newAdjT[vertex], payload);
        }
    }

    // Removing 1 edge(inside of cycle) and adding 1 edge(outside of cycle)
    // SUMMARY - adjT is where I need to give final Answer. Right Now newAdjT has 1 extra edge. 
    // I need to give that edge to adjT and remove one from it.

    /* 
        I want to remove all non zeros nodes from AdjT. Whatever left have atleast 1 cycle. I will try to check for those nodes whose size is
        exactly 2. I will then compare it with newAdjT. newAdjT will have 1 extra node. I will remove the cyclic node from newAdjT.
        NOTE: newAdjT even after adding all nodes will not have a single non-zero edge
    */

    // Removing all non-zero Points
    removeAllNonZeroPoints(AdjT);


    for(int i=0; i<n; i++){
        int size = 0;
        point* j = newAdjT[i];
        while(j){
            size++;
            j = j->next;
        }
        if(size>2){
            cout<<"SIZE IS NOT 2, LOGIC FAILURE. SIZE IS "<<size<<endl;
            continue;
        }else if(size<2){
            // Indegree is less than or equal to 1. NO PROBLEM
            continue;
        }
        // Only if size is 2.

        // Don't know! This case is not possible! Start ki AdjT mein zero Indexes Honge
        if(i==start-1){
            continue;
        }
        size=0;

        int index = newAdjT[i]->data.index;
        int index1 = (newAdjT[i]->next)->data.index;
        int cycle_index = AdjT[i]->data.index;

        if(cycle_index==index){
            removeNode(newAdjT[i], index);
        }else if(cycle_index==index1){
            removeNode(newAdjT[i], index1);
        }else{
            cout<<"WRONG LOGIC! KISI EKK KO TOH SAME HONA THA."<<endl;
        }
    }
    AdjT = newAdjT;
}

bool binarySearch(vector<int> &arbor, int size, int index){
    int l = 0;
    int r = size-1;
    int mid;
    while(l<=r){
        mid = (l+r)/2;
        if(arbor[mid]==index){
            return true;
        }else if(arbor[mid]>index){
            r = mid-1;
        }else{
            l = mid+1;
        }
    }
    return false;
}

void dijkstra(vector< long long > &distance, vector<point*> &A, int n){
    int visited[n] = { 0 };
    for(int i=0; i<n; i++){
        int x = -1;
        // To find Minimum
        for(int j=0; j<n; j++){
            if((visited[j]==0) && ((x==-1) || (distance[x]>distance[j]))){
                x = j;
            }
        }
        if(x==-1){
            continue;
        }
        visited[x] = 1;
        // Driver Code
        point* j = A[x];
        while(j){
            int dest = j->data.vertex;
            long long newDist = distance[x]+j->data.weight;
            if(distance[dest]>newDist){
                distance[dest] = newDist;
            }
            j = j->next;
        }
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
        vector<point*> Adj(n, NULL);
        for(int i=0; i<m; i++){
            cin>>source>>dest>>wt;
            source-=1;
            dest-=1;
            payload.index = i;
            payload.vertex = source;
            payload.weight = wt;
            point* j = AdjT[dest];
            int h1=0;
            // Checking if an edge already exist. If yes then, I am only updating.
            while(j){
                if(j->data.vertex==source){
                    h1=1;
                    if(j->data.weight>wt){
                        j->data.weight = wt;
                    }
                    break;
                }
                j = j->next;
            }
            if(h1==0){
                AdjT[dest] = addNode(AdjT[dest], payload);
                payload.vertex = dest;
                Adj[source] = addNode(Adj[source], payload);
            }
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
            if(i==start-1){
                if(size!=0){
                    cout<<"-1"<<endl;
                    flag=1;
                    break;
                }
            }else if(size==0){
                cout<<"UNREACHABILITY"<<endl;
            }
        }
        if(flag==1){
            continue;
        }
        driver(AdjT, n, start, m);
        vector<int> arbor;
        for(int u1=0; u1<n; u1++){
            point* u2 = AdjT[u1];
            while(u2){
                arbor.push_back(u2->data.index);
                u2= u2->next;
            }
        }
        int arbor_size = arbor.size();
        mergeSort(arbor, 0, arbor_size-1);
        long long total_cost=0;
        for(int u1=0; u1<n; u1++){
            point* u2 = Adj[u1];
            while(u2){
                if(binarySearch(arbor, arbor_size, u2->data.index)){
                    total_cost+=u2->data.weight;
                    u2 = u2->next;
                }else{
                    int foo = u2->data.index;
                    removeNode(Adj[u1], u2->data.index);
                    u2 = u2->next;
                }
            }
        }
        vector<long long> distance(n, INT_MAX);
        distance[start-1] = 0;
        dijkstra(distance, Adj, n);
        cout<<total_cost<<" ";
        for(int i=0; i<n; i++){
            cout<<distance[i]<<" ";
        }
        cout<<endl;
        
        deallocateDriver(AdjT, n);
    }

    return 0;
}