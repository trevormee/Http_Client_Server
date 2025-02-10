CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

OBJS = httpServer.o 

proj1 : ${OBJS}
		${CXX} $(CXXFLAGS) -o $@ ${OBJS}

 
httpServer.o : httpServer.cpp

clean :
		rm ${OBJS}

.PHONY: all clean