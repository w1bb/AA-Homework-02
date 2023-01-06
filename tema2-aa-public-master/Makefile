# Copyright (c) 2023 Valentin-Ioan VINTILA.
# All rights reserved.

CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

# Building everything
build: trial rise redemption

# Running actions
run_trial:
	./trial

run_rise:
	./rise

run_redemption:
	./redemption

# Building the main files
trial: trial.cpp SAT.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

rise: rise.cpp SAT.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

redemption: redemption.cpp SAT.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Object files
SAT.o: SAT.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f *.o trial
