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

struct int_node{
    int vertex;
    node payload;
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

void showAdj(vector<point*> t1){
    for(int i=0; i<t1.size(); i++){
        cout<<"for: "<<i+1<<endl;
        traversePoints(t1[i]);
        cout<<endl;
    }
}

void dfs(vector<point*> &Adj, int n, int* visited, int start){
    visited[start] = 1;
    point* head = Adj[start];
    while(head){
        int vertex = head->data.vertex;
        if(visited[vertex]==0){
            dfs(Adj, n, visited, vertex);
        }
        head = head->next;
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
            cout<<"vertex: "<<vertex<<endl;
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
        }
        head = head->next;
    }
    top = deleteStackNode(top);
    visited[start] = 2;
}

/**
 * 
 * Function to get cycles array in any graph.
 * PARAMS:
 * Adj is the Adjacency List. 
 * n is number of nodes
 * 
 * comps will be filled by getCycles with different components.
 * 
 * This function calls dfs3 to traverse the graph.
 **/

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


/**
 * 
 * Function to Remove All Non-Zero Points from Adjacency List
 * 
 * PARAMS:
 * AdjT or Adjacency List
 * 
 **/
void removeAllNonZeroPoints(vector<point*> &AdjT){
    int n = AdjT.size();
    for(int i=0; i<n; i++){
        point* j = AdjT[i];
        while(j){
            if(j->data.weight!=0){
                int t1 = j->data.index;
                j = j->next;
                cout<<"REMOVING WITH INDEX: "<<t1<<endl;
                removeNode(AdjT[i], t1);
            }else{
                j = j->next;
            }
        }
    }
}

/**
 * 
 * Function for binary search
 * 
 * 
 **/
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


/**
 * 
 * Driver Code
 * 
 * PARAMS: 
 * @param[in] AdjT : Adjacency List
 * @param[in] n : No. Of Vertices
 * @param[in] start : Start Index
 * @param[in] no_of_edges : Number Of Edges
 * 
 * FUNCTIONALITY: It reduces AdjT to an arborescence.
 * 
 **/
void driver(vector<point*> &AdjT, int n, int start, int no_of_edges){
    point* t1;

    // DEBUG PRINT
    cout<<"INITIAL"<<endl;
    showAdj(AdjT);

    // Reducing All Edge Weights By Subtracting from minWt 
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
    // NOTE: Points are not sorted and neither in lexicographically in AdjT right now.

    // DEBUG PRINT
    cout<<"AFTER REDUCTION"<<endl;
    showAdj(AdjT);

    // vector<point*> Adj(n);
    node temp;
    int source;

    // Creating newAdj List from AdjT
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
    // Deallocating All Points inside AdjT
    deallocateDriver(AdjT, n);
    AdjT.clear();
    AdjT.resize(n);

    // DEBUG PRINT
    cout<<"AFTER DEALLOCATION:\n";
    showAdj(AdjT);

    // Making Sorted AdjT. [Copying data from newAdjT to AdjT]
    for(int i=0; i<n; i++){
        t1 = newAdjT[i];
        while(t1){
            temp.index = t1->data.index;
            temp.vertex = t1->data.vertex;
            temp.weight = t1->data.weight;
            source = i;
            AdjT[source] = addNode(AdjT[source], temp);
            t1 = t1->next;
        }
    }


    // Keeping only 1 zero node in AdT;
    point* temp1 = NULL;
    for(int i=0; i<n; i++){
        point* j = AdjT[i];
        while(j){
            point* k = j->next;
            while(k){
                point* temp1 = k->next;
                removeNode(AdjT[i], k->data.index);
                k = temp1;
            }

            // IMPORTANT: CHECK IF NEEDED
            if(j->data.weight!=0){
                removeNode(AdjT[i], j->data.index);
            }
            j=NULL;
        }
    }

    // DEBUG PRINT
    cout<<"PRINT ADJ: IT SHOULD HAVE ALL ZEROES\n";
    showAdj(AdjT);

    // Now every node in AdjT has only 1 point with Zero Index Only. Since at any stage I need to have only 1 outward edge[in AdjT]. 
    // [Indegree should be Zero]
    // Also Points are in Lexicographically sorted.

    // Calling getCycles to get Cycles. Using AdjT where there are only zero nodes.
    vector< vector<int> > comps;
    getCycles(AdjT, n, comps);

    // DEBUG PRINT
    cout<<"PRINTING CYCLES:"<<endl;
    for(int i=0; i<comps.size(); i++){
        cout<<"SIZE OF "<<i<<" CYCLE "<<comps[i].size()<<endl;
        for(int j=0; j<comps[i].size(); j++){
            cout<<comps[i][j]+1<<endl;
        }
        cout<<endl;
    }

    /*
        SUMMARY TILL NOW.
        AdjT has an arborescence.
        newAdjT has additional details edges.

    */

    // Making SuperNode, in newAdjT
    vector<int_node> node_invisible;
    int node_transfer[no_of_edges];
    int name_change[no_of_edges];

    // Initializing node_transfer and name_change to -1
    for(int capf=0; capf<no_of_edges; capf++){
        node_transfer[capf] = name_change[capf] = -1;
    }
    // controls if answer should be returned
    int flag=0;

    cout<<"MAKING SUPERNODE\n";
    for(int i=0; i<comps.size(); i++){
        // If cycle only has 1 node. Then continue; 
        if(comps[i].size()<=1){
            continue;
        }
        flag=1;
        // min_index has minimum index in the cycle. Supernode index = min_index
        int min_index = INT_MAX;
        int size = comps[i].size();
        for(int j=0; j<size; j++){
            min_index = min(min_index, comps[i][j]);
        }

        cout<<"MIN INDEX:"<<min_index+1<<"\n";

        // Traversing all points of ith cycle
        for(int j=0; j<size; j++){
            int num = comps[i][j];
            point* k = newAdjT[num];

            // TODO: num ki adjacency list se saare nodes going to any node other than this SCC ko min_index mein shift karna h
            // Traversing Adjacency matrix of AdjT
            while(k){
                cout<<"INDEX ID: "<<k->data.index<<"DESTINATION-VERTEX"<<k->data.vertex+1<<endl;
                int dest = k->data.vertex;
                int is_dest_to_cycle=0;
                // Checking if destination of this edge is to cycle
                for(int qwe=0; qwe<comps[i].size(); qwe++){
                    if(dest==comps[i][qwe]){
                        is_dest_to_cycle=1;
                        break;
                    }
                }
                /* 
                    trying to either make the node invisible or transfer of num
                    If the edge destination is an internal point
                */

                if(is_dest_to_cycle){
                    cout<<"DESTINATION TO CYCLE\n";
                    node payload = k->data;
                    // Saving the edge only if the edge is of zero weight
                    if(k->data.weight==0){
                        int_node u1;
                        u1.vertex = num;
                        u1.payload = payload;
                        // Adding to node_invisible
                        node_invisible.push_back(u1);
                    }
                    k=k->next;
                    removeNode(newAdjT[num], payload.index);
                }else{
                    // If the edge destination is an not an internal point 
                    cout<<"DESTINATION NOT TO CYCLE\n";                    
                    // If from supernode_index edge is going! Then Not deleting it. 
                    if(comps[i][j]==min_index){
                        cout<<"DESTINATION TO MIN-INDEX\n";
                        k = k->next;
                        continue;
                    }
                    // Adding to node_transfer
                    node_transfer[k->data.index] = num;
                    newAdjT[min_index] = addNode(newAdjT[min_index], k->data);
                    int foo = k->data.index;
                    // DEBUG PRINT
                    cout<<"CALLING 1: "<<num+1<<" "<<k->data.vertex+1<<endl;

                    k = k->next;
                    removeNode(newAdjT[num], foo);
                    // DEBUG PRINT
                    cout<<"SHOWING ADJT 1:"<<endl;
                    showAdj(newAdjT);
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

        cout<<"MIN INDEX:"<<min_index+1<<endl;
        // For all elements in ith cycle
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
                        showAdj(newAdjT);
                    }
                }
                while(k){
                    // If destination is num i.e destination to cycle
                    if(k->data.vertex==num){
                        name_change[k->data.index] = num;
                        cout<<"CHANGING NAME OF:"<<num+1<<" TO:"<<min_index+1<<endl;
                        k->data.vertex = min_index;
                        showAdj(newAdjT);
                    }
                    k = k->next;
                }
            }
        }
    }
    cout<<"SHOWING WITH SUPERNODE\n";
    showAdj(newAdjT);

    // Till Now SuperNode Ban Chuka h. And it is in newAdjT
    if(flag==0){
        // There is no cycle. i.e No SuperNode. It means AdjT and newAdjT is Arborescence. 
        // Deleting all edges with non-zeros weights
        removeAllNonZeroPoints(AdjT);
        cout<<"RETURNING ANSWER 😀\n";
        return;
    }
    cout<<endl;

    driver(newAdjT, n, start, no_of_edges);
    // newAdjT has only zero sized edges.
    cout<<"RECIEVED: \n";
    showAdj(newAdjT);

    // Reverting Changing Names! Keeping all data that came from driver.
    for(int i=0; i<newAdjT.size(); i++){
        point* j = newAdjT[i];
        while(j){
            if(name_change[j->data.index]!=-1){
                // There was some name change
                cout<<"I AM CHANGING NAMES"<<j->data.index<<endl;
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
                cout<<"CALLING 2: "<<i+1<<" "<<original_vertex+1<<" "<<j->data.index<<endl;
                int foo = j->data.index;
                j = j->next;
                removeNode(newAdjT[i], foo);
                showAdj(newAdjT);
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
        /* 
            if payload.weight is not zero it means it is not 
            a part of arborescence and it will never be. Thus excluding them.
        */
        if(payload.weight==0){
            newAdjT[vertex] = addNode(newAdjT[vertex], payload);
        }
    }
    cout<<"newAdjT after Adding all nodes:"<<endl;
    showAdj(newAdjT);

    // SUMMARY - adjT is where I need to give final Answer. Right Now newAdjT has 1 extra edge. 
    // I need to give that edge to adjT and remove one from it.

    /* 
        I want to remove all non zeros nodes from AdjT. Whatever left have atleast 1 cycle. I will try to check for those nodes whose size is
        exactly 2. I will then compare it with newAdjT. newAdjT will have 1 extra node. I will remove the cyclic node from newAdjT.
        NOTE: newAdjT even after adding all nodes will not have a single non-zero edge

    */

    cout<<"AdjT BEFORE REMOVING NON ZERO!"<<endl;
    showAdj(AdjT);

    // Removing all non-zero Points
    removeAllNonZeroPoints(AdjT);

    cout<<"adjT AFTER REMOVING NON ZERO!"<<endl;
    showAdj(AdjT);


    // Removing 1 edge(inside of cycle) and adding 1 edge(outside of cycle)
    for(int i=0; i<n; i++){
        int size = 0;
        point* j = newAdjT[i];
        while(j){
            size++;
            j = j->next;
        }
        cout<<"CASE: "<<i+1<<endl;
        cout<<"ADJT"<<endl;
        showAdj(AdjT);
        cout<<"NEW ADJT"<<endl;
        showAdj(newAdjT);
        if(size==2){
            cout<<"SIZE IS 2"<<endl;
        }else if(size>2){
            cout<<"SIZE IS NOT 2, LOGIC FAILURE. SIZE IS "<<size<<endl;
            continue;
        }else{
            // Indegree is less than or equal to 1. NO PROBLEM
            cout<<"[FINE]SIZE IS NOT 2, IT IS "<<size<<endl;
            continue;
        }
        cout<<i<< " "<< start<<endl;
        // Don't know! This case is not possible! Start ki AdjT mein zero Indexes Honge
        if(i==start-1){
            continue;
        }
        size=0;

        // DEBUG CODE
        point* very_temp = AdjT[i];
        while(very_temp){
            size++;
            very_temp = very_temp->next;
        }
        if(size!=1){
            cout<<"SIZE of AdjT is NOT ONE: "<<size<<endl;
        }else{
            cout<<"NO PROBLEM"<<endl;
        }
        // DEBUG CODE END.

        int index = newAdjT[i]->data.index;
        int index1 = (newAdjT[i]->next)->data.index;
        int cycle_index = AdjT[i]->data.index;
        cout<<"index "<<index<<" index1"<<index1<<" cycle_index "<<cycle_index<<endl;
        cout<<"DELETING_TRADE: "<<i+1<<" "<<AdjT[i]->data.vertex+1<<endl;
        if(cycle_index==index){
            // Delete this edge!
            cout<<"DELETING: "<<index<<endl;
            removeNode(newAdjT[i], index);
            // AdjT[i]->visible = false;
        }else if(cycle_index==index1){
            cout<<"DELETING: "<<index1<<endl;
            removeNode(newAdjT[i], index1);
            // (AdjT[i]->next)->visible = false;
        }else{
            cout<<"WRONG LOGIC! KISI EKK KO TOH SAME HONA THA."<<endl;
        }
    }
    // Right Now newAdjT has the answer

    // Deallocating AdjT
    deallocateDriver(AdjT, n);
    AdjT.clear();
    AdjT.resize(n);
    // Copying all the points
    AdjT = newAdjT;
}


/**
 * 
 * Dijkstra for calculation of shortest path!
 * 
 * @params[in] distance array where distance will be updated
 * @params[in] Adjacency List
 * @params[in] parent array where parent will be updated
 **/
void dijkstra(vector< long long > &distance, vector<point*> &A, int n, vector<int> &parent){
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
                parent[dest] = x+1;
                distance[dest] = newDist;
            }
            j = j->next;
        }
    }
}


int main(){
    node payload;
    int t;
    cin>>t;
    int n, start, m, source, dest, wt;
    while(t--){
        cin>>n>>start>>m;
        vector<point*> AdjT(n, NULL);
        vector<point*> Adj(n, NULL);
        int maxIndex = 0;
        // Creating Adjacency List
        for(int i=0; i<m; i++){
            cin>>source>>dest>>wt;
            source-=1;
            dest-=1;
            payload.index = maxIndex;
            payload.vertex = dest;
            payload.weight = wt;
            point* j = Adj[dest];
            int h1=0;
            // Checking if an edge already exist from SOURCE to DEST. If yes then, only updating it.
            while(j){
                if(j->data.vertex==dest){
                    h1=1;
                    if(j->data.weight>wt){
                        j->data.weight = wt;
                    }
                    break;
                }
                j = j->next;
            }
            if(h1==0){
                Adj[source] = addNode(Adj[source], payload);
                maxIndex++;
            }
        }

        // ASSUMING ARBORESCENCE EXIST

        // Removing all nodes and their edges which are not reachable by start
        int visited_index[n] = { 0 };
        dfs(Adj, n, visited_index, start-1);

        // Deleting Non-Reachable Edges from start
        for(int i=0; i<n; i++){
            if(visited_index[i]==0){
                point* j = Adj[i];
                while(j){
                    int index = j->data.index;
                    j = j->next;
                    removeNode(Adj[i], index);
                }
            }
        }

        // Creating Adjacency Transpose (AdjT)
        for(int i=0; i<n; i++){
            point* j = Adj[i];
            while(j){
                payload = j->data;
                int source = payload.vertex;
                payload.vertex = i;
                AdjT[source] = addNode(AdjT[source], payload);
                j = j->next;
            }
        }

        // DRIVER Function Call
        driver(AdjT, n, start, m);
        // AdjT has the Arborescence

        // DEBUG PRINT
        cout<<"FINAL"<<endl;
        showAdj(AdjT);
        
        
        // Adding all indexes of edges in arborescence into arbor
        vector<int> arbor;
        for(int u1=0; u1<n; u1++){
            point* u2 = AdjT[u1];
            while(u2){
                arbor.push_back(u2->data.index);
                u2= u2->next;
            }
        }
        int arbor_size = arbor.size();
        // Sorting the Arbor Array
        mergeSort(arbor, 0, arbor_size-1);

        // DEBUG PRINT
        cout<<"ARBOR ARRAY:"<<endl;
        for(int u1=0; u1<arbor_size; u1++){
            cout<<arbor[u1]<<" ";
        }
        cout<<endl;


        cout<<"PURANA ADJ"<<endl;
        showAdj(Adj);

        // Removing all elements in Adj and keeping only the Arborescence Part. (REASON: AdjT all edge weights are zero)
        long long total_cost=0;
        for(int u1=0; u1<n; u1++){
            point* u2 = Adj[u1];
            while(u2){
                if(binarySearch(arbor, arbor_size, u2->data.index)){
                    // cout<<"BINARY SEARCH TRUE"<<u2->data.index<<endl;
                    total_cost+=u2->data.weight;
                    u2 = u2->next;
                }else{
                    // cout<<"REMOVING"<<u2->data.index<<endl;
                    int foo = u2->data.index;
                    removeNode(Adj[u1], u2->data.index);
                    u2 = u2->next;
                }
            }
        }

        // Calculating Distance and parent
        vector<long long> distance(n, INT_MAX);
        vector<int> parent(n, -1);
        distance[start-1] = 0;
        parent[start-1] = 0;
        // Calling dijkstra
        dijkstra(distance, Adj, n, parent);


        // PRINTING OUTPUT
        cout<<total_cost<<" ";
        for(int i=0; i<n; i++){
            if(distance[i]!=INT_MAX){
                cout<<distance[i]<<" ";
            }else{
                cout<<"-1 ";
            }
        }
        cout<<"# ";
        // Storing Parent in 1 indexing
        for(int i=0; i<n; i++){
            cout<<parent[i]<<" ";
        }
        cout<<endl;
        // PRINTING OUTPUT END

        
        // Deallocating Memory
        deallocateDriver(AdjT, n);
        deallocateDriver(Adj, n);
    }

    return 0;
}