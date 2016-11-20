all:
	g++ *.cpp -o example  `sdl2-config --static-libs` -lz -lbz2 -lpng -lfreetype  -lFayEngine -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lSDL2_net -L/usr/local/lib -I/usr/local/include -I/usr/local/include/SDL2 -std=c++14

