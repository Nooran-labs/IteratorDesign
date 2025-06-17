
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

SRC = MyContainer.hpp       AscendingOrderIterator.hpp       DescendingOrderIterator.hpp       SideCrossOrderIterator.hpp       ReverseOrderIterator.hpp       OrderIterator.hpp       MiddleOutOrderIterator.hpp

DEMO_SRC = Demo.cpp
MAIN_SRC = Main.cpp
TEST_SRC = tests.cpp

demo: $(DEMO_SRC) $(SRC)
	$(CXX) $(CXXFLAGS) -o demo $(DEMO_SRC)

main: $(MAIN_SRC) $(SRC)
	$(CXX) $(CXXFLAGS) -o main $(MAIN_SRC)

test: $(TEST_SRC) $(SRC)
	$(CXX) $(CXXFLAGS) -o test $(TEST_SRC)

valgrind: main test
	$(VALGRIND) ./main
	$(VALGRIND) ./test

clean:
	rm -f demo main test
