CC ?= gcc

COBJS ?= client.o bmp.o couleur.o json.o validateur.o
SOBJS ?= serveur.o json.o validateur.o
TOBJS ?= test.o bmp.o couleur.o json.o validateur.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client
TEST = test

all: $(SERVER) $(CLIENT) $(TEST)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS)

$(TEST): $(TOBJS)
	$(CC) -o $(TEST) $(TOBJS)

.c.o:
	$(CC) -c $*.c
	
clean :
	-rm -f *.o $(SERVER) $(CLIENT)
	
tests :
	-make
	-./test
	
