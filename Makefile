all: game

main := main.cpp

game: ./bin/$(main)
	g++ -std=c++17 \
	./bin/$(main) \
	./bin/bar.cpp \
	-I./deps/include \
	-lraylib \
	-o game

.PHONY: clean
clean:
	rm -f game
