#include <iostream>
#include <thread>	//to pause program execution for a specified time
#include <chrono>	//provides time related utilities like seconds, milliseconds, microseconds

using namespace std;
const int SIZE = 9;
int speed = 1000;	//default spped in milliseconds

void setSpeed(){
	cout<<"Enter speed in milliseconds:\n";
	cin>>speed;
}

void displayBoard(int (&board)[SIZE][SIZE]){
	system("cls");
	for(int i=0;i<SIZE;i++){
		if(i%3==0 && i!=0){
			cout<<"---------------------";
			cout<<endl;
		}
		for(int j=0;j<SIZE;j++){
			if(j%3==0 && j!=0) cout<<'|'<<" ";
			board[i][j]==0? cout<<'.'<<" ":cout<<to_string(board[i][j])<<" ";
		}
		cout<<endl;
	}
}

void resetBoard(int (&board)[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;	//Reset to 0
        }
    }
    cout << "Sudoku board has been reset." << endl;
}

void takingInput(int (&board)[SIZE][SIZE]){
	int row,col,val;
	char choice;
    do {
        cout<<"Enter row(1 to 9) and then column (1 to 9) for input:\n";
        cin>>row>>col;
        cout<<"Enter your value(1 to 9):\n";
        cin>>val;
        if(row>=1 && row<=9 && col>=1 && col<=9 && val>=1 && val<=9) {
            board[row-1][col-1]=val;
        } else {
            cout<<"Invalid input! Please enter numbers between 1 and 9."<<endl;
        }
        cout<<"Do you want to enter another value? (y/n): ";
        cin>>choice;
    } while(choice=='y' || choice=='Y');
}

bool isSafe(int row,int col,int (&board)[SIZE][SIZE],int val){
	for(int i=0;i<SIZE;i++){
		if(board[row][i]==val) return false;
		if(board[i][col]==val) return false;
		if(board[3*(row/3)+i/3][3*(col/3)+i%3]==val) return false;
	}
	return true;
}

bool solveSudoku(int (&board)[SIZE][SIZE]){
	for(int row=0;row<SIZE;row++){
		for(int col=0;col<SIZE;col++){
			if(board[row][col]==0){
				for(int val=1;val<=9;val++){
					if(isSafe(row,col,board,val)){
						board[row][col] = val;
						displayBoard(board);
						this_thread::sleep_for(chrono::milliseconds(speed));
						bool isFurtherSolPoss = solveSudoku(board);
						if(isFurtherSolPoss){
							return true;
						}
						else{
							board[row][col] = 0;
						}
					}
				}
				return false;
			}
		}
	}
	return true;
}
int main(){
	int board[SIZE][SIZE] = {0};
	char choice;
    do {
        displayBoard(board);
        takingInput(board);
        setSpeed();
        if(!solveSudoku(board)) {
            cout<<"\n\n\t\tNo Solution Possible\n";
        }

        cout<<"\nDo you want to reset the board and solve again? (y/n): ";
        cin>>choice;
        if(choice=='y' || choice=='Y') {
            resetBoard(board); // Reset the board for a new game
        }
    } while(choice=='y' || choice=='Y');
	return 0;
}
