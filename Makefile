# Project
PROJECT := cvec
CC := clang
CFLAGS = -Wall -Wextra -Werror -Wunused-result -Wconversion
CPPFLAGS = -Iinclude
LDFLAGS = -L/usr/local/lib -lcerror -lcarena

# Dirs
BUILD_DIR := build
SRC_DIR := src
OBJ_DIR := $(BUILD_DIR)/obj
INC_DIR	:= include
TEST_DIR := test
EXAMPLE_DIR := example
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include
DOC_DIR := doc

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC_PRIV := $(wildcard $(SRC_DIR)/*.h)
INC := $(INC_DIR)/$(PROJECT).h
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_MAIN := $(TEST_DIR)/test.c
TEST_EXE := $(BUILD_DIR)/test
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so
EXAMPLE_MAIN := $(EXAMPLE_DIR)/example.c
EXAMPLE_EXE := $(BUILD_DIR)/example

# Rules
.PHONY: all test debug example clean install uninstall doc tags

all: CC := gcc
all: CFLAGS += -O3 -march=native -flto
all: CPPFLAGS += -DNDEBUG
all: $(LIB_A) $(LIB_SO)

debug: $(LIB_A) $(LIB_SO)

test: CPPFLAGS += -DTEST
test: LDFLAGS += -lctest
test: $(TEST_EXE)
	./$<

example: LDFLAGS += -lcvec
example: $(EXAMPLE_EXE)
	./$<

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR) compile_commands.json tags

install:
	cp $(LIB_A) $(LIB_INSTALL_DIR)
	cp $(LIB_SO) $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

uninstall:
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_A)))
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_SO)))
	rm $(addprefix $(INC_INSTALL_DIR)/, $(notdir $(INC)))

doc:
	doxygen

tags:
	ctags -R --c-kinds=+p /usr/local/include /usr/include .

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXE): $(TEST_MAIN) $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(INC_PRIV) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(EXAMPLE_EXE): $(EXAMPLE_MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
