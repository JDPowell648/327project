#include <iostream>
#include "rule.h"
#include "CellularAutomaton.h"
#include "GraphicsClient.h"

unsigned char GameOfLife(CellularAutomaton* DCA, int x, int y){
	//Game of Life Rule for a 2DCA-> The rules are as follows:
	//Any live cell with two or three live neighbours survives.
	//Any dead cell with three live neighbours becomes a live cell.
	//All other live cells die in the next generation. Similarly, all other dead cells stay dead.
	//https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
	
	//This implentation checks all 8 neighbors and totals how many neighbors are alive and how many neighbors are dead.
	int numAlive = 0;
	int width = DCA->getWidth();
	int height = DCA->getHeight();
	
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			int newY = (y + i + height) % height;
			int newX = (x + j + width) % width;
			//printf("newY:%i, newX:%i, cell value:%i, bool:%i\n", newY,newX,(int)DCA->getCell(newY,newX),!(i == 0 && j == 0));
			if(!(i == 0 && j == 0)){
				if((int)DCA->getCell(newY,newX) != 0){
					numAlive++;
				}
			}
		}
	}
	
	//printf("y:%i, x:%i\n", y,x);
	//printf("numAlive: %i\n\n", numAlive);
	//Debugging prints, can disregard.
	if(numAlive == 2 || numAlive == 3){
		if(DCA->getCell(y,x) != 0){
			return 1;
		}
	}
	if(numAlive == 3){
		if(DCA->getCell(y,x) == 0){
			return 1;
		}
	}
	return 0;
	
}


