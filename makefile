go1 : casimulator.o GraphicsClient.o CellularAutomaton.o rule.o
	g++ casimulator.o GraphicsClient.o CellularAutomaton.o rule.o -o go1

casimulator.o : casimulator.cpp GraphicsClient.h CellularAutomaton.h rule.h
	g++ -Wall -c casimulator.cpp -lstdc++

GraphicsClient.o : GraphicsClient.cpp GraphicsClient.h
	g++ -Wall -c GraphicsClient.cpp -lstdc++
	
CellularAutomaton.o : CellularAutomaton.cpp CellularAutomaton.h
	g++ -Wall -c CellularAutomaton.cpp -lstdc++

rule.o : rule.cpp rule.h
	g++ -Wall -c rule.cpp -lstdc++

clean :
	rm *.o go1
