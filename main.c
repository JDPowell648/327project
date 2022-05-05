#include <stdio.h>
#include "ca.h"
#include "ca.c"
#include <string.h>

unsigned char GameOfLife(ca_data * DCA, int x, int y){
	//Game of Life Rule for a 2DCA. The rules are as follows:
	//Any live cell with two or three live neighbours survives.
	//Any dead cell with three live neighbours becomes a live cell.
	//All other live cells die in the next generation. Similarly, all other dead cells stay dead.
	//https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
	
	//This implentation checks all 8 neighbors and totals how many neighbors are alive and how many neighbors are dead.
	int numAlive = 0;
	int numDead = 0;
	//printf("y: %i, x: %i, value: %hhu\n", y, x, DCA->cadata[y][x]);
	if(DCA->wrap == 0){ //nowrap implementation
		unsigned char noWrapVal = DCA->qstate;
		if(y == 0 || x == 0){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y-1][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		if(y == 0){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y-1][x] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(y == 0 || x == DCA->width - 1){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y-1][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(x == 0){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(x == DCA->width - 1){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(x == 0 || y == DCA->height - 1){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y+1][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(y == DCA->height - 1){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y+1][x] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(x == DCA->width - 1 || y == DCA->height - 1){
			if(noWrapVal == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y+1][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
	}else if(DCA->wrap == 1){ //wrap implementation
		if(y == 0 && x == 0){
			if(DCA->cadata[DCA->height-1][DCA->width-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(x == 0){
			if(DCA->cadata[y-1][DCA->width-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(y == 0){
			if(DCA->cadata[DCA->height-1][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y-1][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		if(y == 0){
			if(DCA->cadata[DCA->height-1][x] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y-1][x] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(x == DCA->width - 1 && y == 0){
			if(DCA->cadata[DCA->height-1][0] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(x == DCA->width - 1){
			if(DCA->cadata[y-1][0] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(y == 0){
			if(DCA->cadata[DCA->height-1][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y-1][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		if(x == 0){
			if(DCA->cadata[y][DCA->width-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(x == DCA->width - 1){
			if(DCA->cadata[y][0] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		
		if(y == DCA->height - 1 && x == 0){
			if(DCA->cadata[0][DCA->width-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(y == DCA->height - 1){
			if(DCA->cadata[0][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(x == 0){
			if(DCA->cadata[y + 1][DCA->width-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y+1][x-1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(y == DCA->height - 1){
			if(DCA->cadata[0][x] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y+1][x] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
		
		if(y == DCA->height - 1 && x == DCA->width - 1){
			if(DCA->cadata[0][0] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(y == DCA->height - 1){
			if(DCA->cadata[0][x + 1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else if(x == DCA->width - 1){
			if(DCA->cadata[y+1][0] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}else{
			if(DCA->cadata[y+1][x+1] == 0){
				numDead++;
			}else{
				numAlive++;
			}
		}
	}
	//printf("numAlive: %i ", numAlive);
	//printf("numDead %i\n\n", numDead);
	//Debugging prints, can disregard.
	if(numAlive == 2 || numAlive == 3){
		if(DCA->cadata[y][x] != 0){
			return 1;
		}
	}
	if(numAlive == 3){
		if(DCA->cadata[y][x] == 0){
			return 1;
		}
	}
	return 0;
	
}

int main(int argc, char *argv[]){
	char *p;
	unsigned int dimension = strtol(argv[1], &p, 10);
	char* filepath = argv[2];
	ca_data * DCA;
	FILE* inFile = NULL;
	inFile = fopen(filepath, "r");
	if(inFile == NULL){
		printf("Could not open the file provided\n");
		return -1;
	}
	int w,h;
	if(dimension == 1){
		fscanf(inFile, "%i", &w);
		DCA = create1DCA(w, 0); //qstate is initialized as 0 in this implementation. Change this if you want a different qstate.
		DCA->dimension = dimension;
		for(int i = 0; i < w; i++){
			int data;
			DCA->wrap = 1;//In this implentation, we will always wrap. Change this value to 0 to use no wrapping
			fscanf(inFile, "%i ", &data);
			set1DCACell(DCA, i, data);
		}
	}
	else if(dimension == 2){
		fscanf(inFile, "%i %i ", &h, &w);
		DCA = create2DCA(w, h, 0); //qstate is initialized as 0 in this implementation. Change this if you want a different qstate.
		DCA->dimension = dimension;
		for(int i = 0; i < h; i++){
			for(int j = 0; j < w; j++){
				int data;
				DCA->wrap = 1;//In this implentation, we will always wrap. Change this value to 0 to use no wrapping
				fscanf(inFile, "%i ", &data);
				set2DCACell(DCA, j, i, data);
			}
		}
	}	
	fclose(inFile);
	displayCA(DCA);
	while(getchar()=='\n'){
		if(dimension == 1){
			printf("Your 1DCA was created, but there is currently no 1DCA implementation for the Game of Life rule.\n");
			return -1;
		}
		else if(dimension == 2){
			step2DCA(DCA, GameOfLife);
		}
		displayCA(DCA);
	}
	
	return 0;
}
