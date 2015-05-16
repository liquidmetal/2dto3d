all:
	g++ src/* -lGLEW -lglut -lGL -lSOIL -lglui -I/usr/local/include -L/usr/local/lib -I./include -Wno-write-strings -Wno-return-local-addr -std=gnu++11 -L/usr/lib64
