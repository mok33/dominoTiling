app.exe: main.o dominoTiling.o lib\liblodepng.a
		g++ main.o dominoTiling.o lib\liblodepng.a -o app.exe
main.o: main.cpp dominoTiling.hpp
		g++ -c -std=c++11 main.cpp
dominoTiling.o: dominoTiling.cpp dominoTiling.hpp
		g++ -c dominoTiling.cpp
 
