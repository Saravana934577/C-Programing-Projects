# add.exe:main.o file.o contact.o
# 	gcc -o add.exe main.o file.o contact.o
# main.o:main.c
# 	gcc -c main.c
# file.o:file.c
# 	gcc -c file.c
# contact.o:contact.c
# 	gcc -c contact.c
# clean:
# 	rm *.exe *.o
OBJ:=$(patsubst %c,%.o,$(wildcard *.c))
add.exe:$(OBJ)
	gcc -o $@ $^
clean:
	rm *.exe *.o	

