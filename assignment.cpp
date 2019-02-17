
#include <iostream>
#include <stdio.h>
using namespace std;

// For saving center locations and their properties.
struct sign_list{
    int center_x;
    int center_y;
    int quantity;
    char sign;
    int index;

};
// Before moving the location of given sign we have to empty that location to not get conflict with itself.if we get an error again just put that sign back.
// if bool empty given true make empty that locations but if given as false put necessary sign in given locations(if moving get error).
void empty_or_fill(char **arr, int center_x, int center_y, int quant, char sign, bool empty){
    int x = center_x - 1;
    int y = center_y - 1;
    int quantit = quant;
    char o_or_sign;
    if(empty){
        o_or_sign = '0';
    }
    else{
        o_or_sign = sign;
    }
    switch(sign){
        case '+':
            for(int i = 1; i <= quantit; ++i){
                arr[x][y] = o_or_sign;
                arr[x+i][y] = o_or_sign;
                arr[x-i][y] = o_or_sign;
                arr[x][y+i] = o_or_sign;
                arr[x][y-i] = o_or_sign;
            }return;
        case 'x':
            for(int i = 1; i <= quantit; ++i){
                arr[x][y] = o_or_sign;
                arr[x+i][y+i] = o_or_sign;
                arr[x-i][y-i] = o_or_sign;
                arr[x-i][y+i] = o_or_sign;
                arr[x+i][y-i] = o_or_sign;
            }return;
        case '/':
            for(int i = 1; i <= quantit; ++i){
                arr[x][y] = o_or_sign;
                arr[x-i][y+i] = o_or_sign;
                arr[x+i][y-i] = o_or_sign;
            }return;
        case '-':
            for(int i = 1; i <= quantit; ++i){
                arr[x][y] = o_or_sign;
                arr[x][y+i] = o_or_sign;
                arr[x][y-i] = o_or_sign;
            }return;
    }
}



// If there is a conflict error with your operation this func will give you a true value.
bool is_conflict(char **arr, int row, int col, int nx, int ny, char sign, int size){
    int x = nx-1;
    int y = ny -1;
    if(1 <= nx && nx <= row && 1 <=ny && ny <=col){
        if(arr[x][y] != '0'){
            return true;
        }
    }
    switch(sign){
        case '+':
            for(int i = -1*size; i <= size; i++){
                if(1<= nx - i && nx-i <=row && 1<=ny && ny <= col){
                    if(arr[x-i][y] != '0')
                        return false;
                }
                if(1<=nx && nx <= row && 1<=ny-i && ny-i<=col){
                    if(arr[x][y-i] != '0')
                        return false;
                }
            }break;
        case 'x':
            for(int i = -1*size; i <=size; ++i){
                if(1<=nx-i && nx-i <=row && 1 <= ny-(i*-1) && ny-(i*-1) <= col){
                    if(arr[x-i][y-(i*-1)] != '0')
                        return true;
                }
                if(1<=nx-i && nx-i <=row && 1 <= ny-i && ny-i <= col){
                    if(arr[x-i][y-i] != '0')
                        return true;
                }
            }break;
        case '/':
            for(int i = -1*size; i <=size; ++i){
                if(1 <= nx-i && nx-i <=row && 1 <= ny-(i*-1) && ny-(i*-1) <= col){
                    if(arr[x-i][y-(i*-1)] != '0')
                        return true;
                }
            }break;
        case '-':
            for(int i = -1*size; i <= size; i++){
                if(1<=nx && nx <= row && 1<=ny-i && ny-i<=col){
                    if(arr[x][y-i] != '0')
                        return true;
                }
            }break;

    }
    return false;
}


// For moving the location of given sign according to given distance and direction.
// IF the moving successful we have to change center locations in centers array that we keep them.
// therefore we need centers[] array and index of center.
void move_to_new_loc(char **arr, int new_x, int new_y, int quant, char sign, char direction, int how_many, int row, int col, struct sign_list centers[], int center_index){
    int x = new_x - 1; int y = new_y - 1;
    int quantit = quant;
    switch(direction){
        case 'R':
            y = y + how_many;
            break;
        case 'L':
            y = y - how_many;
            break;
        case 'D':
            x = x + how_many;
            break;
        case 'U':
            x = x - how_many;
            break;
    }
    switch(sign){
        case '+':
            // Controling Border error.
            if((1 <= x+1-quantit && x+1 <= row - quantit) && (1 <= y+1-quantit && y+1 <= col - quantit)){
                // controlling conflict error if there is no border error.
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                    return;
                }
                // Putting Signs to their new places.
                for(int i = 1; i <= quantit; ++i){
                    arr[x][y] = '+';
                    arr[x+i][y] = '+';
                    arr[x-i][y] = '+';
                    arr[x][y+i] = '+';
                    arr[x][y-i] = '+';
                }
                // change the saved center location after successfull moving operation.
                cout << "SUCCESS: " << sign << " moved from (" << new_x << "," << new_y << ") to " << "("<< x+1 << "," << y+1 << ")." << endl;
                centers[center_index].center_x = x + 1;
                centers[center_index].center_y = y + 1;
                return;

            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                // controlling conflict error if there is border error already.
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                }
            }return;
            // All signs have same syntax with '+' sign.
        case 'x':
            if((1 <= x+1-quantit && x+1 <= row - quantit) && (1 <= y+1-quantit && y+1 <= col - quantit)){
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                    return;
                }
                for(int i = 1; i <= quantit; ++i){
                    arr[x][y] = 'x';
                    arr[x+i][y+i] = 'x';
                    arr[x-i][y-i] = 'x';
                    arr[x-i][y+i] = 'x';
                    arr[x+i][y-i] = 'x';
                }
                cout << "SUCCESS: " << sign << " moved from (" << new_x << "," << new_y << ") to " << "("<< x+1 << "," << y+1 << ")." << endl;
                centers[center_index].center_x = x + 1;
                centers[center_index].center_y = y + 1;

                return;
            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                }
            }return;
        case '/':
            if((1 <= x+1-quantit && x+1 <= row - quantit) && (1 <= y+1-quantit && y+1 <= col - quantit)){
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                    return;
                }
                for(int i = 1; i <= quantit; ++i){

                    arr[x][y] = '/';
                    arr[x-i][y+i] = '/';
                    arr[x+i][y-i] = '/';
                }
                cout << "SUCCESS: " << sign << " moved from (" << new_x << "," << new_y << ") to " << "("<< x+1 << "," << y+1 << ")." << endl;
                centers[center_index].center_x = x + 1;
                centers[center_index].center_y = y + 1;

                return;
            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                }
            }return;
        case '-':
            if(1 <= y+1-quantit && y+1 <= col - quantit){
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                    return;
                }
                for(int i = 1; i <= quantit; ++i){
                    arr[x][y] = '-';
                    arr[x][y+i] = '-';
                    arr[x][y-i] = '-';
                }
                cout << "SUCCESS: " << sign << " moved from (" << new_x << "," << new_y << ") to " << "("<< x+1 << "," << y+1 << ")." << endl;
                centers[center_index].center_x = x + 1;
                centers[center_index].center_y = y + 1;
                return;
            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                if(is_conflict(arr,row,col,x+1,y+1,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " can not be moved from (" << new_x << "," << new_y << ")" << " to ("<< x + 1 << "," << y + 1 << ")." << endl;
                }
            }return;
    }
}




// for print array and visualize it.
void print_arr(char **arr, int row, int col){
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col;++j){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
// Take array(girid) that we will operate, its row and column size, coordinats(nx, ny) for operation('+', 'X', '-' , '/') and size(quant) of them.
void operation(char **arr, int row, int col, int nx, int ny, char sign, int quantit){
    // Assignment operate in 1 based arrays but program works with 0 based.
    int x = nx - 1; int y = ny - 1;
    switch(sign){
        case '+':
            // Controling Border error.
            if((1 <= nx-quantit && nx <= row - quantit) && (1 <= ny-quantit && ny <= col - quantit)){
                // controlling conflict error if there is no border error.
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
                // Putting Signs to their places.
                for(int i = 1; i <= quantit; ++i){
                    arr[x][y] = '+';
                    arr[x+i][y] = '+';
                    arr[x-i][y] = '+';
                    arr[x][y+i] = '+';
                    arr[x][y-i] = '+';
                }
                cout << "SUCCESS: Operator " << sign << " with size " << quantit << " is placed on(" << nx << "," << ny << ")." << endl;


            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                // controlling conflict error if there is border error already.
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
            }return;
            // All signs have same syntax with '+' sign.
        case 'x':
            if((1 <= nx-quantit && nx <= row - quantit) && (1 <= ny-quantit && ny <= col - quantit)){
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
                for(int i = 1; i <= quantit; ++i){
                    arr[x][y] = 'x';
                    arr[x+i][y+i] = 'x';
                    arr[x-i][y-i] = 'x';
                    arr[x-i][y+i] = 'x';
                    arr[x+i][y-i] = 'x';
                }
                cout << "SUCCESS: Operator " << sign << " with size " << quantit << " is placed on(" << nx << "," << ny << ")." << endl;
                return;
            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
            }return;
        case '/':
            if((1 <= nx-quantit && nx <= row - quantit) && (1 <= ny-quantit && ny <= col - quantit)){
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
                for(int i = 1; i <= quantit; ++i){

                    arr[x][y] = '/';
                    arr[x-i][y+i] = '/';
                    arr[x+i][y-i] = '/';
                }
                cout << "SUCCESS: Operator " << sign << " with size " << quantit << " is placed on(" << nx << "," << ny << ")." << endl;
                return;
            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
            }return;
        case '-':
            if(1 <= ny - quantit && ny <= col - quantit){
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
                for(int i = 1; i <= quantit; ++i){
                    arr[x][y] = '-';
                    arr[x][y+i] = '-';
                    arr[x][y-i] = '-';
                }
                cout << "SUCCESS: Operator " << sign << " with size " << quantit << " is placed on(" << nx << "," << ny << ")." << endl;
                return;
            }
            else{
                cout << "BORDER ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                if(is_conflict(arr,row,col,nx,ny,sign,quantit)){
                    cout << "CONFLICT ERROR: Operator " << sign << " with size " << quantit << " can not be placed on(" << nx << "," << ny << ")." << endl;
                    return;
                }
            }return;
    }
}


void find_center(struct sign_list centers[], int given_x, int given_y,int out_arr[], char sign){
    int i = 0;
    while(true){
        if(centers[i].sign == sign){
            int x = centers[i].center_x;
            int y = centers[i].center_y;
            int quant = centers[i].quantity;
            int index = centers[i].index;
            switch(sign){
                case '0':
                    return;
                case '+':
                    for(int j = 1; j < quant + 1; j++){
                        if((given_x == x && given_y == y) || (given_x == x + j && given_y == y)|| (given_x == x - j && given_y == y) ||
                           (given_x == x && given_y == y + j) || (given_x == x && given_y == y - j)){
                            out_arr[0] = x;
                            out_arr[1] = y;
                            out_arr[2] = quant;
                            out_arr[3] = index;
                            return;
                        }
                    }
                case 'x':
                    for(int j = 1; j < quant + 1; j++){
                        if((given_x == x && given_y == y) || (given_x == x + j && given_y == y + j)|| (given_x == x - j && given_y == y - j) ||
                           (given_x == x - j && given_y == y + j) || (given_x == x + j && given_y == y - j)){
                            out_arr[0] = x;
                            out_arr[1] = y;
                            out_arr[2] = quant;
                            out_arr[3] = index;
                            return;
                        }

                    }
                case '/':
                    for(int j = 1; j < quant + 1; j++){
                        if((given_x == x && given_y == y) || (given_x == x + j && given_y == y - j) || (given_x == x - j && given_y == y + j)){
                            out_arr[0] = x;
                            out_arr[1] = y;
                            out_arr[2] = quant;
                            out_arr[3] = index;

                            return;
                        }
                    }
                case '-':
                    for(int j = 1; j < quant + 1; j++){
                        if((given_x == x && given_y == y) || (given_x == x && given_y == y - j) || (given_x == x && given_y == y + j)){
                            out_arr[0] = x;
                            out_arr[1] = y;
                            out_arr[2] = quant;
                            out_arr[3] = index;

                            return;
                        }
                    }
            }
        }
        i++;
    }
}


int main(int argc, char *argv[]){
    // First part taking instructions and put signs to girid.
    FILE *ins;
    int row, col;
    char sign[2];
    char r_sign;
    int x, y, quant;
    // opening text file that include girid sizes and signs locations with their sizes.
    ins = fopen("C:\\Users\\yusuf\\CLionProjects\\assignment1\\instructions.txt", "r");
    // Taking first line of given text and assigning them to row and col respectively.
    fscanf(ins, "%d %d", &row, &col);
    // Creating an array for center coordinates later we will use this in moving signs.
    const int centers_size = 30;
    struct sign_list centers[centers_size];
    // Creating array dynamically.
    char **arr = new char*[row];
    for(int i = 0; i < row; i++){
        arr[i] = new char[col];
        for(int j = 0; j < col;++j){
            arr[i][j] = '0';
        }
    }
    cout << "A grid is created: " << row << " " << col << endl;
    //
    // For taking indexes of center locations.
    int i = 0;
    while((fscanf(ins, "%s %d %d %d", sign, &x, &y, &quant))==4){
        // Taking second and so on lines and assinning them to sign, x, y and quant.

        r_sign = sign[0];
        centers[i].center_x = x;
        centers[i].center_y = y;
        centers[i].quantity = quant;
        centers[i].sign = sign[0];
        centers[i].index = i;
        i++;
        // doing operation.
        operation(arr, row, col, x, y, r_sign,quant);
        //print_arr(arr, row, col);
    }
    //closing first text.
    fclose(ins);
    //First Part is Done!
    // Second Part: try to moving signs that we put in first part according to given information.
    //MVR 2 1 2
    FILE *girid;
    int founding_center[4];
    char which_side[4];
    char move_now;
    char which_sign;
    int given_x;
    int given_y;
    int given_dist;
    // Opening the second text file that includes direction location and distance to travel.
    girid = fopen("C:\\Users\\yusuf\\CLionProjects\\assignment1\\girid.txt", "r");
    // assigning values in text to the variables to use them.
    while((fscanf(girid, "%s %d %d %d", which_side, &given_x, &given_y, &given_dist))==4){
        // Taking third character of first element(which_side) because other 2 are unimportant.
        move_now = which_side[2];
        // Finding sign for given location.
        which_sign = arr[given_x-1][given_y-1];
        // Finding the center of given location(it is not neccessary to be center of sign).
        find_center(centers, given_x, given_y, founding_center, which_sign);
        int to_move_x = founding_center[0];
        int to_move_y = founding_center[1];
        int to_move_quant = founding_center[2];
        int center_index = founding_center[3];
        // Empty given sign.
        empty_or_fill(arr, to_move_x, to_move_y, to_move_quant, which_sign, true);
        move_to_new_loc(arr, to_move_x, to_move_y, to_move_quant, which_sign, move_now, given_dist, row, col, centers, center_index);
        //print_arr(arr, row, col);
        // İf move operation gets failure fill back the area we emptied.
        if(to_move_x == centers[center_index].center_x && to_move_y == centers[center_index].center_y){
            empty_or_fill(arr, to_move_x, to_move_y, to_move_quant, which_sign, false);
        }


    }
    fclose(girid);

    //print_arr(arr, row, col);

    // delete the array for not getting memory leak.
    for(int i = 0; i < row; i++){
        delete [] arr[i];
    }
    delete [] arr;

}

















