#include "GraphicsClient.h"
#include "CellularAutomaton.h"
#include "rule.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	CellularAutomaton CA = CellularAutomaton(10, 10, 0);
	
	GraphicsClient GC = GraphicsClient("192.168.50.22", 7777); //mention ipv4
	GC.setBackgroundColor(255, 220, 192);
	GC.setDrawingColor(99,182,173);
	GC.clear();
	GC.drawRectangle(0,0,600,599);
	GC.drawRectangle(600,0,199,599);
	GC.drawRectangle(600,0,199,599);
	GC.drawButtons();
	
	GC.repaint();
	CA.display(&GC);
	while(GC.getStatus() != -1){
		GC.getClick(&CA);
		if(GC.getStatus() == 1){
			struct timespec timing = {0, 100000000L};
			nanosleep(&timing,NULL);
			CA.step(GameOfLife);
			CA.display(&GC);
		}
	}
	
	return 0;
	
}
