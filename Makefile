CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = mon_programme
SRCS = main.cpp fichier1.cpp fichier2.cpp
OBJS = $(SRCS:.cpp=.o)
INC_DIRS = -I.

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) -o $(TARGET) $(OBJS)

main.o: main.cpp fichier1.hpp fichier2.h
	$(CC) $(CFLAGS) $(INC_DIRS) -c main.cpp

fichier1.o: fichier1.cpp fichier1.hpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c fichier1.cpp

fichier2.o: fichier2.cpp fichier2.h
	$(CC) $(CFLAGS) $(INC_DIRS) -c fichier2.cpp

clean:
	rm -f $(TARGET) $(OBJS)
