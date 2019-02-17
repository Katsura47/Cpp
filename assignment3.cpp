#include <iostream>
#include <fstream>
#define STACKSIZE 1000
using namespace std;

typedef int StackDataType;
struct Stack{
    int top ;
    StackDataType stackarray[STACKSIZE];
    void add(int );
    int pop();
    void create();
};

// Pops the last element of stackarray our stacks top element, decreasing top 1 and returning popping element.
int Stack::pop() {
    int x = stackarray[--top];

    return x;
}
// Add new element to our stack, increasing top 1.
void Stack::add(int element) {
    stackarray[top++] = element;

}
// Creating Stack with top=0.
void Stack::create() {
    top = 0;
}

// Gives from stack one to stack two.
// how_many_to_add is the number which is taken from table.
void add_from_one_to_two(Stack &one,Stack &two,int how_many_to_add,Stack &bin){
    /*I did this because I will look at this at main and I will choose which
    player to be stack one and stack two so in this function
    how_many_to_add is always taken as positive. IF it is given negative convert to positive.*/
    if(how_many_to_add < 0){
        how_many_to_add *= -1;
    }

    if(how_many_to_add > one.top){   // If number that taken from table is bigger than your deck size you have to give your all card.
        how_many_to_add = one.top;   // If do not do this it will try to pop cards when there are no cards therefore it will give error.
    }
    for(int i = 0;i < how_many_to_add;++i){
        //taken player is the player who takes card.
        if(two.stackarray[two.top-1] < one.stackarray[one.top-1]){      /*Look at if the taken player's stack top element is bigger
																		 *or smaller than given's top element.*/
            two.add(one.pop());     // If bigger, taken player takes the element.
        }else{
            bin.add(one.pop());     // If smaller, taken player throws it to the bin.
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc){
        cout << "";
    }
    Stack Player1;
    Stack Player2;
    Stack bin;
    Stack Table;
    Player1.create();
    Player2.create();
    bin.create();
    Table.create();
    // In this block program will take inputs from file.
    string filename = argv[1];
    ifstream file;
    file.open(filename,ios::in);
    int table_deck, player_decks;       // table_deck = how many cards table deck include.
    file >> table_deck >> player_decks; // player_decks = how many cards players deck include.
    for(int i = 0; i < table_deck; i++){
        int card;
        file >> card;
        Table.add(card);
    }
    for(int i = 0; i < player_decks; i++){
        int card;
        file >> card;
        Player1.add(card);
    }
    for(int i = 0; i < player_decks; i++){
        int card;
        file >> card;
        Player2.add(card);
    }

    // Taking inputs is over.
    // Now players will take cards from table.
    for(int turns = 1; turns < table_deck+1; turns++){
        int taken_card = Table.pop();
        if(turns%2 == 1){// Looking if it is player 1 turn or not.
            //player 1 takes card from table
            if(taken_card < 0){ // player 1 will give cards to player 2.
                add_from_one_to_two(Player1,Player2,taken_card,bin);
            }else{ // player 1 will take cards from player 2.
                add_from_one_to_two(Player2,Player1,taken_card,bin);
            }
        }
        else{
            // player 2 takes card from table.
            if(taken_card < 0){ // player 2 will give cards to player 1.
                add_from_one_to_two(Player2,Player1,taken_card,bin);
            }else{ // player 2 will take cards from player 1.
                add_from_one_to_two(Player1,Player2,taken_card,bin);
            }
        }
        if(Player1.top == 0 || Player2.top == 0){ // Looks if one of player is out of cards.
            break;                                // If one is out of cards finish game.
        }
    }
    cout << bin.top;
    file.close();
    return 0;
}