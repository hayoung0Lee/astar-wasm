map_manager.o : map_manager.h map_manager.cpp
	g++ -c map_manager.cpp -std=c++17

astar_pathfinder.o : astar_pathfinder.h astar_pathfinder.cpp
	g++ -c astar_pathfinder.cpp -std=c++17

main.o : main.cpp map_manager.h astar_pathfinder.h
	g++ -c main.cpp -std=c++17

main : map_manager.o astar_pathfinder.o main.o
	g++ map_manager.o astar_pathfinder.o main.o -o main -std=c++17