
outprogname : 44312.ps.lab02.second.lib.o 44312.ps.lab02.second.main.o
	gcc -o outprogname 44312.ps.lab02.second.lib.o 44312.ps.lab02.second.main.o

44312.ps.lab02.second.lib.o : 44312.ps.lab02.second.lib.c 44312.ps.lab02.second.lib.h
	gcc -c 44312.ps.lab02.second.lib.c

44312.ps.lab02.second.main.o : 44312.ps.lab02.second.main.c 44312.ps.lab02.second.lib.h
	gcc -c 44312.ps.lab02.second.main.c
