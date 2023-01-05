CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

build: trial

trial: trial.cpp mediator.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

run_trial:
	./trial

# Object files
mediator.o: mediator.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f *.o trial
