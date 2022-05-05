#include <iostream>
#include "GraphicsClient.h"
#include "CellularAutomaton.h"
#include "rule.h"
#include <filesystem>
using namespace std;
CellularAutomaton::CellularAutomaton(int w, int h, int qstate){
	initState = new int;
	width = new int;
      	height = new int;
      	wrap = new int;
      	cadata = new unsigned char*[h];
	for(int i = 0; i < h; i++){
	    cadata[i] = new unsigned char[w];
	}
	*wrap = 1;
      	*initState = qstate;
      	*width = w;
      	*height = h;
	
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			cadata[i][j] = qstate;
		}
	}
}
CellularAutomaton::CellularAutomaton(const CellularAutomaton& obj){
	initState = new int;
	cadata = new unsigned char*[*(obj.height)];
	for(int i = 0; i < *(obj.height); i++){
	    cadata[i] = new unsigned char[*(obj.width)];
	}
      	width = new int;
      	height = new int;
      	wrap = new int;
      	
   	*initState = *(obj.initState);
      	*width = *(obj.width);
      	*height = *(obj.height);
	for(int i = 0; i < *(obj.height); i++){
		for(int j = 0; j < *(obj.width); j++){
	    		cadata[i][j] = (obj.cadata)[i][j];
	    	}
	}
}
CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& obj){
	if(this != &obj){
		delete initState;
      		for(int i = 0; i < *height; i++){
		    delete []  cadata[i];
		}
		delete [] cadata;
      		delete width;
      		delete height;
      		delete wrap;
      		
      		initState = new int;
      		width = new int;
      		height = new int;
      		wrap = new int;
      		*initState = *(obj.initState);
      		*width = *(obj.width);
      		*height = *(obj.height);
      		
      		cadata = new unsigned char*[*(obj.height)];
		for(int i = 0; i < *(obj.height); i++){
		    cadata[i] = new unsigned char[*(obj.width)];
		}
		
		for(int i = 0; i < *(obj.height); i++){
			for(int j = 0; j < *(obj.width); j++){
		    		cadata[i][j] = (obj.cadata)[i][j];
		    	}
		}
		
      	}
	return *this;
}
CellularAutomaton::~CellularAutomaton(){
	delete initState;
	for(int i = 0; i < *height; i++){
	    delete [] cadata[i];
	}
	delete [] cadata;
      	delete width;
      	delete height;
      	delete wrap;
}
void CellularAutomaton::step(unsigned char (*rule)(CellularAutomaton*, int, int)){
	CellularAutomaton tempCA = CellularAutomaton(*this);
	for(int i = 0; i < *height; i++){ 
		for(int j = 0; j < *width; j++){ 
			cadata[i][j] = rule(&tempCA, j, i); //j = x, i = y 
		}
	}
}

void CellularAutomaton::display(GraphicsClient* gc){
	int maxSize;
	if(*width > *height){
		maxSize = *width;
	}else{
		maxSize = *height;
	}
	int offset = 0;
	int size = 1;
	if(200 < maxSize && maxSize <= 600){
		offset = 0;
		size = 1;
	}else if(100 < maxSize && maxSize <= 200){
		offset = 1;
		size = 2;
	}else if(50 < maxSize && maxSize <= 100){
		offset = 1;
		size = 4;
	}else if(1 < maxSize && maxSize <= 50){
		offset = 2;
		size = 10;
	}
	
	this->clearDisplay(gc);
	for(int i = 0; i < *height; i++){
		int y1 = (i*size)+(offset*i);
		
		for(int j = 0; j < *width; j++){
			int x1 = (j*size)+(offset*j);
			if(cadata[i][j] != 0){
				gc->fillRectangle(x1,y1,size,size);
			}
		}
	}
	gc->repaint();
}

void CellularAutomaton::clearDisplay(GraphicsClient* gc){
	int maxSize;
	if(*width > *height){
		maxSize = *width;
	}else{;
		maxSize = *height;
	}
	int offset = 0;
	int size = 1;
	if(200 < maxSize && maxSize <= 600){
		offset = 0;
		size = 1;
	}else if(100 < maxSize && maxSize <= 200){
		offset = 1;
		size = 2;
	}else if(50 < maxSize && maxSize <= 100){
		offset = 1;
		size = 4;
	}else if(1 < maxSize && maxSize <= 50){
		offset = 2;
		size = 10;
	}
	for(int i = 0; i < *height; i++){
		int y1 = (i*size)+(offset*i);
		
		for(int j = 0; j < *width; j++){
			int x1 = (j*size)+(offset*j);	
			gc->clearRectangle(x1,y1,size,size);
		}
	}
	gc->repaint();
}

unsigned char** CellularAutomaton::getCA(){
	return cadata;
}
int CellularAutomaton::getHeight(){
	return *height;
}
int CellularAutomaton::getWidth(){
	return *width;
}
void CellularAutomaton::setHeight(int value){
	*height = value;
}
void CellularAutomaton::setWidth(int value){
	*width = value;
}
unsigned char CellularAutomaton::getCell(int y, int x){
	return cadata[y][x];
}
void CellularAutomaton::setCell(int y, int x, unsigned char value){
	cadata[y][x] = value;
}
int CellularAutomaton::getInitState(){
	return *initState;
}
int CellularAutomaton::getWrap(){
	return *wrap;
}

void CellularAutomaton::setEveryCell(int value){
	for(int i = 0; i < *height; i++){
		for(int j = 0; j < *width; j++){
			if(value == -1){
				cadata[i][j] = rand() & 1;
			}else{
				cadata[i][j] = value;
			}
		}
	}
}

void CellularAutomaton::interact(int x, int y){
	int maxSize;
	if(*width > *height){
		maxSize = *width;
	}else{
		maxSize = *height;
	}
	int offset = 0;
	int size = 1;
	if(200 < maxSize && maxSize <= 600){
		offset = 0;
		size = 1;
	}else if(100 < maxSize && maxSize <= 200){
		offset = 1;
		size = 2;
	}else if(50 < maxSize && maxSize <= 100){
		offset = 1;
		size = 4;
	}else if(1 < maxSize && maxSize <= 50){
		offset = 2;
		size = 10;
	}
	int posx = x/(size + offset);
	int posy = y/(size + offset);
	
	if(posx >= *width || posy >= *height){
		return;
	}
	
	if((int)this->getCell(posy,posx) == 1){
		this->setCell(posy,posx,0);
	}
	else if((int)this->getCell(posy,posx) == 0){
		this->setCell(posy,posx,1);
	}
}

void CellularAutomaton::loadFromFilePath(string fileName, GraphicsClient* GC){
	FILE* inFile = NULL;
	const char *fName = fileName.c_str();
	if(fopen(fName,"r") == NULL){
		return;
	}
	inFile = fopen(fName,"r");
	this->clearDisplay(GC);
	int w, h;
	int qstate = 0;
	fscanf(inFile, "%i %i ", &h, &w);
	initState = new int;
	width = new int;
	height = new int;
	wrap = new int;
	cadata = new unsigned char*[h];
	for(int i = 0; i < h; i++){
		cadata[i] = new unsigned char[w];
	}
	*wrap = 1;
	*initState = qstate;
	*width = w;
	*height = h;

	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
		    int data;
		    fscanf(inFile, "%i ", &data);
		    cadata[i][j] = data;
		}
	}
	this->display(GC);
}
