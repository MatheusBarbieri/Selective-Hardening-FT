CC = g++
FLAGS = -g -Wall -pthread -std=c++14
CFLAGS = $(FLAGS) $(INCLUDE)

UTILS = instance.o \
		simulatedannealing.o \
		solution.o \

CODE = salbp1-sa.o

.PHONY: all clean

all: salbp1-sa clean

salbp1-sa: $(UTILS) $(CODE)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean: removeObjects

removeObjects:
	rm -f $(UTILS) $(CODE)

run:
	./salbp1-sa -c 54 -s 1530488776 -v < ../WEE-MAG.IN2

generate_gold:
	./salbp1-sa -c 54 -s 1530488776 -v < ../WEE-MAG.IN2
	mv outputs.txt gold_outputs.txt
