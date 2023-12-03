CC = g++
PROJECT = Thread
SRC = Paralelo_thread.cpp

LIBS = `pkg-config opencv4 --cflags --libs`

all: $(PROJECT)

$(PROJECT): $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)
