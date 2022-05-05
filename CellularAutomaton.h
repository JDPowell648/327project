#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H

#include <string>
using namespace std;
class GraphicsClient;
class CellularAutomaton {
   public:
      CellularAutomaton(int w, int h, int qstate);
      CellularAutomaton(const CellularAutomaton& obj);
      CellularAutomaton& operator=(const CellularAutomaton& obj);
      ~CellularAutomaton();
      void step(unsigned char (*rule)(CellularAutomaton*, int, int));
      void display(GraphicsClient* gc);
      void clearDisplay(GraphicsClient* gc);
      unsigned char** getCA();
      int getHeight();
      int getWidth();
      int getInitState();
      int getWrap();
      unsigned char getCell(int x, int y);
      void setCell(int y, int x, unsigned char value);
      void setHeight(int value);
      void setWidth(int value);
      void setEveryCell(int value);
      void interact(int x, int y);
      void loadFromFilePath(string fileName, GraphicsClient* GC);
   private:
      int* initState;
      unsigned char** cadata;
      int* width;
      int* height;
      int* wrap;
};

#endif
