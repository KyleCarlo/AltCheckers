#include <stdio.h>
#define P_BOARD_COL 5
#define P_BOARD_ROW 7

const int BLANK[2] = {0,0};

typedef enum {True = 1, False = 0} bool;
typedef int cart_p[2];
// enum {AlphaWins = 1, BetaWins = 0};

void inputPlayerMove(cart_p nPrev, cart_p nNext);                   //asking for piece selection and movement
int isInputESet(cart_p input, cart_p nSet[]);                       //checking if the input is an element of given set
int isAdjacent(int nB, int nD);                                     //checking if the movement is diagonal or straight forward
int isInputEFree(cart_p input, cart_p nAlpha[], cart_p nBeta[]);    //checking if the movement is or not included in Alpha and Beta set
void replaceESet(const cart_p add, cart_p remove, cart_p nSet[]);   //checking if a piece can take down the oppenent's piece
int isInputESpec(cart_p input);                                     //checking if the input is an element of S set
void printBoard(cart_p nAlpha[], cart_p nBeta[]);                   //prints the board and pieces of players

int main()
{
    // SYSTEM VARIABLES
    bool bool_over = False, 
         bool_ok = False, 
         bool_aTurn = True; 
    cart_p nAlpha[5] = {
                        {6,2},
                        {6,4},
                        {7,1},
                        {7,3},
                        {7,5}
                    },
           nBeta[5] = {
                        {1,1},
                        {1,3},
                        {1,5},
                        {2,2},
                        {2,4}
                    };
    
    // inputs
    cart_p nPrev,                                           //a = nPrev[0], b = nPrev[1] 
           nNext;                                           //c = nNext[0], d = nNext[1]
           
    while (1) //TO DO: Figure out how to end the game properly
    {    
        printBoard(nAlpha, nBeta);
        
        if (bool_aTurn)
            printf("Alpha's Turn\n");
        else    
            printf("Beta's Turn\n");
        inputPlayerMove(nPrev, nNext);                      //scan for nPrev & nNext inputs

        if (bool_aTurn)
        {
            if (
                    isInputESet(nPrev, nAlpha) &&           //if (a,b) an element of alpha set
                    nPrev[0] == nNext[0] + 1 &&             //if making a 1-tile forward movement
                    isAdjacent(nPrev[1], nNext[1])          //if making a 1-tile diagonal or straight movement
            ) 
            {
                bool_ok = !bool_ok;
            }
        } else {
        if (
                    isInputESet(nPrev, nBeta) &&            //if (a,b) an element of beta set
                    nNext[0] == nPrev[0] + 1 &&             //if making a 1-tile backward movement
                    isAdjacent(nPrev[1], nNext[1])          //if making a 1-tile diagonal or straight movement
            )  
            {
                bool_ok = !bool_ok;
            }
        }

        if (bool_ok)
        {
            if (bool_aTurn)
            {
                
                if (isInputEFree(nNext, nAlpha, nBeta))     //ok ^ aTurn ^ next E Free
                {
                    replaceESet(nNext, nPrev, nAlpha);      //replace nNext to nPrev
                    bool_aTurn = !bool_aTurn;
                }
                
                else if (isInputESet(nNext, nBeta)) 
                    if (isInputESpec(nNext))                //ok ^ aTurn ^ next E Beta ^ next E S
                    {
                        replaceESet(nNext, nPrev, nAlpha);  //alpha piece eats beta piece
                        replaceESet(BLANK, nNext, nBeta);   //removes beta piece
                        
                        bool_aTurn = !bool_aTurn; 
                    }                      
            } 
            else 
            {
                if (isInputEFree(nNext, nAlpha, nBeta))     //ok ^ ~aTurn ^ next E Free
                {
                    replaceESet(nNext, nPrev, nBeta);       //replace nNext to nPrev
                    bool_aTurn = !bool_aTurn;
                }
                
                else if (isInputESet(nNext, nAlpha))        //alpha piece eats beta piece
                    if (isInputESpec(nNext))                //ok ^ ~aTurn ^ next E Beta ^ next E S
                    {
                        replaceESet(nNext, nPrev, nBeta);
                        replaceESet(BLANK, nNext, nAlpha);  //removes alpha piece
                        bool_aTurn = !bool_aTurn;
                    }
            }
            bool_ok = !bool_ok;
        } 
    }
    
    return 0;
}

void inputPlayerMove(cart_p nPrev, cart_p nNext)
{
    do{
        printf("Prev (a,b): ");
        scanf("%d %d", nPrev, nPrev + 1);

        if (nPrev[0] < 1 || nPrev[0] > P_BOARD_ROW ||
            nPrev[1] < 1 || nPrev[1] > P_BOARD_COL)
        {
            printf("Invalid Input\n");
        }
        
    } while (nPrev[0] < 1 || nPrev[0] > P_BOARD_ROW ||
             nPrev[1] < 1 || nPrev[1] > P_BOARD_COL);

    do{
        printf("Next (c,d): ");
        scanf("%d %d", nNext, nNext + 1);

        if (nNext[0] < 1 || nNext[0] > P_BOARD_ROW ||
            nNext[1] < 1 || nNext[1] > P_BOARD_COL)
        {
            printf("Invalid Input\n");
        }
        
    } while (nNext[0] < 1 || nNext[0] > P_BOARD_ROW ||
             nNext[1] < 1 || nNext[1] > P_BOARD_COL);
}

int isInputESet(cart_p input, cart_p nSet[])
{
    int i;

    for (i = 0; i < 5; i++)
        if (input[0] == nSet[i][0] && input[1] == nSet[i][1])
            return True;

    return False;
}

int isAdjacent(int nB, int nD)
{
    if (nD == nB || nD == nB + 1 || nB == nD + 1)
        return True;

    return False;
}

int isInputEFree(cart_p input, cart_p nAlpha[], cart_p nBeta[])
{
    if (!isInputESet(input, nAlpha) && !isInputESet(input, nBeta))
        return True;
    
    return False;
}

void replaceESet(const cart_p add, cart_p remove, cart_p nSet[])
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (remove[0] == nSet[i][0] && remove[1] == nSet[i][1])
        {
            nSet[i][0] = add[0];
            nSet[i][1] = add[1];
            return;
        }
    }
}

int isInputESpec(cart_p input)
{
    //to be an element of S, 
    //x and y are both odd or both even
    if (input[0] % 2)
    {
        if (input[1] % 2)
            return True;
        else    
            return False;
    }
    else
    {
        if (input[1] % 2)
            return False;
        else    
            return True;
    }    
}

void printBoard(cart_p nAlpha[], cart_p nBeta[])
{
    int i, j, k;
    bool isPrint;
    printf("    ");
    for (i = 1; i <= P_BOARD_COL; i++)
    {
        printf("%d ", i);
    }
    printf("\n\n");
    
    for (i = 1; i <= P_BOARD_ROW; i++)
    {
        printf("%d   ", i);
        for (j = 1; j <= P_BOARD_COL; j++)
        {   
            isPrint = True;
            for (k = 0; k < 5; k++)
            {
                if (i == nAlpha[k][0] && j == nAlpha[k][1])
                {
                    printf("A ");
                    isPrint = !isPrint;
                    break;
                }
                else if (i == nBeta[k][0] && j == nBeta[k][1])
                {
                    printf("B ");
                    isPrint = !isPrint;
                    break;
                }
            }
            if (isPrint)
                printf("* ");
                
            isPrint = !isPrint;
        }
        printf("\n");   
    }
    //printing coordinates of pieces
    //TESTING PURPOSES ONLY
    printf("COORDINATES\n");
    printf("ALP | BET\n");
    for (j = 0; j < 5; j++)
    {
        for (i = 0; i < 2; i++)
        {
            printf("%d ", nAlpha[j][i]);
        }
        printf("| ");
        for (i = 0; i < 2; i++)
        {
            printf("%d ", nBeta[j][i]);
        }
        printf("\n");
    }
}