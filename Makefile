CC = g++ 
COPTFLAGS = -O3 -g

all: insert_test search_test edit_distance

insert_test: insert_test.o HashTable.o
	$(CC) $(COPTFLAGS) -o $@ $^

search_test: search_test.o HashTable.o
	$(CC) $(COPTFLAGS) -o $@ $^

edit_distance: edit_distance.o
	$(CC) $(COPTFLAGS) -o $@ $^

clean:
	rm -f core *.o *~ insert_test search_test edit_distance

