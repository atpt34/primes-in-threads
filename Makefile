CC=g++

SRC=Interval.cpp Xml_Loader.cpp Primes_Calculator.cpp
MAIN_SRC=$(SRC) main.cpp
MAIN_FLAGS=-g -std=c++11 -Wall -pthread

TEST_SRC=$(SRC) AllinTest.cpp
TEST_FLAGS=-isystem $(GOOGLETEST_DIR)/include $(GOOGLETEST_DIR)/libgtest.a -Wall -pthread
GOOGLETEST_DIR=/home/atpt34/Documents/googletest/googletest

main:
	$(CC) $(MAIN_SRC) $(MAIN_FLAGS) -o main
test:
	$(CC) $(TEST_SRC) $(TEST_FLAGS) -o tests
clean:
	rm main tests
all: main test
