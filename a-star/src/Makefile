astar_pathfinder.o : astar_pathfinder.h astar_pathfinder.cpp
	emcc -c astar_pathfinder.cpp -std=c++17

map_manager.o : map_manager.h map_manager.cpp
	emcc -c map_manager.cpp -std=c++17

main.o : main.cpp map_manager.h astar_pathfinder.h
	emcc -c main.cpp -std=c++17

main : map_manager.o astar_pathfinder.o main.o
	emcc --bind map_manager.o astar_pathfinder.o main.o -o main.js -std=c++17 -sLLD_REPORT_UNDEFINED