


.PHONY: all config  build clean
all:
	rm -rvf build
	cmake -S ./ -B ./build
	cmake --build ./build

config:
	cmake -S ./ -B ./build

build:
	cmake --build ./build 

clean: 
	rm -rvf build
