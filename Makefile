all:
	g++ main.cpp src/rasterization.cpp src/engine.cpp src/mathUtils.cpp src/model3d.cpp src/model2d.cpp src/3to2d.cpp src/STL_utils.cpp -lSDL2 -o engine.out -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Werror

