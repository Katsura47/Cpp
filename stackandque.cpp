//
// Created by yusuf on 4.12.2018.
//
#include "stackandque.h"
#include <iostream>

void stackAnt::create() {
    head = NULL;
}

void stackAnt::add(int data) {
    Node* newnode;
    newnode = new Node;
    newnode->data = data;
    if(head == NULL){
        head = newnode;
        head->next = NULL;
    }
    else{
        newnode->next = head;
        head = newnode;
    }
}

Node *stackAnt::pop() {
    Node* return_node;
    return_node = head;
    head = head->next;
    return return_node;
}



void queueAnt::create() {
    head = NULL;
    tail = NULL;
}

void queueAnt::add(int data) {
    Node* newnode;
    newnode = new Node;
    newnode->data = data;
    newnode->next = NULL;
    if(tail == NULL){
        tail = newnode;
        head = newnode;
    }else{
        tail->next = newnode;
        tail = newnode;
    }
}

Node *queueAnt::pop(){
        Node* to_return;
        to_return = head;
        head = head->next;
        return to_return;
}