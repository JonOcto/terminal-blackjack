CC = g++
STD = -std=c++11
FLAG = -w
DFLAG = -Wall -gdwarf -g3
OBJ = main.cpp functions.cpp
OUT = app

all :
	$(CC) $(OBJ) $(STD) $(FLAG) -o $(OUT)
debug :
	$(CC) $(OBJ) $(STD) $(DFLAG) -o $(OUT)
windows:
	$(CC) $(OBJ) $(STD) $(FLAG) -o app.exe
