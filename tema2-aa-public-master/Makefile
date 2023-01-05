CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

build: trial rise

# Running actions
run_trial:
	./trial

run_rise:
	./rise

# Building the main files
trial: trial.cpp SAT.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

rise: rise.cpp SAT.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Object files
SAT.o: SAT.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f *.o trial
