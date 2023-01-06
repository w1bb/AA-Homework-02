# Copyright (c) 2023 Valentin-Ioan VINTILA.
# All rights reserved.

# Compilation command & flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lm

# Building everything
build: clean trial rise redemption

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
	rm -f *.o trial rise redemption sat.in sat.sol

# ZIP package
pack:
	zip -FSr 323_ValentinIoan-VINTILA.zip *.cpp *.hpp Makefile README.md

# These are not files:
.PHONY: build run_trial run_rise run_redemption clean pack
