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
MODULES_DIR = ./modules
TESTS_DIR = ./tests
REPORT_DIR = ./report
INCLUDE_DIR = ./include
DEBUG_DIR = ./debug
DOCS_DIR = ../docs

# TARGET NAMES ===============================================================#
TARGET = test
LIB = $(PROJECT_NAME).a
GCOV = gcov_report

# LIST OF FILES AND DIRECTORIES IN MODULES ===================================#
MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
MODULES_CC = $(shell find $(MODULES_DIR) -type f -name "*.cc")
MODULES_H = $(shell find $(INCLUDE_DIR) -type f -name "*.h")
MODULES_O = $(notdir $(MODULES_CC:%.cc=%.o))
MODULES_OBJ_PATH = $(addprefix $(OBJ_DIR)/modules/, $(MODULES_O))

# LIST OF FILES AND DIRECTORIES IN TESTS =====================================#
TESTS_DIRS = $(shell find $(TESTS_DIR) -type d)
TESTS_CC = $(shell find $(TESTS_DIR) -type f -name "*.cc")
TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")
TESTS_O = $(notdir $(TESTS_CC:%.cc=%.o))
TESTS_OBJ_PATH = $(addprefix $(OBJ_DIR)/tests/, $(TESTS_O))

# LIST OF FILES TO CLANG-FORMAT AND CPPCHECK =================================#
CC_FILES = $(MODULES_CC) $(TESTS_CC)
H_FILES = $(MODULES_H) $(TESTS_H)

# LIST OF DIRECTORIES THAT MAKE SHOULD SEARCH
vpath %.cc $(MODULES_DIRS) $(TESTS_DIRS)
vpath %.o $(OBJ_DIR)

# TARGETS ====================================================================#
.PHONY: all
all: $(GCOV)

.PHONY: $(LIB)
$(LIB): $(OBJ_DIR) $(MODULES_O) $(MODULES_H)
	ar rcs $@ $(MODULES_OBJ_PATH)
	ranlib $@

.PHONY: $(TARGET)
$(TARGET): $(LIB) $(OBJ_DIR) $(TESTS_O)
	$(CXX) $(TESTS_OBJ_PATH) $(LIB) $(LDFLAGS) -o $@
	./$@

.PHONE: $(GCOV)
$(GCOV): $(OBJ_DIR) $(REPORT_DIR) $(TESTS_O)
	$(CXX) $(TESTS_OBJ_PATH) $(MODULES_CC) $(LDFLAGS) $(GCOV_FLAGS) -o $(addprefix $(OBJ_DIR)/, $(TARGET))
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

%.o: %.cc $(MODULES_H) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(addprefix $(OBJ_DIR)/modules/, $@) $<

# CHECKS =====================================================================#
clang_fix:
	clang-format -style=Google -i $(CC_FILES) $(H_FILES)

clang_check:
	clang-format -style=Google -n $(CC_FILES) $(H_FILES)

cpplint:
	cpplint $(MODULES_CC) $(MODULES_H)

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
	rm -f $(LIB)
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -f $(VALGRIND_REPORT)
	rm -rf $(DOCS_DIR)

.PHONY: preferences
preferences:
	sudo apt install libgtest-dev

# CREATE DIRECTORIES =========================================================#
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tests/
	mkdir -p $(OBJ_DIR)/modules/

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

$(DOCS_DIR):
	mkdir -p $(DOCS_DIR)

1:
	@echo $(MODULES_DIR)
	@echo
	@echo $(MODULES_CC)
	@echo
	@echo $(MODULES_H)
	@echo
	@echo $(MODULES_O)
	@echo
	@echo $(MODULES_OBJ_PATH)

2:
	@echo $(TESTS_DIR)
	@echo
	@echo $(TESTS_CC)
	@echo
	@echo $(TESTS_H)
	@echo
	@echo $(TESTS_O)
	@echo
	@echo $(TESTS_OBJ_PATH)
