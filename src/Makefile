PROJECT_NAME = s21_containers

# COMPILER ===================================================================#
CXX = g++
# add -Werror
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g
LDFLAGS = -lgtest

# ADDITIONAL FLAGS ===========================================================#
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --tool=memcheck --leak-check=yes
VALGRIND_REPORT = val.txt

# DIRECTORIES ================================================================#
OBJ_DIR = ./obj
TESTS_DIR = ./tests
REPORT_DIR = ./report
CONTAINERS_DIR = ./containers
DOCS_DIR = ../docs

# TARGET NAMES ===============================================================#
TARGET = test
GCOV = gcov_report

# LIST OF FILES IN CONTAINERS ================================================#
CONTAINERS_H = $(shell find $(SRC_INCLUDE_LIST_H_) -type f -name "*.h")

# LIST OF FILES AND DIRECTORIES IN TESTS =====================================#
TESTS_DIRS = $(shell find $(TESTS_DIR) -type d)
TESTS_CC = $(shell find $(TESTS_DIR) -type f -name "*.cc")
TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")
TESTS_O = $(notdir $(TESTS_CC:%.cc=%.o))
TESTS_OBJ_PATH = $(addprefix $(OBJ_DIR)/tests/, $(TESTS_O))

# LIST OF FILES TO CLANG-FORMAT AND CPPCHECK =================================#
CC_FILES = $(TESTS_CC)
H_FILES = $(CONTAINERS_H) $(TESTS_H)

# LIST OF DIRECTORIES THAT MAKE SHOULD SEARCH
vpath %.cc $(TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# TARGETS ====================================================================#
.PHONY: all
all: $(GCOV)

.PHONY: $(TARGET)
$(TARGET): $(CONTAINERS_H) $(OBJ_DIR) $(TESTS_O)
	$(CXX) $(TESTS_OBJ_PATH) $(LDFLAGS) -o $@
	./$@

.PHONE: $(GCOV)
$(GCOV): $(OBJ_DIR) $(REPORT_DIR) $(TESTS_O)
	$(CXX) $(TESTS_OBJ_PATH) $(LDFLAGS) $(GCOV_FLAGS) -o $(addprefix $(OBJ_DIR)/, $(TARGET))
	-./$(addprefix $(OBJ_DIR)/, $(TARGET))
	gcovr -r . --html --html-details -o $(REPORT_DIR)/coverage.html
	xdg-open $(REPORT_DIR)/coverage.html

.PHONY: dvi
dvi:
	rm -rf $(DOCS_DIR)
	doxygen Doxyfile

.PHONY: dvi_open
dvi_open:
	xdg-open $(DOCS_DIR)/html/index.html

%_test.o: %_test.cc $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(addprefix $(OBJ_DIR)/tests/, $@) $<

# CHECKS =====================================================================#
clang_fix:
	clang-format -style=Google -i $(CC_FILES) $(H_FILES)

clang_check:
	clang-format -style=Google -n $(CC_FILES) $(H_FILES)

cpplint:
	cpplint $(CC_FILES) $(H_FILES)

check:
	make clang_fix
	make cpplint

valgrind: $(TARGET)
	@printf '\033[1;33m\n\t\t\t\t                   _            _           _   _            _   _             \n'
	@printf '\t\t\t\t                  | |          (_)         | | | |          | | (_)            \n'
	@printf '\t\t\t\t       __   ____ _| | __ _ _ __ _ _ __   __| | | |_ ___  ___| |_ _ _ __   __ _ \n'
	@printf '\t\t\t\t       \ \ / / _` | |/ _` | '\''__| | '\''_ \ / _` | | __/ _ \/ __| __| | '\''_ \ / _` |\n'
	@printf '\t\t\t\t        \ V / (_| | | (_| | |  | | | | | (_| | | ||  __/\__ \ |_| | | | | (_| |\n'
	@printf '\t\t\t\t         \_/ \__,_|_|\__, |_|  |_|_| |_|\__,_|  \__\___||___/\__|_|_| |_|\__, |\n'
	@printf '\t\t\t\t                      __/ |                                               __/ |\n'
	@printf '\t\t\t\t                     |___/                                               |___/ \n\033[0m\n'

	@$@ $(VALGRIND_FLAGS) ./$(TARGET) > $(VALGRIND_REPORT) 2>&1 && \
	{ \
		printf "\033[1;33m\n"; \
		printf "###########################################################################################################################################################\n\n"; \
		printf "                                                                 Valgrind test results:\n"; \
		printf "                                                                Passed tests $$(grep "ERROR SUMMARY: 0" -c val.txt) from $$(grep "ERROR SUMMARY:" -c val.txt)\n\n"; \
		printf "###########################################################################################################################################################\n"; \
		printf "\033[0m\n"; \
	}

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f $(VALGRIND_REPORT)
	rm -rf $(DOCS_DIR)

.PHONY: dependencies
dependencies:
	sudo apt install libgtest-dev -y
	sudo apt install python3-pip
	pip install cpplint

# CREATE DIRECTORIES =========================================================#
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tests/

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

$(DOCS_DIR):
	mkdir -p $(DOCS_DIR)
