/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>



/*=========================================================================
  Constants and definitions:
========================================================================== */
#define sizeOfBoard 9



/*-------------------------------------------------------------------------

 -------------------------------------------------------------------------*/
void printTable (char gameTable [][3][3]);
void printRow(char gameTable [][3][3],int row);
void setArry(char arryToSet [][3][3],int arrayLen);
int getChecksubBoard(char gameTable[][3][3],int* subBoard,int TableLength);
bool boardIsFull (char gameTable [][3][3], int subBoard);
bool boardIsOk (int tableLength, int subBoard);
int getChecksubPosition (char gameTable [][3][3], int subBoard);
bool emptyPlace (char gameTable [][3][3], int subBoard,int position);
int getNextBoard (char gameTable [][3][3], int position);
void checkWinInSuboard(char table [][3][3],char boardWinner[][3][3],
                       int board,int turn);
bool checkLine (char Table [][3][3],int board);
bool checkRow(char Table [][3][3],int board);
bool checkDiagonal  (char Table [][3][3],int board);
bool checkGameEnd(char table[][3][3],int len,int turn);
bool winG(char table[][3][3],int len,int turn);
char playerTurn(int turn);
void gameRunner(char gameTable[][3][3],char boardWinner[][3][3],
           int* subBoard,int* position,int turn);
int getUserScanf(char gameTable [][3][3],int TableLen,int* subBoard,
                 int* position,int turn);
// 13 lines
// print the game board
void printTable (char gameTable [][3][3]){
      printf(" 1  1  1 2  2  2 3  3  3 \n");
      printRow(gameTable,1);
      printRow(gameTable,2);
      printRow(gameTable,3);
      printf(" ------- ------- ------- \n");
      printRow(gameTable,4);
      printRow(gameTable,5);
      printRow(gameTable,6);
      printf(" ------- ------- ------- \n");
      printRow(gameTable,7);
      printRow(gameTable,8);
      printRow(gameTable,9);
      printf(" 7  7  7 8  8  8 9  9  9 \n");
}
// 8 lines
// print one line of the game board
void printRow(char gameTable [][3][3],int row)
{
    printf("%d",(3*(((row-1)/3)+1)-2));
    for (int i=0; i<3; i++)
    {
         for (int j=0; j<3; j++)
         {
            if (j!=2)
           printf("%c  ",gameTable [3*(((row-1)/3))+i][((row-1)%3)][j]);
           else
            printf("%c",gameTable [3*(((row-1)/3))+i][((row-1)%3)][j]);
         }
    printf("|");
    }
    printf("%d\n",(((row-1)/3)+1)*3);
}
// 4 lines
//set array to ' '
void setArry(char arryToSet [][3][3],int arrayLen)
{
     for (int i=0; i<arrayLen; i++)
         for (int j=0; j<3; j++)
            for (int g=0; g<3; g++)
                    arryToSet [i][j][g]=' ';
}
// 9 lines
//get some sub boards form the user until we get legal one.
int getChecksubBoard(char gameTable [][3][3],int* subBoard,int TableLength)
{

    do
    {
        if (scanf(" %d",&*subBoard)!=1)
                    return -1;
        while(!boardIsOk(TableLength,*subBoard))
            if (scanf(" %d",&*subBoard)!=1)
              return -1;
         if(boardIsFull (gameTable,*subBoard))
         {
    printf("Sub-board %d is full. Please choose another one:\n",*subBoard);
         }
    }while (boardIsFull (gameTable,*subBoard));
        return *subBoard;
    }
// 6 lines
//check if the is full and return the answer
bool boardIsFull (char gameTable [][3][3], int subBoard)
{
       int count=0;
        for (int i=0; i<3; i++)
          for (int j=0; j<3; j++)
               if (gameTable [subBoard-1][i][j]!=' ')
                    count++;
      return count==9;
   }
// 4 lines
//check if the board number is legal and print message
bool boardIsOk (int tableLength, int subBoard)
{
 if ((subBoard<=0) ||(subBoard>tableLength-1))
    {
     printf("Index out of range. Please enter a value between 1 and 9:\n");
     return false;
    }
    return true;
}
// 9 lines
//get some positions form the user until we get legal and empty one.
int getChecksubPosition (char gameTable [][3][3], int subBoard)
{
 int position=0;
 do
{
 if (scanf(" %d",&position)!=1)
        return -1;
 while((position<1)||(position>9))
    {
     printf("Index out of range. Please enter a value between 1 and 9:\n");
            if (scanf(" %d",&position)!=1)
              return -1;
    }
}

while (!emptyPlace(gameTable,subBoard,position));
        return position;
}
// 4 lines
//check if the position is empty in the sub board.
bool emptyPlace (char gameTable [][3][3], int subBoard,int position)
{
    if (gameTable [subBoard-1][((position-1)/3)][(position-1)%3]!=' ')
    {
        printf("Position is taken, please choose another one:\n");
        return false;
    }
    return true;
}
// 13 lines
//if need new sub board we get one, and get new position
int getUserScanf(char gameTable [][3][3],int TableLen,int* subBoard,
                 int* position,int turn)
{
    if (*subBoard==0)
        {
        printf("Player %c, please enter the index",playerTurn(turn));
        printf(" of the wanted sub-board:\n");
        if (getChecksubBoard(gameTable,subBoard, TableLen)==-1)
            {
                printf("Input error!\n");
                return 1;
            }
        }
    printf("Player %c, please enter the ",playerTurn(turn));
    printf("wanted position in sub-board %d:\n", *subBoard);
    *position=getChecksubPosition(gameTable,*subBoard);
        if (*position==-1)
        {
            printf("Input error!\n");
                return 1;
        }
    return 0;

}
// 4 lines
//return the char of the turn's player
char playerTurn(int turn)
{
    if (turn%2==0)
        return 'X';
    else
        return 'O';
}
// 4 lines
//if the board is full we set the next board
int getNextBoard (char gameTable [][3][3], int position)
    {
        if (boardIsFull(gameTable,position))
            return 0;
        else
        return position;
    }
// 6 lines
//if there is new winning in sub board, we print message and mark in
// winners table
void checkWinInSuboard(char table [][3][3],char boardWinner[][3][3]
                       ,int board,int turn)
{
    if (boardWinner[0][((board-1)/3)][(board-1)%3]==' ')
        if (checkLine(table,board)||checkRow(table,board)
            ||checkDiagonal (table,board))
        {
        boardWinner[0][((board-1)/3)][(board-1)%3]=playerTurn(turn);
        printf("Player %c ",playerTurn(turn));
        printf("has won in sub-board %d!\n",board);
        }
}
// 6 lines
//check if there is winning in some line in the sub board
bool checkLine (char Table [][3][3],int board)
{
    for (int i=0; i<3; i++)
    if(Table [board-1][i][0]==Table [board-1][i][1])
        if(Table [board-1][i][1]==Table [board-1][i][2])
            if(Table [board-1][i][1]!=' ')
               return true;
    return false;
}
// 6 lines
//check if there is winning in some row in the sub board
bool checkRow(char Table [][3][3],int board)
{
    for (int i=0; i<3; i++)
    if(Table [board-1][0][i]==Table [board-1][1][i])
        if(Table [board-1][1][i]==Table [board-1][2][i])
             if(Table [board-1][1][i]!=' ')
                 return true;
    return false;
}
// 9 lines
//check if there is winning in some diagonal in the sub board
bool checkDiagonal  (char Table [][3][3],int board)
{
    if(Table [board-1][0][0]==Table [board-1][1][1])
        if(Table [board-1][1][1]==Table [board-1][2][2])
             if(Table [board-1][0][0]!=' ')
          return true;
    if(Table [board-1][0][2]==Table [board-1][1][1])
        if(Table [board-1][1][1]==Table [board-1][2][0])
            if(Table [board-1][1][1]!=' ')
          return true;
    return false;
}
// 9 lines
//check if someone win the game, or if it's tie, and print message
bool checkGameEnd(char table[][3][3],int len,int turn)
{
  if (checkLine(table,len)||checkRow(table,len)||checkDiagonal (table,len))
     {
        printf("Game over, %c is the winner!\n",playerTurn(turn-1));
        return true;
     }
     if(turn==81)
        {
        printf("Game over, it's a tie!\n");
        return true;
        }
 return false;
}
// 4 lines
//mark the move, check for winner in sub board, and get next board
void gameRunner(char gameTable[][3][3],char boardWinner[][3][3],
           int* subBoard,int* position,int turn)
{
    gameTable[*subBoard-1][((*position-1)/3)][(*position-1)%3]=
    playerTurn(turn);
   checkWinInSuboard(gameTable,boardWinner,*subBoard,turn);
   *subBoard= getNextBoard(gameTable,*position);
}
// 13 lines
// declare and set the variables,for every turn get inputs and run the
// system of the game.
int main( )
{
   char gameTable [sizeOfBoard][3][3]={{{0}}},boardWinner[1][3][3]={{{0}}};
    int turn=0, subBoard=0, position=0;
    int *pointerSubBoard =&subBoard, *poinerPosition=&position;
    setArry(gameTable,sizeOfBoard);
    setArry(boardWinner,1);
    printf("Welcome to Ultimate Tic-Tac-Toe!\n");
    while(!checkGameEnd(boardWinner,1,turn))
    {
      printTable(gameTable);
    if( getUserScanf(gameTable,9,pointerSubBoard,poinerPosition,turn)==1)
                return 1;
    gameRunner(gameTable, boardWinner,pointerSubBoard,poinerPosition,turn);
    turn++;
    }
         return 0;
}
