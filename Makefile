all:
	mkdir build
	cd build
	cmake ..
	make
	cd ..
clean:
	cd build
	make clean
	cd ..
install:
	sudo apt-get install libsfml-dev
