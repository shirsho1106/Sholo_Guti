#include<stdio.h>
#include<graphics.h>
#include<iostream>
#include "header.hpp"
#include<queue>
#include<stdlib.h>

using namespace std;

extern bool dontChange;

extern pair<int,int> yellow_pcs[16];
extern pair<int,int> white_pcs[16];

extern struct Board{
    pair<int,int> coord;
    queue< pair<int,int> > neighs;
    queue< pair<int,int> > lines;
}board[37];

bool WhitesMove = false;

extern bool TWO_PLAYER_MODE;
extern bool AI_MODE;


                                                                    // End indicating function

int ifFinished(){


    int take = 0;

    for(int i = 0 ; i < 16 ; i++){
        if(white_pcs[i]!=make_pair(0,0)){take = PLAYER_WHITE;break;}
    }

    for(int i = 0 ; i < 16 ; i++){
        if(yellow_pcs[i]!=make_pair(0,0)){
            if(take==PLAYER_WHITE) return 0;
            else return PLAYER_YELLOW;
        }
    }

    return PLAYER_WHITE;
}


void selectPiece(pair<int,int>select){
    setcolor(YELLOW);
    circle(select.first,select.second,11);
    circle(select.first,select.second,10);
    circle(select.first,select.second,9);
}

/*


    - The following two functions are for controlling the game with mouse

    - mouseControl function selects the piece to move

    - mouseControl2 function selects the destination point

    - Then it calls the kill/general move function for moving the piece

    - It controls the player who will make the next move

*/



bool mouseControl2(int j, int color){
    POINT cursor;
    int x,y;
    bool take = false;
    while(1){
        delay(100);

        GetCursorPos(&cursor);x=cursor.x;y=cursor.y-25;

        for(int i = 0 ; i < 37 ; i++){
                if(((x>board[i].coord.first-10)&&(x<board[i].coord.first+10))&&((y>board[i].coord.second-10)&&(y<board[i].coord.second+10))){

                    //setcolor(WHITE);circle(board[i].coord.first,board[i].coord.second,11);
                }
        }

        if(GetAsyncKeyState(VK_LBUTTON)){
            GetCursorPos(&cursor); x = cursor.x; y = cursor.y-25;
            for(int i = 0 ; i < 37 ; i++){
                if(((x>board[i].coord.first-10)&&(x<board[i].coord.first+10))&&((y>board[i].coord.second-10)&&(y<board[i].coord.second+10))){
                    if(pieceAvailable(board[i].coord)) break;
//                    if(color == PLAYER_WHITE)
//                        white_pcs[j] = board[i].coord;
//                    else yellow_pcs[j] = board[i].coord;
                    if(color==PLAYER_WHITE)
                        take = move_piece(j,i,PLAYER_WHITE);
                    else
                        take = move_piece(j,i,PLAYER_YELLOW);
                    //else break;
                    cleardevice();
                    drawBoard();
                    return take;
                }
            }
            //if(!take) AI_MODE = false;
            return take;
        }

    }

}



void mouseControl(){
    //set();
    //initializeGeneralMoves();
    //initializeKillMoves();
    //getch();
    POINT cursor;
    int x,y, whoWin = 0;
    bool take = false;

    while(1){
        whoWin = ifFinished();
        if(whoWin) break;
        delay(100);

        GetCursorPos(&cursor);x=cursor.x;y=cursor.y-25;

        for(int i = 0 ; i < 37 ; i++){
                if(((x>board[i].coord.first-10)&&(x<board[i].coord.first+10))&&((y>board[i].coord.second-10)&&(y<board[i].coord.second+10))){

                    //setcolor(WHITE);circle(board[i].coord.first,board[i].coord.second,11);
                }
        }

        if(GetAsyncKeyState(VK_LBUTTON)){
            GetCursorPos(&cursor);x=cursor.x;y=cursor.y-25;
                //Newlyadded
                if(dontChange)
                {
                    for(int i = 0 ; i < 16 ; i++){
                    if(((x>white_pcs[i].first-10)&&(x<white_pcs[i].first+10))&&
                       ((y>white_pcs[i].second-10)&&(y<white_pcs[i].second+10))){
                        cleardevice();
                        drawBoard();setcolor(BLACK);circle(white_pcs[i].first,white_pcs[i].second,11);
                        circle(white_pcs[i].first,white_pcs[i].second,12);
                        circle(white_pcs[i].first,white_pcs[i].second,13);
                        take = mouseControl2(i,PLAYER_WHITE);
                        //while(!take) take = mouseControl2(i,PLAYER_WHITE);
                        if(take&&AI_MODE) gameAI();
                        else if(take)WhitesMove = false;
                    }
                    }
                    for(int i = 0 ; i < 16 ; i++){
                    if(((x>yellow_pcs[i].first-10)&&(x<yellow_pcs[i].first+10))&&
                       ((y>yellow_pcs[i].second-10)&&(y<yellow_pcs[i].second+10))){
                        cleardevice();
                        drawBoard();
                        setcolor(RED);circle(yellow_pcs[i].first,yellow_pcs[i].second,11);
                        circle(yellow_pcs[i].first,yellow_pcs[i].second,12);
                        circle(yellow_pcs[i].first,yellow_pcs[i].second,13);
                        take = mouseControl2(i,PLAYER_YELLOW);
                        if(take&&AI_MODE) gameAI();
                        else if(take)WhitesMove = true;
                    }
                    }
                    continue;
                }
                //Done
                if(WhitesMove)
                    for(int i = 0 ; i < 16 ; i++){
                    if(((x>white_pcs[i].first-10)&&(x<white_pcs[i].first+10))&&
                       ((y>white_pcs[i].second-10)&&(y<white_pcs[i].second+10))){
                        cleardevice();
                        drawBoard();setcolor(BLACK);circle(white_pcs[i].first,white_pcs[i].second,11);
                        circle(white_pcs[i].first,white_pcs[i].second,12);
                        circle(white_pcs[i].first,white_pcs[i].second,13);
                        take = mouseControl2(i,PLAYER_WHITE);
                        //while(!take) take = mouseControl2(i,PLAYER_WHITE);
                        if(take&&AI_MODE) gameAI();
                        else if(take)WhitesMove = false;
                    }
                    }
                else
                    for(int i = 0 ; i < 16 ; i++){
                    if(((x>yellow_pcs[i].first-10)&&(x<yellow_pcs[i].first+10))&&
                       ((y>yellow_pcs[i].second-10)&&(y<yellow_pcs[i].second+10))){
                        cleardevice();
                        drawBoard();
                        setcolor(RED);circle(yellow_pcs[i].first,yellow_pcs[i].second,11);
                        circle(yellow_pcs[i].first,yellow_pcs[i].second,12);
                        circle(yellow_pcs[i].first,yellow_pcs[i].second,13);
                        take = mouseControl2(i,PLAYER_YELLOW);
                        if(take&&AI_MODE) gameAI();
                        else if(take)WhitesMove = true;
                    }
                    }

        }
    }
    closegraph();
    printf("\nPLAYER %d WINS THE GAME\n",whoWin);
    menu();
}
