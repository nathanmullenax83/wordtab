all: wordtab

wordtab: *.cpp *.tpp
	g++ -std=c++1z main.cpp -owordtab
