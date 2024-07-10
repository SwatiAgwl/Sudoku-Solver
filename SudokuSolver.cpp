#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool isSafe(int row, int col,int val, vector<vector<char> >&board,vector<vector<bool> >&sameRow,vector<vector<bool> >&sameCol ){
        if (sameRow[row][val]== 1 )return false;
        if( sameCol[col][val] ==1) return false;
        // checking in 3*3 grid
        int rs= row-(row%3);
        int cs= col- (col%3);
        for( int r=rs; r<rs+3; r++){
            for(int c=cs ; c<cs+3; c++){
                if (board[r][c] != '.'){
                    if( board[r][c] -'0' == val) return false; // char i
                }
            }
        }
        return true;
    }

    bool solve(int row,int col, vector<vector<char> > &board,vector<vector<bool> > &sameRow,vector<vector<bool> >&sameCol){
        if( row==9) return true;
        if( col== 9) return solve( row+1,0,board,sameRow,sameCol);
        if( board[row][col] != '.') return solve( row,col+1,board,sameRow,sameCol);
        
        for( int i=1; i<=9;i++){
            if( isSafe(row,col,i,board,sameRow,sameCol) ){
                board[row][col]=i+'0'; //int to char
                sameRow[row][i]=1;
                sameCol[col][i]=1;
                if(solve(row, col+1,board,sameRow, sameCol)){
                    return true;
                }
                // backtrack
                board[row][col]='.';
                sameRow[row][i]=0;
                sameCol[col][i]=0;
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char> >& board) {
        vector<vector<bool > >sameRow(9,vector<bool> (10,0)); // checks in horizontal direction
        vector<vector<bool> > sameCol (9,vector<bool> (10,0)); // checks in vertical direction

        // marking initial status of board 
        for( int row=0; row<9; row++){
            for( int col=0; col<9; col++){
                if( board[row][col] != '.'){
                    int val= board[row][col] - '0';
                    sameRow[row][val]=1;
                    sameCol[col][val]=1;
                }
            }
        }

        solve( 0,0,board,sameRow,sameCol);
    }
};

int main(){
    vector<vector<char> >board(9,vector<char>(9));
    // taking input 
    cout<<"Enter initial configuration of the board (use '.' for empty cells) : "<<endl;
    for( int i=0; i<9; i++){
        for( int j=0; j<9; j++){
            cin>>board[i][j]; 
        }
    }

    Solution().solveSudoku(board);

    // printing output
    cout<<"Congratulations! You solved it."<<endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}

/* 
Example configuration
5 3 . . 7 . . . .
6 . . 1 9 5 . . .
. 9 8 . . . . 6 .
8 . . . 6 . . . 3
4 . . 8 . 3 . . 1
7 . . . 2 . . . 6
. 6 . . . . 2 8 .
. . . 4 1 9 . . 5
. . . . 8 . . 7 9
*/
