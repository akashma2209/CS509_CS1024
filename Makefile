all:
	g++ -std=c++17 wrapper/wrapper.cpp -o wrapper/wrapper.exe
	wrapper/wrapper.exe