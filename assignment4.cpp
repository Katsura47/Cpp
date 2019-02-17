#include <iostream>
#include "stackandque.cpp"
#include <fstream>
using namespace std;
struct Ants{
    queueAnt ants;
    queueAnt holeDepths;
    stackAnt hole;
    void ReadFile(char *);
    void ShowContents(bool);
    void CrossRoad();
};

void Ants::ReadFile(char *filename) {
    ifstream file;
    file.open(filename,ios::in);
    ants.create();
    holeDepths.create();
    int count_ant;
    int depth_of_hole;
    file >> count_ant;
    for(int i = 1; i <= count_ant; i++){
        ants.add(i);
    }
    while(file >> depth_of_hole){
        holeDepths.add(depth_of_hole);
    }
    file.close();
}

void Ants::ShowContents(bool is_depths){
    Node* traverse;
    if(is_depths) {
        traverse = ants.head;
    }else{
        traverse = holeDepths.head;
    }
    while(traverse != NULL){
        cout << traverse->data << " ";
        traverse = traverse->next;
    }
    cout << endl;

}

void Ants::CrossRoad(){
    hole.create();
    Node* traverse;
    traverse = holeDepths.head;
    while(traverse != NULL){
        for(int i = 0; i < traverse->data;i++){
            hole.add(ants.pop()->data);
        }
        for(int i = 0; i < traverse->data;i++){
            ants.add(hole.pop()->data);
        }
        traverse = traverse->next;
    }
}


int main(int argc, char** argv){
    Ants a;
    a.ReadFile(argv[1]);
    cout << "The initial Ant sequence is: ";
    a.ShowContents(1);
    cout << "The depth of holes are: ";
    a.ShowContents(0);
    a.CrossRoad();
    cout << "The final Ant sequence is: ";
    a.ShowContents(1);

    return 0;
}