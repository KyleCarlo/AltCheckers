#include <stdio.h>
#define P_BOARD_COL 5
#define P_BOARD_ROW 7

typedef enum {True = 1, False = 0} bool;
typedef int cart_p[2];

void inputPlayerMove(cart_p nPrev, cart_p nNext);
int isInputESet(cart_p input, cart_p nSet[]);
int isAdjacent(int nB, int nD);

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
    cart_p nPrev, //a = nPrev[0], b = nPrev[1] 
           nNext; //c = nNext[0], d = nNext[1]
    inputPlayerMove(nPrev, nNext);

    if (bool_aTurn)
    {
        if (
                isInputESet(nPrev, nAlpha) && //if (a,b) an element of alpha set
                nPrev[0] == nNext[0] + 1 && //if making a 1-tile forward movement
                isAdjacent(nPrev[1], nNext[1]) //if making a 1-tile diagonal or straight movement
        ) 
        {
            bool_ok = !bool_ok;
        }
    } else {
       if (
                isInputESet(nPrev, nBeta) && //if (a,b) an element of beta set
                nNext[0] == nPrev[0] + 1 && //if making a 1-tile backward movement
                isAdjacent(nPrev[1], nNext[1]) //if making a 1-tile diagonal or straight movement
        )  
        {
            bool_ok = !bool_ok;
        }
    }
    if (bool_ok)
    {
        printf("OK");
    }
    



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
    {
        if (*input == *nSet[i])
        {
            return True;
        }
    }
    return False;
}

int isAdjacent(int nB, int nD)
{
    if (nD == nB || nD == nB + 1 || nB == nD + 1)
        return True;
    return False;
}