#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct doublenode{
    doublenode* forward;
    doublenode* backward;
    int data;
};

struct doublelist{
    doublenode* head;
    doublenode *tail;
    void create();
    void add(int);
    void remove();
};

void doublelist::create() {
    head = tail = NULL;
}

void doublelist::add(int number){
    doublenode* newnode;
    newnode = new doublenode;
    newnode->data = number;
    newnode->forward = NULL;
    newnode->backward = NULL;
    if(head == NULL){
        head = tail = newnode;
    }
    else{
        tail->forward = newnode;
        newnode->backward = tail;
        tail = newnode;
    }
}

void doublelist::remove() {
    if(tail->backward == NULL){
        tail = head = NULL;
        return;
    }
    tail = tail->backward;
    tail->forward = NULL;
}


struct nodeTree {
    nodeTree *right;
    nodeTree *left;
    int number;
};

struct BinaryTree{
    doublelist listleft;
    doublelist listright;
    doublelist list;
    nodeTree *root;
    int total = 0;
    void create();
    nodeTree* add(int inputs[], int inputs_count, int location,nodeTree* root);
    bool is_there_a_hope(nodeTree*, int);
    void result(int wanting_number);
};

void BinaryTree::create(){
    root = NULL;
    list.create();
    listleft.create();
    listright.create();
}





nodeTree* BinaryTree::add(int inputs[], int inputs_count, int location, nodeTree* root){
    if(location >= inputs_count) return NULL;
    nodeTree* newnode = new nodeTree;
    newnode->left = newnode->right = NULL;
    newnode->number = inputs[location];
    root = newnode;
    root->left = add(inputs, inputs_count, 2*location+1, root->left);
    root->right = add(inputs, inputs_count, 2*location+2, root->right);
    return root;
}


bool BinaryTree::is_there_a_hope(nodeTree* root, int wantin_num) {
    if(root == NULL){
        return false;
    }
    total = total + root->number;
    list.add(root->number);
    if(total < wantin_num && root->left == NULL && root->right == NULL){
        list.remove();
        total -= root->number;
        return false;
    }
    if(total > wantin_num){
        total -= root->number;
        list.remove();
        return false;
    }
    if(total == wantin_num){
        return true;
    }
    else if(is_there_a_hope(root->left, wantin_num)){
        return true;
    }
    else if(is_there_a_hope(root->right, wantin_num)){
        return true;
    }
    else{
        list.remove();
        total -= root->number;
        return false;
    }
}

void printlist(doublenode* head){
    if(head == NULL) return;
    cout << head->data << " ";
    printlist(head->forward);
}

void BinaryTree::result(int wanting_number) {
    wanting_number = wanting_number - root->number;

    if(wanting_number == 0){
        cout << "Path Found: " << root->number << endl;
        cout << "Path Found: " << root->number << endl;
    }
    else{
        if(is_there_a_hope(root->left, wanting_number)){
            cout << "Path Found: " << root->number << " ";
            total = 0;
            listleft.head = list.head; listleft.tail = list.tail;
            list.head = list.tail =  NULL;
            printlist(listleft.head);
            cout << endl;
        }else{
            cout << "No Path Found!" << endl;
        }
        if(is_there_a_hope(root->right, wanting_number)){
            cout << "Path Found: " << root->number << " ";
            listright.head = list.head; listright.tail = list.tail;
            list.head = list.tail =  NULL;
            printlist(listright.head);
            cout << endl;
        }else{
            cout << "No Path Found!" << endl;
        }

    }

}




int main(int argc, char* argv[]) {
    doublelist input_list;
    input_list.create();
    char* filename = "\\Users\\yusuf\\CLionProjects\\hw5\\two_paths.txt";
    int inputs_size = 0;
    int input;
    string line;
    fstream input_file;
    input_file.open(filename, ios::in);
    while(input_file >> input){
        inputs_size++;
        input_list.add(input);
    }
    int inputs[inputs_size];
    doublenode* traverse = input_list.head;
    for(int i = 0; i < inputs_size; i++){
        inputs[i] = traverse->data;
        traverse  = traverse->forward;
    }
    int wanted_number = inputs[--inputs_size];
    input_file.close();
    BinaryTree tree;
    tree.create();
    tree.root = tree.add(inputs, inputs_size, 0, tree.root);
    //print(tree.root);

    tree.result(wanted_number);
    return 0;
}
