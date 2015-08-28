############################ MakeFile #############################
#All 
all: 
	gcc -c aritmetica.c main.c
	gcc -o teste aritmetica.o main.o 
	gcc -o teste aritmetica.c main.c 

#Main	
main:
	gcc -o teste aritmetica.c main.c
#Clean	
clean: 
	rm -rf *.o