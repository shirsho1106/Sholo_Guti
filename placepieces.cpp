#include<graphics.h>
#include "header.hpp"
#include<iostream>
#include<queue>

using namespace std;

extern pair<int,int> yellow_pcs[16];
extern pair<int,int> white_pcs[16];
extern struct Board{
    pair<int,int> coord;
    queue< pair<int,int> > neighs;
    queue< pair<int,int> > lines;
}board[37];

// Drawing the pieces

void placePieces(int x, int y){

    //setcolor(WHITE);

    int radius = 10;

    for(int i = 1 ; i <= radius; i=i++){
        circle(x,y,i);
    }

}

int whichPiece(pair<int,int>x){
    for(int i = 0; i<16 ; i++){
        if(x==white_pcs[i]) return PLAYER_WHITE;
        if(x==yellow_pcs[i]) return PLAYER_YELLOW;
    }
    return 0;
}
