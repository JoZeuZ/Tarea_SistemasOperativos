CC = g++
PROJECT = Secuencial_Final
SRC = Secuencial.cpp

LIBS = `pkg-config opencv4 --cflags --libs`

all: $(PROJECT)

$(PROJECT): $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)
