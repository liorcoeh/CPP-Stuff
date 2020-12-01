 
TEST = thread_pool_test

C_FILES:= $(shell find ./src -name *.cpp)
INCLUDES:= -I ./include 
DEPS = ./include/*.hpp
LIB_PATH = /home/liorcoeh/git/lior-cohen/cpp/sourceCR/lib

CC = g++
CFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g 				# For Debbuging
LDFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -DNDEBUG -O3 	# Not Debbug

# Link the test binary to shared objects
test:	libproject.so $(DEPS) ./test/$(TEST).cpp
	@$(CC) -L./lib -Wl,-rpath=$(LIB_PATH) $(INCLUDES) $(LDFLAGS) ./$@/$(TEST).cpp -o $(TEST) -lm  -lproject -ldl -lboost_system -lboost_chrono -lboost_thread
	@mv $(TEST) ./$@/bin
	@./$@/bin/$(TEST) 

debug:	./test/$(TEST).cpp libproject.so $(DEPS)
		@$(CC) -L./lib -Wl,-rpath=$(LIB_PATH) $(INCLUDES) $(CFLAGS) ./test/$(TEST).cpp -o main -libproject -lm -ldl
		@mv main ./test/debbuging 

libproject.so: $(C_FILES) $(DEPS) 
	@$(CC) $(INCLUDES) $(CFLAGS) $(C_FILES) -fPIC -shared -o $@
	@mv $@ ./lib

run:
	./test/bin/$(TEST)
		
gt: ./test/bin/main
	clear
	@gdbtui ./test/bin/main
	
vlg: ./test/bin/main
	@valgrind ./test/bin/main

.PHONY: clean

clean:
	 @rm -f -R *.o *.so *_test
