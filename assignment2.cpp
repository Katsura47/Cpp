#include <iostream>
#include <string>
#include <fstream>
using namespace std;
double value_of_character(string character){
    if(character == "ç" || character == "Ç"){
        return  99.5;
    }
    else if(character == "ğ" || character == "Ğ"){
        return 103.5;
    }
    else if(character == "ş" || character == "Ş"){
        return 115.5;
    }
    else if(character == "ö" || character == "Ö"){
        return 111.5;
    }
    else if(character == "ü" || character == "Ü"){
        return 117.5;
    }

    double x = tolower(character[0]);
    return x;
}


struct occur_node {
    string character;
    occur_node *next;
    int occurence;
};


struct vocab_node {
    vocab_node *next;
    occur_node *list;
};

struct vocab_list {
    vocab_node *head;
    vocab_node *tail;
        void create();
        void print();
        void add_char(string );
        void add_occurence(string , string );
        void get_together();
        double get_Probability(string, string );
};

void vocab_list::create() {
    head = NULL;
    tail = NULL;

}

void vocab_list::print() {
    vocab_node *traverse;
    traverse = head;
    while(traverse != NULL){
        if(traverse->list->character == " "){
            cout << "<SP>:"<<endl;
        }
        else{
        cout << traverse->list->character << ":" << endl;
        }
        traverse->list = traverse->list->next;
        while (traverse->list != NULL){
            if(traverse->list->character == " "){
                cout << "<<SP>," << traverse->list->occurence<< ">" << endl;
            }
            else{
                cout << "<" << traverse->list->character << "," << traverse->list->occurence << ">" << endl;
            }
            traverse->list = traverse->list->next;
        }
        traverse = traverse->next;
    }


}

void vocab_list::add_char(string element){
    vocab_node *traverse;
    vocab_node *newnode;
    newnode = new vocab_node;
    newnode->list = new occur_node;
    newnode->list->character = element;
    if(value_of_character(element) < 'a'){
        if(tail == NULL){
            newnode->list->next = NULL;
            newnode->list->occurence = 1;
            newnode->next = NULL;
            tail = newnode;
        }
        else{
            traverse = tail;
            while(traverse->next != NULL && traverse->list->character != element){
                traverse = traverse->next;
            }
            if(traverse->list->character == element){
                traverse->list->occurence++;
            }
            else{
                newnode->list->next = NULL;
                newnode->list->occurence = 1;
                traverse->next = newnode;
                newnode->next = NULL;

            }
        }

    }
    else if(head == NULL){
        newnode->list->next = NULL;
        newnode->list->occurence = 1;
        newnode->next = NULL;
        head = newnode;

    }
    else if(value_of_character(head->list->character) == value_of_character(element)){
        head->list->occurence++;
    }
    else if(value_of_character(head->list->character) > value_of_character(element)){
        newnode->list->next = NULL;
        newnode->list->occurence = 1;
        newnode->next = head;
        head = newnode;
    }
    else{
        traverse = head;
        while(traverse->next != NULL && value_of_character(traverse->next->list->character) < value_of_character(element)){
            traverse = traverse->next;
        }

        if(traverse->next == NULL){
            newnode->list->next = NULL;
            newnode->list->occurence = 1;
            traverse->next = newnode;
            newnode->next = NULL;
        }
        else if(value_of_character(traverse->next->list->character) == value_of_character(element)){
            traverse->next->list->occurence++;
        }
        else{
            newnode->list->next = NULL;
            newnode->list->occurence = 1;
            newnode->next = traverse->next;
            traverse->next = newnode;
        }

    }
}

void vocab_list::add_occurence(string element1, string element2) {
    vocab_node *traverse;
    traverse = head;
    occur_node *traverse_bot;

    while(traverse->list->character != element1){
        traverse = traverse->next;
    }
    traverse_bot = traverse->list;
    while(traverse_bot->next != NULL && traverse_bot->next->character != element2){
        traverse_bot = traverse_bot->next;
    }
    if(traverse_bot->next == NULL){
        occur_node *n_occur_node;
        n_occur_node = new occur_node;
        n_occur_node->character = element2;
        n_occur_node->occurence = 1;
        traverse_bot->next = n_occur_node;
        n_occur_node->next = NULL;
    }
    else if(traverse_bot->next->character == element2){
        traverse_bot->next->occurence++;
    }

}

void vocab_list::get_together() {
    vocab_node *traverse;
    traverse = head;
    while(traverse->next != NULL){
        traverse = traverse->next;
    }
    traverse->next = tail;

}


double vocab_list::get_Probability(string element1, string element2) {
    vocab_node *traverse;
    traverse = head;
    double occurence, uni_occurence;
    while(traverse != NULL && traverse->list->character != element1){
        traverse = traverse->next;
    }
    if(traverse != NULL){
        occurence = traverse->list->occurence;
        while(traverse->list != NULL && traverse->list->character != element2){
            traverse->list = traverse->list->next;
        }
        if (traverse->list != NULL){
            uni_occurence = traverse->list->occurence;
            return uni_occurence/occurence;
        }
        else{
            return 0;
        }
    }
    return 0;
}




int main(int argc, char *argv[]) {
    vocab_list my_voc;
    my_voc.create();

    ifstream input;
    input.open(argv[1],ifstream::in);

    string element;

    while(input.good()){
        input.get(element);
        if(element != "\n") {
            my_voc.add_char(element);

        }
    }
    my_voc.get_together();
    input.close();
    input.open(argv[1],ifstream::in);
    string element1,element2;
    input.get(element1);
    while(input.good()){
        input.get(element2);
        if(element2 == "\n"){
            input.get(element1);
            input.get(element2);
        }
        my_voc.add_occurence(element1,element2);
        element1 = element2;

    }
    input.close();
    if(argv[2] == NULL){
        my_voc.print();
    }
    else{
        string first_element = argv[2];
        string second_element = argv[3];
        if(first_element == "<SP>"){
            cout << my_voc.get_Probability(" ",argv[3]) << endl;
        }
        else if(second_element == "<SP>"){
            cout << my_voc.get_Probability(argv[2], " ") << endl;
        }
        else{
            cout << my_voc.get_Probability(argv[2],argv[3]) << endl;
        }
    }
    return 0;
}