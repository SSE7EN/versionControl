# TARGET = prog
# LIBS = -lm
# CC = gcc
# CFLAGS = -g -Wall

# SRC_DIR     = ./src
# BUILD_DIR   = ./build
# BIN_DIR     = ./bin
# HEADERS_DIR = ./headers

# SRC_LIST = $(wildcard $(SRC_DIR)/*.c)
# OBJ_LIST = $(BUILD_DIR)/$(notdir $(SRC_LIST:.c=.o))
# HEADER_LIST = $(wildcard $(HEADERS_DIR)/*.h)

# .PHONY: default all clean

# default: $(TARGET)
# all: default

# $(OBJ_LIST): $(SRC_LIST) $(HEADER_LIST)
# 	$(CC) $(CFLAGS) -c $(SRC_LIST)

# .PRECIOUS: $(TARGET) $(OBJECTS)

# $(TARGET): $(OBJ_LIST) $(SRC_LIST)
# 	$(CC) $(OBJ_LIST) $(SRC_LIST) -Wall $(LIBS) -o $@
# clean:
# 	-rm -f *.o
# 	-rm -f $(TARGET)


# CC          = gcc
# LD          = gcc
# CFLAG       = -Wall
# PROG_NAME   = prog

# SRC_DIR     = ./src
# BUILD_DIR   = ./build
# BIN_DIR     = ./bin
# SRC_LIST = $(wildcard $(SRC_DIR)/*.c)
# OBJ_LIST = $(BUILD_DIR)/$(notdir $(SRC_LIST:.c=.o))

# .PHONY: all clean $(PROG_NAME) compile

# all: $(PROG_NAME)



# $(OBJ_LIST): $(SRC_LIST)
# 	$(CC) -c $< -o $@

# compile: 
# 	$(CC) -c $(CFLAG) $(SRC_LIST) -o $(OBJ_LIST)

# $(PROG_NAME): compile
# 	$(LD) $(OBJ_LIST) -o $(BIN_DIR)/$@

# clean:
# 	rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o


# tool marcros
CC := gcc
CCFLAG := -Wall -g -lm
DBGFLAG := -g -Wall -lm
CCOBJFLAG := $(CCFLAG) -c -lm

# path marcros
BIN_PATH := bin
OBJ_PATH := build
SRC_PATH := src
DBG_PATH := debug
HEADERS_DIR = ./headers

# compile marcros
TARGET_NAME := vc.out
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .out,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
MAIN_SRC := src/main.c

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
HEADER_LIST = $(wildcard $(HEADERS_DIR)/*.h)

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST)

# default rule
default: all

# non-phony targets
$(TARGET): $(OBJ) 
	$(CC) $(CCFLAG) -o $@ $? -lm $(HEADER_LIST)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCOBJFLAG) -o $@ $< 

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c* $(HEADERS_DIR)/%.h*
	$(CC) $(CCOBJFLAG) $(DBGFLAG) -o $@ $< 

$(TARGET_DEBUG): $(OBJ_DEBUG) $(HEADER_LIST)
	$(CC) $(CCFLAG) $(DBGFLAG) $? -o $@ 

# phony rules
.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)