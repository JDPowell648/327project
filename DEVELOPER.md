The primary structure used in this project is a CellularAutomaton class, which includes an array of unsigned character pointers representing a 2DCA, and several integers to store the initial value, height, width, wrapping status, and qstate.
Index the 2d array with DCA->cadata[y][x]

Source files include:

ca.c, ca.h, main.c:

Legacy Code

CellularAutomaton.cpp, CellularAutomaton.h:

step(unsigned char (*rule)(CellularAutomaton*, int, int)):

Takes a user-defined rule which accepts a reference to the current CA object and parameters X and Y for the location of the current cell. The function creates a temporary CellularAutomaton according to the rule selected. This function executes one step of the given rule.

display(GraphicsClient* gc):

Draws the current CellularAutomaton onto the Graphics Server. Cell sizes are outlined as follows:

m Cell size in pixels Cell gap in pixels, Let m be the maximum value of the width and height of the 2DCA.

200 < m <= 600 1 0 

100 < m <= 200 2 1 

50 < m <= 100 4 1 

1 < m <= 50 10 2 

clearDisplay(GraphicsClient* gc):

Clears every rectangle drawn by the respective CA.

setEveryCell(int value):

Sets every cell in the CA to the value given. A value of -1 will randomize the values of each cell.

interact(int x, int y):

Toggles a cell based on a click from the graphics serve

loadFromFilePath(string fileName, GraphicsClient* GC):

loads a new CA from a given filepath. The template of the file is explained in README.md.

getCA(), getHeight(), getWidth(),getInitState(), getWrap(), getCell(int x, int y):

Accessor functions


setCell(int y, int x, unsigned char value), setHeight(int value), setWidth(int value):

Mutator Functions


GraphicsClient.cpp, GraphicsClient.h:

Includes the methods:

setBackgroundColor(int red, int green, int blue);

setDrawingColor(int red, int green, int blue);

clear();

setPixel(int x, int y, int red, int green, int blue);

drawRectangle(int x, int y, int w, int h);

fillRectangle(int x, int y, int w, int h);

clearRectangle(int x, int y, int w, int h);

drawOval(int x, int y, int w, int h);

fillOval(int x, int y, int w, int h);

drawLine(int x1, int y1, int x2, int y2);

drawString(int x, int y, string content);

repaint();

Which interface with the graphics server to send messages. The object is constructed with an address and port to connect to, and will send messages based on what methods are called. The methods are fairly self explainitory. After drawing new objects to the server, it is necessary to call repaint() to push the changes.

drawButton(int x, int y, int w, int h, string text):

draws a button at a respective location of size w,h with the given text.

drawButtons():

draws the default configuration of buttons of the GraphicsServer.

setCACell(int x, int y, CellularAutomaton* CA):

recieves a click from the server, and sends it to the CA to toggle a cell

getClick(CellularAutomaton* CA):

gets the location of a click

step(CellularAutomaton* CA):

runs one step of the simulation

run(CellularAutomaton* CA):

continously runs the simulation. Sets GC status to 1, meaning running

pause():

pauses the simulation. Sets GC status to 0, meaning pause

quit():

quits the connection. Sets GC status to -1, meaning quit

reset(CellularAutomaton* CA):

resets the CA back to a previously loaded file

load(CellularAutomaton* CA):

loads a CA from file. The template of the file is explained in README.md.

clearButton(CellularAutomaton* CA):

clears the entire CA, sets every value back to 0.

randomize(CellularAutomaton* CA):

randomizes the entire CA.

exectueButtonFromClick(int x, int y, CellularAutomaton* CA):

parses the click location and executes the button that was clicked.

getStatus():

returns the status of the GC.
0 means pause
1 means running
-1 means quit

rule.cpp, rule.h:
The Game of Life Rule, which is defined simply as:

Any live cell with two or three live neighbours survives.

Any dead cell with three live neighbours becomes a live cell.

All other live cells die in the next generation. Similarly, all other dead cells stay dead.

Read more at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

main.cpp:

Main runs the program, building a CellularAutomaton from the file given. The first two objects in the file should be the width and height, followed by the next w*h items in the CA. A sample input file could be: 4 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 where the DCA is 4x5 and all values are 0. Pressing the enter or return key will execute one step of Game of Life on the DCA given.

Makefile:

Build a binary executable "go1." Can be ran with ./go1 <filename>
