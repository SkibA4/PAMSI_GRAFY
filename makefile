OBJS	= main.o graf.o dijkstra.o
SOURCE	= main.cpp graf.cpp dijkstra.cpp
HEADER	= graf.h dijkstra.h
OUT	= grafy
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

graf.o: graf.cpp
	$(CC) $(FLAGS) graf.cpp 

dijkstra.o: dijkstra.cpp
	$(CC) $(FLAGS) dijkstra.cpp 


clean:
	rm -f $(OBJS) $(OUT)