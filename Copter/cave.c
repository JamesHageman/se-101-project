#include <OrbitOled.h>
#include <OrbitOledGrph.h>
#include "cave.h"
#include "gamestate.h"
#include "constants.h"

void drawCave(GameState *state) {
    int i=0, j=0, x=0, c=0;
  for( i=0; i<MAX_HEIGHT; i++){
        for( j=0; j<MAX_WIDTH; j++){
            if(state->caveObject[i][j] == '#' ){
                OrbitOledMoveTo(j,i); 
                OrbitOledDrawPixel();
            }
        }
        
    }

}

void createCave(GameState *state) {
    srand(1);
    int i=0, j=0, x=0, c=0;
    int shift = 0;
   
    for( i=0; i<MAX_HEIGHT; i++){
        for( j=0; j<MAX_WIDTH; j++){
            state->caveObject[i][j] = '.';
        }
    }
    int y=0;
    int lineLength = 8;
    //iterate through each horizontal line of the cave
    for( x = 0; x<MAX_WIDTH/lineLength; x++){
        
        int sign = rand() % 2;
        
        
        if (sign == 1 && y < 10) //go down 1, with limit 10 down as max
            y += 1;
        else if(y>0)
            y -= 1;

        //loop to draw line segement of cave
        for( c=0; c<lineLength; c++){
            //printf(" x: %d y: %d \n", x*lineLength+c, y );
            state->caveObject[y][x*lineLength+c] = '#';
            
            state->caveObject[y+22][x*lineLength+c] = '#';
        }
        
    }
    
    //add obstacles to cave
//    int lineHeight = 4;
//    for (i = 0; i < MAX_WIDTH/64; i++){
//        //draw vertical line at random height
//        int heightFromTop = rand() % MAX_HEIGHT/2;
//        //loop through vertical line
//        for( j=0; j<lineHeight; j++){
//            state->caveObject[j+heightFromTop][i*64] = '#';
//        }
//    }
    
}

void shiftCave(GameState *state){
  int i=0, j=0, x=0, c=0, v=0;
  for( i=0; i<MAX_HEIGHT; i++){
        for( j=0; j<MAX_WIDTH; j++){
            state->caveObject[i][j] = state->caveObject[i][j+1]; 
        }
      
      //clear the last column
        state->caveObject[i][127] = '.';
    }
    
    state->cavePosition += 1;
    
    
    int foundLine = 0;
    for( i=0; i<MAX_HEIGHT && foundLine == 0; i++){
        if(state->caveObject[i][126] == '#' && state->caveObject[i][125] == '#' && state->caveObject[i][124] == '#' ){
           int sign = rand() % 2;
            int icopy = i;

            if (sign == 1 && icopy < 9) //go down 1, with limit 10 down as max
                icopy +=1;
            else if(i>0)
                icopy -=1; 
            state->caveObject[icopy][127] = '#';
            state->caveObject[icopy +22][127] = '#';
            foundLine = 1;
        } else if(state->caveObject[i][126] == '#' ) {
            state->caveObject[i][127] = '#'; //keep going
        }
    }
    
    //add obstacle
    if(   state->obstacleOnScreen == 0){
        state->obstacleOnScreen = 1;
        int lineHeight = 4;
        //draw vertical line at random height
        int heightFromTop = rand() % MAX_HEIGHT/2;
        //loop through vertical line
        for( v=0; v<lineHeight; v++){
            
            state->caveObject[v+heightFromTop][127] = '#';
        }
        
    } 
    
    if( state->cavePosition %128 == 0){
        state->obstacleOnScreen = 0;
    }
    
}