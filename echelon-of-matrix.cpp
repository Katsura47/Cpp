#include <iostream>
using namespace std;


void row_divide(int row[], int constant, int col){
    for(int i = 0; i < col; i++){
        row[i] = row[i]/constant;
    }

}

void row_multiple(int row[], int constant, int col){
    for(int i = 0; i < col; i++){
        row[i] = row[i]*constant;
    }
}
void print_arr(int **arr, int row, int col){
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

}
// row1 = row1 - row2
void row_sub(int row1[], int row2[], int col){
    for(int i = 0; i < col; i++){
        row1[i] = row1[i] - row2[i];
    }
}

void make_echelon(int **arr, int row, int col){

    int j = 0;
    for(int i = 0; i < row - 1; i++){
        print_arr(arr, row, col);
        cout << "----------" << endl;
        while(arr[i][j] == 0 && j < col){
            j++;
        }
        if(j >= col){
            continue;
        }
        row_divide(arr[i],arr[i][j],col);
        row_multiple(arr[i],arr[i+1][j],col);
        row_sub(arr[i+1],arr[i],col);

    }
    for(int i = 0; i < row; i++){
        while(arr[i][j] == 0 && j < col){
            j++;
        }
        if(j >= col){
            continue;
        }
        row_divide(arr[i], arr[i][j], col);
    }
}







int main() {
    int row, col;
    cout << "Please enter row and column" << endl;
    cin >> row >> col;
    int **arr = new int*[row];
    for(int i = 0; i < row; i++){
        arr[i] = new int[col];
    }
    for(int i = 0; i < row; i++){
        cout << "please enter " << i << "row" << endl;
        for(int j = 0; j < col; j++){
            int element;
            cin >> element;
            arr[i][j] = element;
        }
    }
    make_echelon(arr, row, col);
    cout << "------" << endl;

    print_arr(arr, row, col);






    for(int i = 0; i < row; i++){
        delete [] arr[i];
    }
    delete [] arr;

}