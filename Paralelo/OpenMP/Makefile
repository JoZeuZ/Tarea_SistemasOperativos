CC = g++
PROJECT = OpenMP
SRC = Paralelo_openmp.cpp

LIBS = `pkg-config opencv4 --cflags --libs` -fopenmp

all: $(PROJECT)

$(PROJECT): $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)
