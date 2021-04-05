CC = g++
FLAGS = -c

TARGETS = oss user scheduler sharedmemory errors childhandler filehandler clock

all: $(TARGETS)

oss: oss.o
	$(CC) $(FLAGS) -o $@ oss.o

user: user.o
	$(CC) $(FLAGS) -o $@ user.o

scheduler.o: scheduler.cpp scheduler.h
	$(CC) $(FLAGS) scheduler.cpp

sharedmemory.o: sharedmemory.cpp sharedmemory.h
	$(CC) $(FLAGS) sharedmemory.cpp

errors.o: errors.cpp errors.h
	$(CC) $(FLAGS) errors.cpp

childhandler.o: childhandler.cpp childhandler.h
	$(CC) $(CFLAGS) childhandler.cpp

filehandler.o: filehandler.cpp filehandler.h
	$(CC) $(FLAGS) filehandler.cpp

clock.o: clock.cpp clock.h
	$(CC) $(CFLAGS) clock.cpp

clean:
	rm -rf *.o $(TARGETS)
