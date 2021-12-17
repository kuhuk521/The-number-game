#include<iostream>
#include<iomanip>
using namespace std;
 
// Board elememts
#define EDGE -1
#define EMPTY 0
 
// Global Variable
int N;      // Board dimension
int D;      // maximum number of different tile types on the board
int S;      // Seed for pseudo-random number generation
int** board;
int line;
int column;
int points;
int pointsTotal = 0;
 
// Class that defines the movement
class movement{
   public:
       pair <int,int> origin;
       pair <int,int> destination;
};
 
// Variable that stores the movement
movement mover;
 
//
// USE BACKTRACKING TO CREATE BOARDS
// WITHOUT REMOVABLE STRUCTURES
//
 
/*
----------------------------------------------------------------------------------------------------
||||||||||||||||||||||||||||||||||||||||||||| THE CODE  |||||||||||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------------------------------------
*/
 
// allocating board of size NXN
void allocateBoard(){
 
   // allocate memory space for the board
   board = new int*[N+2];
   for(int i= 0; i <= N+1; i++){
       board[i] = new int[N+2];
   }
 
 
   // Define a EDGE
   for(int i = 0; i <= N+1; i++){
 
       board[0][i]     = EDGE;
       board[i][0]     = EDGE;
       board[N+1][i]   = EDGE;
       board[i][N+1]   = EDGE;
 
   }
 
 
   // Reset all positions on the board
   for(int i = 1; i <= N; i++){
       for(int j = 1; j <= N; j++){
           board[i][j] = EMPTY;
       }
   }
}
 
 
// Search for empty cells
bool EmptyCell(int& i, int& j){
 
   for(i = 1; i <= N; i++){
       for(j = 1; j <= N; j++){
           if(board[i][j] == EMPTY)
               return true;
       }
 
   }
 
   return false;
}
 
 
bool PiecesSameAsAbove(int row, int col, int num){
 
   if(row > 2){
       if( (num == board[row-1][col]) &&
           (num == board[row-2][col]) )
           return true;
   }
 
   return false;
}
 
bool PiecesSameAsBelow(int row, int col, int num){
 
   if(row > 1 && row < N){
       if( (num == board[row-1][col]) &&
           (num == board[row+1][col]) )
           return true;
   }
 
   return false;
}
 
bool PiecesEqualsUpdown(int row, int col, int num){
 
   if(row <= N-2){
       if( (num == board[row+1][col]) &&
           (num == board[row+2][col]) )
           return true;
   }
 
   return false;
}
 
 
// Search for the same colors in the same column
bool EqualPartsSameColumn(int row, int col, int num){
 
 
   if( PiecesSameAsAbove(row, col, num)        ||
       PiecesSameAsBelow(row, col, num) ||
       PiecesEqualsUpdown(row, col, num))
       return true;
 
 
   return false;
}
 
// Search for matching tiles to the left of the current tile.
bool PiecesEqualLeft(int row, int col, int num){
 
   if(col > 2){
       if( (num == board[row][col-1]) &&
           (num == board[row][col-2]) )
           return true;
   }
 
   return false;
}
 
// Search for equal tiles to the left and right of the current tile.
bool EqualPartsRightLeft(int row, int col, int num){
 
   if(col > 1 && col < N){
       if( (num == board[row][col-1]) &&
           (num == board[row][col+1]) )
           return true;
   }
 
   return false;
 
}
 
// Search for pieces equal to the right of the current piece.
bool PiecesEqualRight(int row, int col, int num){
 
   if(col <= N-2){
       if( (num == board[row][col+1]) &&
           (num == board[row][col+2]) )
           return true;
   }
 
   return false;
}
 
 
// Search for identical pieces in the same line.
bool EqualPiecesOnSameLine(int row, int col, int num){
 
   if( PiecesEqualLeft(row, col, num)      ||
       EqualPartsRightLeft(row, col, num) ||
       PiecesEqualRight(row, col, num))
       return true;
 
 
   return false;
}
 
// Search for a scoring structure
bool ScorableStructure(int row, int col, int num){
 
 
   if(EqualPiecesOnSameLine(row, col, num) ||
       EqualPartsSameColumn(row, col, num))
       return true;
 
   return false;
}
 
 
// Generates an N x N board with no scoring structures
// using backtracking
bool BuildBoard(){
 
   int i, j;
 
   if(!EmptyCell(i, j)){
       return true;
   }
 
   board[i][j] = rand()%D+1;
 
   if(!ScorableStructure(i, j, board[i][j])){
       if(BuildBoard())
           return true;
   }
 
   for(int num = 1; num <= D; num++){
 
       board[i][j] = num;
 
       if(!ScorableStructure(i, j, num)){
           if(BuildBoard())
               return true;
       }
 
   }
 
 
   board[i][j] = EMPTY;
 
   // Triggers backtracking
   return false;
}
 
// Print the board with the EDGEs
void PrintBoard(){
   for(int i= 0; i <= N+1; i++){
       for(int j= 0; j <= N+1; j++){
           cout<<setw(3)<<board[i][j];
       }
       cout<<endl;
   }
}
 
// frees memory space
void TurnOffBoard(){
   for(int i= 0; i <= N+1; i++){
       delete [] board[i];
   }
   delete [] board;
}
 
// Check if there is a punctual structure above, between and below
// of the moved part, and marks them as EMPTY.
void BrandPartsEqualInSameColumn(int row, int col, int num){
 
   if(PiecesSameAsAbove(row, col, num)){
       for(int i = row; i >= 1; i--){
 
           if(board[i][col] == num)
               board[i][col] = EMPTY;
           else if(board[i][col] == EMPTY)
               continue;
           else
               break;
 
       }
 
   }
 
   if(PiecesSameAsBelow(row, col, num)){
 
       for(int i = row; i >= 1; i--){
 
           if(board[i][col] == num)
               board[i][col] = EMPTY;
           else if(board[i][col] == EMPTY)
               continue;
           else
               break;
 
       }
 
       for(int i = row; i <= N; i++){
 
           if(board[i][col] == num)
               board[i][col] = EMPTY;
           else if(board[i][col] == EMPTY)
               continue;
           else
               break;
       }
 
   }
 
   if(PiecesEqualsUpdown(row, col, num)){
 
       for(int i = row; i <= N; i++){
 
           if(board[i][col] == num)
               board[i][col] = EMPTY;
           else if(board[i][col] == EMPTY)
               continue;
           else
               break;
       }
 
   }
 
}
 
 
//Checks if there are punctual structure(s) on the right, between and left
// of the moved part, and marks them as EMPTY.
void BrandPartsEqualOnSameLine(int row, int col, int num){
 
   if(PiecesEqualRight(row, col, num)){
 
       for(int j = col; j <= N; j++){
 
           if(board[row][j] == num)
               board[row][j] = EMPTY;
           else if(board[row][j] == EMPTY)
               continue;
           else
               break;
 
       }
   }
 
 
   if(EqualPartsRightLeft(row, col, num)){
 
       for(int j = col; j <= N; j++){
 
           if(board[row][j] == num)
               board[row][j] = EMPTY;
           else if(board[row][j] == EMPTY)
               continue;
           else
               break;
 
       }
 
       for(int j = col; j >= 1; j--){
 
           if(board[row][j] == num)
               board[row][j] = EMPTY;
           else if(board[row][j] == EMPTY)
               continue;
           else
               break;
       }
 
   }
 
 
   if(PiecesEqualLeft(row, col, num)){
 
       for(int j = col; j >= 1; j--){
 
           if(board[row][j] == num)
               board[row][j] = EMPTY;
           else if(board[row][j] == EMPTY)
               continue;
           else
               break;
       }
 
   }
}
 
// Mark the scoring structure(s) as EMPTY.
void ExecuteMovement(int row, int col, int num){
 
   BrandPartsEqualOnSameLine(row, col, num);
   BrandPartsEqualInSameColumn(row, col, num);
 
}
 
 
// Performs the movement of the piece.
void MovePiece(){
 
   int lineorigin = mover.origin.first;
   int columnorigin = mover.origin.second;
 
   int linedestination = mover.destination.first;
   int columndestination = mover.destination.second;
 
   int pecaorigin = board[lineorigin][columnorigin];
   int pecadestination = board[linedestination][columndestination];
 
   if(ScorableStructure(linedestination, columndestination, pecaorigin)){
 
       board[lineorigin][columnorigin] = pecadestination;
       board[linedestination][columndestination] = pecaorigin;
 
 
       ExecuteMovement(linedestination, columndestination, pecaorigin);
 
       if(ScorableStructure(lineorigin, columnorigin, pecadestination)){
           ExecuteMovement(lineorigin, columnorigin, pecadestination);
       }
 
   }
 
}
 
// Calculates the number of empty pieces in the
// board and returns this number to be added
// the total score.
int CalculateScore(){
 
   int qtyMarkedParts = 0;
 
   for(int row = 1; row <= N; row++){
       for(int col = 1; col <= N; col++){
 
           if(board[row][col] == EMPTY)
               qtyMarkedParts++;
 
       }
   }
 
   return qtyMarkedParts;
}
 
//Use the BuildBoard() function to avoid
// create scoring structures
void ReBuildBoard(){
   BuildBoard();
}
 
// Check if the movement is valid
bool isValidMovement(){
 
   int lineorigin = mover.origin.first;
   int columnorigin = mover.origin.second;
 
   int linedestination = mover.destination.first;
   int columndestination = mover.destination.second;
 
   if( (abs(linedestination - lineorigin) == 1 )||
       (abs(columndestination - columnorigin) == 1) ){
 
 
       if( (abs(linedestination - lineorigin) == 1) &&
           (abs(columndestination - columnorigin) == 1))
           return false;
 
       else if(board[linedestination][columndestination] == EDGE ||
               board[lineorigin][columnorigin]   == EDGE)
           return false;
 
       else
           return true;
 
   }
 
   return false;
 
}
 
// Look for valid movements.
bool ExistMovement(){
 
   for(int i = 1; i <= N; i++){
       for(int j = 1; j <= N; j++){
 
           if( ScorableStructure(i+1, j, board[i][j]) ||
               ScorableStructure(i-1, j, board[i][j]) ||
               ScorableStructure(i, j+1, board[i][j]) ||
               ScorableStructure(i, j-1, board[i][j]))
               return true;
       }
   }
 
   return false;
}
 
 
// run the program
int main(int argc, char* argv[]){
 
   //Reading the board dimension
   cout<<"The board dimension: "<<endl;
   cin>>N;
 
   cout<<"The maximum amount of color on the board: "<<endl;
   cin>>D;
 
   cout<<"Seed for generation of pseudo-random numbers, any integer value: "<<endl;
   cin>>S;
 
   // Powering the pseudorandom number generator
   srand(S);
   allocateBoard();
 
   BuildBoard();
   PrintBoard();
 
   do{
 
       cout<<"Source row: ";
       cin>>line;
       cout<<"Source column: ";
       cin>>column;
       mover.origin = make_pair (line,column);
 
       cout<<"Target row: ";
       cin>>line;
       cout<<"Target column: ";
       cin>>column;
       mover.destination = make_pair (line,column);
 
       if(!isValidMovement()){
           cout << "Your movement is invalid.";
           cout << "Please, make another move." << endl;
           continue;
       }
 
       MovePiece();
       points = CalculateScore();
       cout<<"Score: "<< points <<endl;
       pointsTotal += points;
 
       PrintBoard();
       ReBuildBoard();
 
       cout<<"\nCurrent board: "<<endl;
       PrintBoard();
 
   }while(ExistMovement());
 
   cout << "End of the game." << endl;
   cout << "Total score: " << pointsTotal << endl;
 
 
   return 0;
}
 

