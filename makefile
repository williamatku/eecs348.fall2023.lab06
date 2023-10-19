matrix:
	g++ -o prog ./matrix.cpp
	./prog matrix_input.txt

clean:
	[ ! -e ./prog ] || rm ./prog