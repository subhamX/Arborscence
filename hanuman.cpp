#include<iostream>

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

void deallocate(point* head){
    while(head){
        point* t1 = head->next;
        free(head);
        head = t1;
    }
}

void traversePoints(point* head){
    while(head){
        cout<<head->data.index<<" "<<head->data.vertex<<" "<< head->data.weight<<endl;
        head = head->next;
    }
    cout<<endl;
}

int main(){
    point* head = NULL;
    node temp;
    

    deallocate(head);
    return 0;
}