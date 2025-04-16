### Compile command #########################################
###  for FreeBSD of Linux with gcc
CC= gcc
CFLAGS= -Wall -O2
LIBS= -lm 

SOURCES= main.c setup.c files.c rollup.c
OBJECTS= main.o setup.o files.o rollup.o

TARGET= mktb

.c.o	:$(SOURCES)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@ 

$(TARGET)	:$(OBJECTS)
	$(CC) $(CFLAGS) $(RUN_OPTIONS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean	:
	rm -f $(TARGET) $(OBJECTS) core a.out *~ "#"* 


