#include <stdio.h>
#include <stdlib.h>
#include "ca.h"
#include <time.h>

void displayCA(ca_data * DCA){
	for(int i = 0; i < DCA->height; i++){
		for(int j = 0; j < DCA->width; j++){
    			printf("%hhu ", DCA->cadata[i][j]);
    		}
    		printf("\n");
	}
}

int set1DCACell(ca_data * DCA, int x, unsigned char state){
	if(x >= 0 && x <= DCA->width- 1){
		DCA->cadata[0][x] = state;
		return 1;
  	}
  	
  	return 0;
}

int set2DCACell(ca_data * DCA, int x, int y, unsigned char state){
	if(x >= 0 && x <= DCA->width - 1 && y >= 0 && y <= DCA->height - 1){

		DCA->cadata[y][x] = state;
		return 1;
  	}
  	
  	return 0;
}

void initCA(ca_data * DCA, int state){
	srandom(time(NULL) );
	for(int i = 0; i < DCA->width; i++){
		if(DCA->dimension == 1){
			set1DCACell(DCA, i, state);
		}else if(DCA->dimension == 2){
			for(int j = 0; j < DCA->height; j++){
	    			set2DCACell(DCA, j, i, state);
	    		}
		}
	}
}

ca_data * create1DCA(int w, unsigned char qstate){
	ca_data * DCA;
	DCA = (ca_data*)malloc(sizeof(ca_data));
	DCA->width = w;
	DCA->height = 1;
	DCA->cadata = (unsigned char **)malloc(sizeof(unsigned char *));
	DCA->cadata[0] = (unsigned char *)malloc(w * sizeof(unsigned char));
	DCA->qstate = qstate;
	
	initCA(DCA, DCA->qstate);
	
	return DCA;
}

ca_data * create2DCA(int w, int h, unsigned char qstate){
	ca_data * DCA;
	DCA = (ca_data*)malloc(sizeof(ca_data));
	DCA->width = w;
	DCA->height = h;
	DCA->cadata = (unsigned char **)malloc(w * sizeof(unsigned char *));
	for(int i = 0; i < w; i++){
		DCA->cadata[i] = (unsigned char *)malloc(h * sizeof(unsigned char));
	}
	DCA->qstate = qstate;
	
	initCA(DCA, DCA->qstate);
	
	return DCA;
}

void step1DCA(ca_data * DCA, unsigned char (*rule)(ca_data *, int x)){
	ca_data * tempDCA = (ca_data*)malloc(sizeof(ca_data));
	tempDCA = create1DCA(DCA->width, DCA->qstate);
	tempDCA->cadata = DCA->cadata;
	
	for(int i = 0; i < DCA->width; i++){
		DCA->cadata[0][i] = rule(tempDCA, i);
	}
	
	free(tempDCA);
}

void step2DCA(ca_data * DCA, unsigned char (*rule)(ca_data *, int x, int y)){
	ca_data * tempDCA = (ca_data*)malloc(sizeof(ca_data));
	tempDCA = create2DCA(DCA->width, DCA->height, DCA->qstate);
	tempDCA->wrap = DCA->wrap;
	for(int i = 0; i < DCA->height; i++){
		for(int j = 0; j < DCA->width; j++){
			tempDCA->cadata[i][j] = DCA->cadata[i][j];
		}
	}
	for(int i = 0; i < DCA->height; i++){
		for(int j = 0; j < DCA->width; j++){
			DCA->cadata[i][j] = rule(tempDCA, j, i);
		}
	}
	free(tempDCA);
}
