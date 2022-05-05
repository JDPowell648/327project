#include <stdio.h>
#ifndef ca_h
#define ca_h

typedef struct ca_data_struct {
	unsigned char ** cadata;
	unsigned int dimension;
	unsigned int wrap;
	unsigned char qstate;
	int width;
	int height;
} ca_data;

void displayCA(ca_data * DCA);

int set1DCACell(ca_data * DCA, int x, unsigned char state);

int set2DCACell(ca_data * DCA, int x, int y, unsigned char state);

void initCA(ca_data * DCA, int state);

ca_data * create1DCA(int x, unsigned char qstate);

ca_data * create2DCA(int w, int h, unsigned char qstate);

void step1DCA(ca_data * DCA, unsigned char (*rule)(ca_data *, int x));

void step2DCA(ca_data * DCA, unsigned char (*rule)(ca_data *, int x, int y));

#endif
