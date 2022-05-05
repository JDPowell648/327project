#ifndef GRAPHICS_CLIENT_H
#define GRAPHICS_CLIENT_H

#include <string>
using namespace std;

class CellularAutomaton;
class GraphicsClient {
   public:
      GraphicsClient(std::string URL, int port);
      GraphicsClient(const GraphicsClient& obj);
      ~GraphicsClient();
      GraphicsClient& operator=(const GraphicsClient& obj);
      void setBackgroundColor(int red, int green, int blue);
      void setDrawingColor(int red, int green, int blue);
      void clear();
      void setPixel(int x, int y, int red, int green, int blue);
      void drawRectangle(int x, int y, int w, int h);
      void fillRectangle(int x, int y, int w, int h);
      void clearRectangle(int x, int y, int w, int h);
      void drawOval(int x, int y, int w, int h);
      void fillOval(int x, int y, int w, int h);
      void drawLine(int x1, int y1, int x2, int y2);
      void drawString(int x, int y, string content);
      void repaint();
      void drawButton(int x, int y, int w, int h, string text);
      void drawButtons();
      void setCACell(int x, int y, CellularAutomaton* CA);
      void getClick(CellularAutomaton* CA);
      void step(CellularAutomaton* CA);
      void run(CellularAutomaton* CA);
      void pause();
      void quit();
      void reset(CellularAutomaton* CA);
      void load(CellularAutomaton* CA);
      void clearButton(CellularAutomaton* CA);
      void randomize(CellularAutomaton* CA);
      void exectueButtonFromClick(int x, int y, CellularAutomaton* CA);
      int getStatus();
   private:
      string* url;
      int* sockfd;
      int* myPort;
      int status = 0;
      string savedFilePath;
};
#endif
