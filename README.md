# coms327P2PB
This project is Part B of Project 2 in ComS327.

The features impletemented is the implementation of a 2DCA CellularAutomaton structure, that allows for a user to define several parameters and run a simulation on the DCA with a dynamic rule. The result is displayed on a Graphics Server connected to by a GraphicsClient.

The rule currently implemented is Game of Life, which can be explained as:

Any live cell with two or three live neighbours survives.

Any dead cell with three live neighbours becomes a live cell.

All other live cells die in the next generation. Similarly, all other dead cells stay dead.

Read more at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

In the top level directory, you can make, and then run the executable created with ./go1 dimension filepath

The first two objects in the file should be the width and height, followed by the next w*h items in the CA.
A sample input file could be "CA.txt":

7 10

0 0 0 0 0 0 0 0 0 0

0 1 0 1 0 0 0 0 0 0

0 0 1 1 0 0 0 0 0 0

0 0 1 0 0 0 0 0 0 0

0 0 0 0 0 0 0 0 0 0

0 0 0 0 0 0 0 0 0 0

0 0 0 0 0 0 0 0 0 0

where the DCA is 7x10, and a "glider" is made.

After making, running a simulation on this CA can be done with ./go1

This will connect to the server and display the simulation. Several buttons will be dispalyed on the GraphicsServer, allowing for user interaction with the CA on the screen. To start, an empty 5x5 CA is displayed. Users may load CAs from files as shown above, and can create different sizes of CAs, inlcuding 40x40, 150x150, and 600x600. Entering any other character will exit the simulation and detach the socketed connection.

Currently, wrap value and qstate are hard coded. Wrap set to 0 results in no wrapping, whereas wrap set to 1 will wrap. Qstate is currently set to 0, but it can be anything. Note that qstate is only applied in the nowrap scenario.

There are no issues that I am presently aware of in this code. It may be good to note the hard-coded address in main is an ipv4 address, because I am running the server on a windows command line and the client is running from a linux VM. You may have to change the ip in GraphicsClient in main to whatever works for your machine. This may be your own ipv4 or 127.0.0.1.

Following this, loading a CA from a text file must be in the same directory as the executable.
