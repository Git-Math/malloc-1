#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/29 13:16:03 by mcanal            #+#    #+#              #
#    Updated: 2018/04/28 00:50:23 by mc               ###   ########.fr        #
#                                                                              #
#******************************************************************************#

##
## CUSTOM CONFIG
##

# name of the lib to make
TARGET = libft_malloc.so

# file-names of the sources
SRC_NAME = malloc.c free.c realloc.c show_alloc_mem.c calloc.c reallocarray.c \
			find_free_block.c find_block_by_addr.c sort_list.c \
			debug/debug.c debug/print_bytes.c debug/hex_dump.c debug/get_env.c \
			util/ft_memcpy.c util/ft_bzero.c util/ft_strlen.c util/ft_memcmp.c \
			util/ft_putnbr_fd.c util/ft_putstr_fd.c util/ft_isprint.c

# folder-names of the sources
SRC_PATH = src

# folder-names containing headers files
INC_PATH = inc

# where are your tests?
TEST_DIR = test

# extra libraries needed for linking
ifeq ($(shell uname), Linux)
LDLIBS = -pthread
else
LDLIBS =
endif

# linking flags
LDFLAGS = -shared

# compilation flags
CPPFLAGS = -fPIC


##
## GLOBAL VARIABLES
##

# compilation/linking flags for the differents public rules
WFLAGS = -Wextra -Wall  # warnings
RCFLAGS = $(WFLAGS) -Werror -O2  # release
DCFLAGS = $(WFLAGS) -g -DDEBUG  # debug
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5  # sanitize
WWFLAGS = $(WFLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
  -Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
  -Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
  -Wredundant-decls  # moar warnings

# folder used to store all compilations sub-products (.o and .d mostly)
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
DEP = $(OBJ:.o=.d)

# includes
INC = $(addprefix -I, $(INC_PATH))

# specify flags for commands used in the following rules
LN =		ln -s
RM =		rm -f
RMDIR =		rmdir
MKDIR =		mkdir -p
CC =		clang
MAKE ?=		make -j$(shell nproc 2>/dev/null || echo 4)
SUB_MAKE =	make -C

# the real name of the lib
ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
PROJECT = $(TARGET:.so=_$(HOSTTYPE).so)

# default to "pretty" Makefile, but you can run ´VERBOSE=t make´
# ifndef VERBOSE
#  ifndef TRAVIS
# .SILENT:
#  endif
# endif
# PRINTF = test $(VERBOSE)$(TRAVIS) || printf

# some colors for pretty printing
WHITE =		\033[37m
RED =		\033[31m
GREEN =		\033[32m
YELLOW =	\033[33m
BLUE =		\033[34m
BASIC =		\033[0m


##
## PUBLIC RULES
##

# release build
all:
	+$(MAKE) $(PROJECT) "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

# masochist build
mecry:
	+$(MAKE) $(PROJECT) "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

# build for gdb/valgrind debugging
dev:
	+$(MAKE) $(PROJECT:.so=.dev.so) \
		"PROJECT = $(PROJECT:.so=.dev.so)" "TARGET = $(TARGET:.so=.dev.so)" \
		"CFLAGS = $(DCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/dev"

# build for runtime debugging (fsanitize)
san:
	+$(MAKE) $(PROJECT:.so=.san.so) \
		"PROJECT = $(PROJECT:.so=.san.so)" "TARGET = $(TARGET:.so=.san.so)" \
		"CFLAGS = $(SCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/san"

# remove all generated .o and .d
clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	$(RM) $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -name '*.[od]' | xargs $(RM) || true

# remove the generated binary, and all .o and .d
fclean: clean
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs $(RMDIR) || true
	$(RM) $(PROJECT) $(PROJECT:.so=.san.so) $(PROJECT:.so=.dev.so)
	$(RM) $(TARGET) $(TARGET:.so=.san.so) $(TARGET:.so=.dev.so)
	$(RM) test.{san,dev}.sh test[0-8] test3_bis ctrl[0-8] ctrl3_bis
	$(RM) -r *.dSYM

# some people like it real clean
mrproper:
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(TEST_DIR)
	+$(MAKE) fclean

# clean build and recompile
re: fclean
	+$(MAKE) all

# run tests on project
test: all
	./test.sh

# run tests on project (debug mode)
testdev: dev
	cp test.sh test.dev.sh
	sed -i 's/ft_malloc/ft_malloc.dev/g' test.dev.sh
	sed -i 's/extra/extra -g/g' test.dev.sh
	./test.dev.sh

# run tests on project (sanitize mode)
testsan: san
	cp test.sh test.san.sh
	sed -i 's/ft_malloc/ft_malloc.san/g' test.san.sh
	sed -i 's/extra/extra -g -fsanitize=address,undefined/g' test.san.sh
	./test.san.sh


##
## PRIVATE RULES
##

# create binary (link)
$(PROJECT): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@
	test -L $(TARGET) || $(LN) $(PROJECT) $(TARGET)

# create object files (compile)
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

# create directory for compilation sub-products
$(OBJ_PATH):
	$(MKDIR) $(dir $(OBJ))

# read dependencies list generated by -MMD flag
-include $(DEP)

# just to avoid conflicts between rules and files/folders names
.PHONY: all, dev, san, mecry, $(PROJECT), clean, fclean, mrproper, re, test, testdev, testsan
