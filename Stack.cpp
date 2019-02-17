#include <iostream>
using namespace std;


struct node{
    node* next;
    string data;
};

struct Stack{
    node* head;
    void create();
    void push(string );
    string pop();
};

void Stack::create() {
    head = NULL;
}

void Stack::push(string add) {
    node *newnode;
    newnode = new node;
    newnode->data = add;
    newnode->next = head;
    head = newnode;
}

string Stack::pop() {
    node *newnode;
    newnode = new node;
    newnode = head;
    string ret = head->data;
    head = head->next;
    delete newnode;
    return ret;
}






