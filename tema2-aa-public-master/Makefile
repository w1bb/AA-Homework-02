CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

build: trial

trial: trial.cpp SAT.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

run_trial:
	./trial

# Object files
SAT.o: SAT.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f *.o trial
