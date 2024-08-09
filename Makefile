CC = g++
QT = qmake
CFLAGS = -Werror -Wall -Wextra -std=c++17 -fPIC
GT_FLAGS = -lgtest -lgtest_main -pthread
S21_MAC = ~/Users/bocal/
MODEL_SRC := $(wildcard ./SmartCalc/model/*.cpp)
MODEL_SRC := $(filter-out ./SmartCalc/model/model_graph.cpp, $(MODEL_SRC))
MODEL_DIR = ./SmartCalc/model
TEST_DIR = ./SmartCalc/tests
VIEW_DIR = ./SmartCalc/view
CONTROLLER_DIR = ./SmartCalc/controller
COMMON_DIR = ./SmartCalc/common
MODEL_LIB_NAME = libmodel.a
CONTROLLER_LIB_NAME = libcontroller.a
TEST_BIN_NAME = test_executable
OS = $(shell uname)
SCHOOL_CHECK=$(shell test -d /Users/bocal/ || echo 'FALSE')
GT_INCPATH = 
GT_LIBS =

PRGRM_NAME=smartcl

.PHONY: all, install, test, clean

all: clean gcov_report open_report

gcov_flag_ON:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_flag_OFF:
	$(eval CFLAGS -= -fprofile-arcs -ftest-coverage)

school21_check:
ifneq ($(SCHOOL_CHECK), FALSE)
	$(eval GT_INCPATH += -I/opt/goinfre/$(USER)/homebrew/include)
	$(eval GT_LIBS += -L/opt/goinfre/$(USER)/homebrew/lib)
endif

check_leak: test
	clang-format -style="{BasedOnStyle: Google}" -i $(MODEL_SRC) $(CONTROLLER_DIR)/*.cpp $(VIEW_DIR)/*.cpp $(MODEL_DIR)/*.h $(CONTROLLER_DIR)/*.h $(COMMON_DIR)/*.h $(VIEW_DIR)/*.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(MODEL_DIR)/*.h $(CONTROLLER_DIR)/*.h $(COMMON_DIR)/*.h $(VIEW_DIR)/*.h
ifeq ($(OS), Darwin)
	leaks --atExit -- ./test_executable
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test_executable
endif
model_lib:
	$(CC) $(CFLAGS) -c $(MODEL_SRC) -I./SmartCalc/model/ -I$(COMMON_DIR)
	ar rcs $(MODEL_LIB_NAME) *.o
	rm -f *.o
lint:
	clang-format -i $(CONTROLLER_DIR)/*.cpp $(MODEL_DIR)/*.cpp $(TEST_DIR)/*.cpp $(VIEW_DIR)/*.cpp
	clang-format -i $(CONTROLLER_DIR)/*.h $(MODEL_DIR)/*.h $(VIEW_DIR)/*.h
install:
	@echo 'Installing SmartCalc...'
	@mkdir -p ./SmartCalc/build
	@cd ./SmartCalc && qmake && make && cp -r $(PRGRM_NAME).app ./build/ && make clean && rm -rf Makefile && rm -rf *.app
launch:
	@./SmartCalc/build/$(PRGRM_NAME).app/Contents/MacOS/$(PRGRM_NAME)
uninstall:
	@echo 'Uninstalling SmartCalc...'
	@rm -rf ./SmartCalc/build
test: model_lib school21_check
	$(CC) $(CFLAGS) $(TEST_DIR)/*.cpp -L. -lmodel $(GT_INCPATH) $(GT_LIBS) $(GT_FLAGS) -o $(TEST_BIN_NAME)
	./$(TEST_BIN_NAME)
gcov_report: clean gcov_flag_ON test gcov_flag_OFF
	@echo 'Generating a coverage report...'
	@mkdir report
	@gcovr -r . --exclude=tests --exclude=model/bank --html --html-details -s -o report/report.html
	@rm -f *.gcda *.gcno
open_report:
ifeq ($(OS), Darwin)
	open report/report.html
else
	xdg-open report/report.html
endif
dvi:
ifeq ($(OS), Darwin)
	open ./SmartCalc/about/readme.html
else
	xdg-open ./SmartCalc/about/readme.html
endif

dist:
	@echo 'Creating an archive...'
	@mkdir -p ./dist
	@tar -czvf ./dist/$(PRGRM_NAME)-1.0.tar.gz ./SmartCalc/* 2> /dev/null && echo "Sources saves to path \"./dist/$(PRGRM_NAME)-1.0.tar.gz\""

clean:
	rm -f *.a ./SmartCalc/*.o ./SmartCalc/*.a  $(TEST_BIN_NAME) ./SmartCalc/*.gcda ./SmartCalc/*.gcno ./SmartCalc/*.gcov coverage.info
	rm -rf ./report ./dist ./SmartCalc/build
