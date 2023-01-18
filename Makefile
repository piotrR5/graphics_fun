all:
	g++ main.cpp src/rasterization.cpp src/engine.cpp src/mathUtils.cpp src/model3d.cpp src/model2d.cpp src/3to2d.cpp -lSDL2 -o engine.out 

