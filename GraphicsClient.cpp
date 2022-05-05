extern "C"
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
#include <sys/ioctl.h>
#include <time.h>
#include <vector>
using namespace std;

GraphicsClient::GraphicsClient(std::string URL, int port){
	sockfd = new int;
	url = new string;
	myPort = new int;
	*sockfd = socket(AF_INET, SOCK_STREAM, 0);
	*url = URL;
	*myPort = port;
	if (sockfd < 0)
	{
		fprintf( stderr, "Error creating socket\n");
		exit(-1);
	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, URL.c_str(), &serv_addr.sin_addr)<=0)
	{
		fprintf(stderr, "Invalid address/ Address not supported \n");
		exit(-1);
	}

	if (connect(*sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
	fprintf(stderr, "Connection Failed \n");
		exit(-1);
	}

}
GraphicsClient::GraphicsClient(const GraphicsClient& obj){
	sockfd = new int;
	myPort = new int;
	url = new string;
	*sockfd = *(obj.sockfd);
	*url = *(obj.url);
	*myPort = *(obj.myPort);
}
GraphicsClient& GraphicsClient::operator=(const GraphicsClient& obj){
	if(this != &obj){
		delete sockfd;
		delete url;
		delete myPort;
		sockfd = new int;
		myPort = new int;
		url = new string;
		*sockfd = *(obj.sockfd);
		*url = *(obj.url);
		*myPort = *(obj.myPort);
      	}
	return *this;
}
GraphicsClient::~GraphicsClient(){
	close(*sockfd);
	delete sockfd;
	delete url;
	delete myPort;
}
void GraphicsClient::setBackgroundColor(int red, int green, int blue){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x07;
	message[5] = 0x02;
	
	message[6] = (red >> 4) & 0x0F;
	message[7] = (red >> 0) & 0x0F;
	
	message[8] = (green >> 4) & 0x0F;
	message[9] = (green >> 0) & 0x0F;
	
	message[10] = (blue >> 4) & 0x0F;
	message[11] = (blue >> 0) & 0x0F;
	send(*sockfd, message, 12, 0);
}
void GraphicsClient::setDrawingColor(int red, int green, int blue){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x07;
	message[5] = 0x06;
	
	message[6] = (red >> 4) & 0x0F;
	message[7] = (red >> 0) & 0x0F;
	
	message[8] = (green >> 4) & 0x0F;
	message[9] = (green >> 0) & 0x0F;
	
	message[10] = (blue >> 4) & 0x0F;
	message[11] = (blue >> 0) & 0x0F;
	send(*sockfd, message, 12, 0);
}
void GraphicsClient::clear(){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x01;
	message[5] = 0x01;
	send(*sockfd, message, 6, 0);
}
void GraphicsClient::setPixel(int x, int y, int red, int green, int blue){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x0F;
	message[5] = 0x03;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;	
	
	message[14] = (red >> 4) & 0x0F;
	message[15] = (red >> 0) & 0x0F;
	
	message[16] = (green >> 4) & 0x0F;
	message[17] = (green >> 0) & 0x0F;
	
	message[18] = (blue >> 4) & 0x0F;
	message[19] = (blue >> 0) & 0x0F;
	send(*sockfd, message, 20, 0);
}
void GraphicsClient::drawRectangle(int x, int y, int w, int h){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x01;
	message[4] = 0x01;
	message[5] = 0x07;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;
	
	message[14] = (w >> 12) & 0x0F;
	message[15] = (w >> 8) & 0x0F;
	message[16] = (w >> 4) & 0x0F;
	message[17] = (w >> 0) & 0x0F;
	
	message[18] = (h >> 12) & 0x0F;
	message[19] = (h >> 8) & 0x0F;
	message[20] = (h >> 4) & 0x0F;
	message[21] = (h >> 0) & 0x0F;
	send(*sockfd, message, 22, 0);
}
void GraphicsClient::fillRectangle(int x, int y, int w, int h){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x01;
	message[4] = 0x01;
	message[5] = 0x08;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;
	
	message[14] = (w >> 12) & 0x0F;
	message[15] = (w >> 8) & 0x0F;
	message[16] = (w >> 4) & 0x0F;
	message[17] = (w >> 0) & 0x0F;
	
	message[18] = (h >> 12) & 0x0F;
	message[19] = (h >> 8) & 0x0F;
	message[20] = (h >> 4) & 0x0F;
	message[21] = (h >> 0) & 0x0F;	
	
	send(*sockfd, message, 22, 0);
}
void GraphicsClient::clearRectangle(int x, int y, int w, int h){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x01;
	message[4] = 0x01;
	message[5] = 0x09;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;
	
	message[14] = (w >> 12) & 0x0F;
	message[15] = (w >> 8) & 0x0F;
	message[16] = (w >> 4) & 0x0F;
	message[17] = (w >> 0) & 0x0F;
	
	message[18] = (h >> 12) & 0x0F;
	message[19] = (h >> 8) & 0x0F;
	message[20] = (h >> 4) & 0x0F;
	message[21] = (h >> 0) & 0x0F;	
	
	send(*sockfd, message, 22, 0);
}
void GraphicsClient::drawOval(int x, int y, int w, int h){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x01;
	message[4] = 0x01;
	message[5] = 0x0A;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;
	
	message[14] = (w >> 12) & 0x0F;
	message[15] = (w >> 8) & 0x0F;
	message[16] = (w >> 4) & 0x0F;
	message[17] = (w >> 0) & 0x0F;
	
	message[18] = (h >> 12) & 0x0F;
	message[19] = (h >> 8) & 0x0F;
	message[20] = (h >> 4) & 0x0F;
	message[21] = (h >> 0) & 0x0F;	
	
	send(*sockfd, message, 22, 0);
}
void GraphicsClient::fillOval(int x, int y, int w, int h){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x01;
	message[4] = 0x01;
	message[5] = 0x0B;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;
	
	message[14] = (w >> 12) & 0x0F;
	message[15] = (w >> 8) & 0x0F;
	message[16] = (w >> 4) & 0x0F;
	message[17] = (w >> 0) & 0x0F;
	
	message[18] = (h >> 12) & 0x0F;
	message[19] = (h >> 8) & 0x0F;
	message[20] = (h >> 4) & 0x0F;
	message[21] = (h >> 0) & 0x0F;	
	
	send(*sockfd, message, 22, 0);
}
void GraphicsClient::drawLine(int x1, int y1, int x2, int y2){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x01;
	message[4] = 0x01;
	message[5] = 0x0D;
	
	message[6] = (x1 >> 12) & 0x0F;
	message[7] = (x1 >> 8) & 0x0F;
	message[8] = (x1 >> 4) & 0x0F;
	message[9] = (x1 >> 0) & 0x0F;
	
	message[10] = (y1 >> 12) & 0x0F;
	message[11] = (y1 >> 8) & 0x0F;
	message[12] = (y1 >> 4) & 0x0F;
	message[13] = (y1 >> 0) & 0x0F;
	
	message[14] = (x2 >> 12) & 0x0F;
	message[15] = (x2 >> 8) & 0x0F;
	message[16] = (x2 >> 4) & 0x0F;
	message[17] = (x2 >> 0) & 0x0F;
	
	message[18] = (y2 >> 12) & 0x0F;
	message[19] = (y2 >> 8) & 0x0F;
	message[20] = (y2 >> 4) & 0x0F;
	message[21] = (y2 >> 0) & 0x0F;	
	
	send(*sockfd, message, 22, 0);
}
void GraphicsClient::drawString(int x, int y, string content){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = ((content.length()*2 + 9) >> 4) & 0x0F;
	message[4] = ((content.length()*2 + 9) >> 0) & 0x0F;
	message[5] = 0x05;
	
	message[6] = (x >> 12) & 0x0F;
	message[7] = (x >> 8) & 0x0F;
	message[8] = (x >> 4) & 0x0F;
	message[9] = (x >> 0) & 0x0F;
	
	message[10] = (y >> 12) & 0x0F;
	message[11] = (y >> 8) & 0x0F;
	message[12] = (y >> 4) & 0x0F;
	message[13] = (y >> 0) & 0x0F;
	
	for(int i = 0; i < (int)content.length()*2; i=i+2){
		message[14+i] = (content[i/2] >> 4) & 0x0F;
		message[15+i] = (content[i/2]) & 0x0F;
	}
	send(*sockfd, message, 100, 0);
}
void GraphicsClient::repaint(){
	char message[100];
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x01;
	message[5] = 0x0C;
	send(*sockfd, message, 6, 0);
}

void GraphicsClient::drawButton(int x, int y, int w, int h, string text){
	this->drawRectangle(x,y,w,h);
	this->drawString(x+5,y+(h/2),text);
}

void GraphicsClient::drawButtons(){
	this->drawButton(650,100,100,50,"STEP");
	this->drawButton(650,150,100,50,"RUN");
	this->drawButton(650,200,100,50,"PAUSE");
	this->drawButton(650,250,100,50,"QUIT");
	this->drawButton(650,300,100,50,"RESET");
	this->drawButton(650,350,100,50,"LOAD");
	this->drawButton(650,400,100,50,"CLEAR");
	this->drawButton(650,450,100,50,"RANDOMIZE");
	this->drawButton(650,550,33,33, "1");
	this->drawButton(683,550,34,33, "2");
	this->drawButton(717,550,33,33, "3");
}

void GraphicsClient::getClick(CellularAutomaton* CA){
	int count; 
	char message[100];
	if(ioctl(*sockfd, FIONREAD, &count) != -1){
		int num = read(*sockfd,message,count);
		if(num != 0 && num != -1){
			int click = int(message[5] & 0x0F);
			if(click == 1){
				int x1 = int(message[7] & 0x0F);
				int x2 = int(message[8] & 0x0F) * 256;
				int x3 = int(message[9] & 0x0F) * 16;
				int x4 = int(message[10] & 0x0F);
				int x = x1 + x2 + x3 + x4;
				int y1 = int(message[11] & 0x0F);
				int y2 = int(message[12] & 0x0F) * 265;
				int y3 = int(message[13] & 0x0F) * 16;
				int y4 = int(message[14] & 0x0F);
				int y = y1 + y2 + y3 + y4;
				
				this->exectueButtonFromClick(x,y,CA);
				this->setCACell(x,y,CA);
			}
		}
	}
}

void GraphicsClient::setCACell(int x, int y, CellularAutomaton* CA){
	CA->interact(x,y);
	CA->clearDisplay(this);
	CA->display(this);
	this->repaint();
}

void GraphicsClient::exectueButtonFromClick(int x, int y,CellularAutomaton* CA){
	if(x > 650 && x < 750 && y > 100 && y < 150){
		this->step(CA);
	}
	if(x > 650 && x < 750 && y > 150 && y < 200){
		this->run(CA);
	}
	if(x > 650 && x < 750 && y > 200 && y < 250){
		this->pause();
	}
	if(x > 650 && x < 750 && y > 250 && y < 300){
		this->quit();
	}
	if(x > 650 && x < 750 && y > 300 && y < 350){
		this->reset(CA);
	}
	if(x > 650 && x < 750 && y > 350 && y < 400){
		this->load(CA);
	}
	if(x > 650 && x < 750 && y > 400 && y < 450){
		this->clearButton(CA);
	}
	if(x > 650 && x < 750 && y > 450 && y < 500){
		this->randomize(CA);
	}
	if(x > 650 && x < 683 && y > 550 && y < 616){
		cout<<"40x40"<<endl;
		CA->clearDisplay(this);
		*CA = CellularAutomaton(40,40,0);
		CA->display(this);
	}
	if(x > 683 && x < 717 && y > 550 && y < 616){
		cout<<"150x150"<<endl;
		CA->clearDisplay(this);
		*CA = CellularAutomaton(150,150,0);
		CA->display(this);
	}
	if(x > 717 && x < 740 && y > 550 && y < 616){
		cout<<"600x600"<<endl;
		CA->clearDisplay(this);
		*CA = CellularAutomaton(600,600,0);
		CA->display(this);
	}
}

void GraphicsClient::step(CellularAutomaton* CA){
	CA->step(GameOfLife);
	CA->display(this);
	this->repaint();
}

void GraphicsClient::run(CellularAutomaton* CA){
	this->status = 1;
	cout<<"run"<<endl;
}

void GraphicsClient::pause(){
	cout<<"pause"<<endl;
	this->status = 0;
}

void GraphicsClient::quit(){
	this->status = -1;
}

void GraphicsClient::reset(CellularAutomaton* CA){
	cout<<"reset"<<endl;
	CA->loadFromFilePath(savedFilePath, this);
}

void GraphicsClient::load(CellularAutomaton* CA){
	cout<<"load"<<endl;
	int count;
	char message[100];
	string filepath = "";
	message[0] = 0xFF;
	message[1] = 0x00;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x01;
	message[5] = 0x0E;
	send(*sockfd, message, 6, 0);
	
	char answer[100];
	ioctl(*sockfd, FIONREAD, &count);
	read(*sockfd,answer,count);
	while(count == 0 || (answer[5] & 0x0F) != 10){
		ioctl(*sockfd, FIONREAD, &count);
		read(*sockfd,answer,count);
	}
	
	int x1 = int(answer[1] & 0x0F) * 4096;
	int x2 = int(answer[2] & 0x0F) * 256;
	int x3 = int(answer[3] & 0x0F) * 16;
	int x4 = int(answer[4] & 0x0F);
	int len = x1 + x2 + x3 + x4 - 1;
	savedFilePath = "";
	if((answer[5] & 0x0F) == 10){
		for(int i = 0; i < len; i=i+2){
			int char1 = (answer[i+6] & 0x0F) * 16;
			int char2 = (answer[i+7] & 0x0F);
			char character = char1 + char2;
			savedFilePath.push_back(character);
		}
		cout<<savedFilePath<<endl;
	}
	std::vector<std::string> out;
	size_t start;
    	size_t end = 0;
	while ((start = savedFilePath.find_first_not_of('\\', end)) != std::string::npos)
	{
		end = savedFilePath.find('\\', start);
		out.push_back(savedFilePath.substr(start, end - start));
	}
	savedFilePath =	out.back();
	CA->loadFromFilePath(savedFilePath, this);
}

void GraphicsClient::clearButton(CellularAutomaton* CA){
	cout<<"clear"<<endl;
	CA->clearDisplay(this);
	CA->setEveryCell(0);
	CA->display(this);
}

void GraphicsClient::randomize(CellularAutomaton* CA){
	cout<<"randomize"<<endl;
	CA->clearDisplay(this);
	CA->setEveryCell(-1);
	CA->display(this);
}

int GraphicsClient::getStatus(){
	return status;
}
