all:
	gcc -fPIC -shared calc.c -o libmycalc.so
	g++ app.cc -o app -ldl

clean:
	rm -f *.o *.so app