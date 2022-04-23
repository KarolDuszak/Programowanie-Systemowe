
outprogname : 44312.ps.lab03.shared.main.c 44312.ps.lab03.shared.lib.so.0.1
	gcc 44312.ps.lab03.shared.main.c -o outprogname -ldl

44312.ps.lab03.shared.lib.so.0.1 : 44312.ps.lab03.shared.lib.o
	gcc -shared -fPIC 44312.ps.lab03.shared.lib.o -o 44312.ps.lab03.shared.lib.so.0.1

44312.ps.lab03.shared.lib.o : 44312.ps.lab03.shared.lib.c
	gcc -c -fPIC 44312.ps.lab03.shared.lib.c
