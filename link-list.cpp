#include <iostream>
#include <string.h>
using namespace std;

struct node {
    char data;
    node *next;
};

struct link_list {
    node *head;

    void create();

    void add(char );

    void print();
};

void link_list::create() {
    head = NULL;
}


void link_list::add(char some) {
    node *newnode;
    newnode = new node;
    newnode->data = some;
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
    } else {
        node *traverse;
        traverse = head;
        while(traverse->next != NULL){
            traverse = traverse->next;
        }
        traverse->next = newnode;
    }
}

void link_list::print() {
    node *traverse;
    traverse = head;
    while (traverse) {
        cout << traverse->data << " ";
        traverse = traverse->next;
    }
}


int main() {
    link_list mylist;
    mylist.create();
    mylist.add('a');
    mylist.add('b');
    mylist.add('d');
    mylist.add('c');
    mylist.add('e');
    mylist.print();
    return 0;
}