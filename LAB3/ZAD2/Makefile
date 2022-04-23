
outprogname : 44312.ps.lab03.static.lib.o 44312.ps.lab03.shared.main.o
	gcc -o outprogname 44312.ps.lab03.static.lib.o 44312.ps.lab03.shared.main.o

44312.ps.lab03.static.lib.o : 44312.ps.lab03.static.lib.c 44312.ps.lab03.static.lib.h
	gcc -c 44312.ps.lab03.static.lib.c

44312.ps.lab03.shared.main.o : 44312.ps.lab03.shared.main.c 44312.ps.lab03.static.lib.h
	gcc -c 44312.ps.lab03.shared.main.c
