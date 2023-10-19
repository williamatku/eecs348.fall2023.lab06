matrix:
	g++ -o prog ./matrix.cpp
	./prog input.txt

clean:
	[ ! -e ./prog ] || rm ./prog