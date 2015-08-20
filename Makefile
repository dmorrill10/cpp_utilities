.PHONY: default
default: all

# Build options
#==============

# Compile options
#----------------

ADD_SYMBOLS =-g
DEBUG_SYMBOLS =$(ADD_SYMBOLS) -O1

TO_OBJ = -c
TO_FILE = -o

# Enable print log
PRINT_LOG = -DDEBUG

# Enable profiling code
PROFILE = -DPROFILE

# Preprocess out asserts
NO_ASSERTS = -DNDEBUG

OPT =-O3 -ffast-math -ftree-vectorize

DISABLED_WARNINGS =-Wno-vla-extension -Wno-unused-function -Wno-unknown-pragmas
WARNINGS =-Wall -Wextra -Wredundant-decls -Wfatal-errors -Wshadow

### C
CC =gcc -std=gnu99
CFLAGS = -fPIC -march=native

### C++
CPPFLAGS := $(CFLAGS)
#CLANG_OPTIONS = -fsanitize=memory -fno-optimize-sibling-calls -fno-omit-frame-pointer -fsanitize-memory-track-origins=1
CLANG_OPTIONS =-fcolor-diagnostics
CPP =clang++ -std=c++11 $(CLANG_OPTIONS)


# Linking options
#----------------
LDLIBS = -lm -lutil


# Structure
#====================

# More precise but typically not necessary and more verbose
# THIS_DIR := $(abspath $(CURDIR)/$(dir $(lastword $(MAKEFILE_LIST))))
THIS_DIR := .

VENDOR_DIR := $(THIS_DIR)/vendor
$(VENDOR_DIR):
	-mkdir $(VENDOR_DIR)

# Vendor definitions
#-------------------

VENDOR_INCLUDES := -I$(VENDOR_DIR)

# Project
#--------
INCLUDES =$(VENDOR_INCLUDES)

### Directories
SRC_DIR := $(THIS_DIR)/src
TOOL_DIR := $(SRC_DIR)/tools


### Source files
C_SRC = $(shell find $(SRC_DIR) -type f -name '*.c' 2>/dev/null)
C_HEADERS =$(shell find $(SRC_DIR) -type f -name '*.h' 2>/dev/null)
CPP_SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp' 2>/dev/null)
CPP_HEADERS =$(shell find $(SRC_DIR) -type f -name '*.hpp' 2>/dev/null)

### Intermediate files
C_OBJ :=$(C_SRC:%.c=%.c.o)
CPP_OBJ :=$(CPP_SRC:%.cpp=%.cpp.o)

MAIN_OBJ :=$(filter %-main.cpp.o,$(CPP_OBJ))

C_LIB_OBJ :=$(filter-out %-main.c.o,$(C_OBJ))
CPP_LIB_OBJ :=$(filter-out %-main.cpp.o,$(CPP_OBJ))


### Executables
TO_TARGET=$(patsubst %-main.cpp.o,%-tool,$(notdir $1))
TARGETS  =$(call TO_TARGET,$(MAIN_OBJ))


SRC_INCLUDES :=-I$(SRC_DIR)
INCLUDES +=$(SRC_INCLUDES)


# Build rules
#============

# Base rules
#-----------

%.c.o: %.c | $(C_HEADERS)
	@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	@echo [CC] $@
	$(CC) -c $(CFLAGS) $(TO_FILE) $@ $^ $(INCLUDES)

%.cpp.o: %.cpp $(C_LIB_OBJ) | $(UTILITIES_DIR) $(C_HEADERS) $(CPP_HEADERS)
	@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	@echo [CPP] $@
	$(CPP) -c $(CPPFLAGS) $(TO_FILE) $@ $^ $(INCLUDES)

%-tool: $(CPP_LIB_OBJ) $(C_LIB_OBJ) $(TOOL_DIR)/%-main.cpp.o | $(C_HEADERS) $(CPP_HEADERS)
	@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	@echo [LD] $@
	$(CPP) $(CPPFLAGS) $(TO_FILE) $@ $^ $(LDLIBS)
	@chmod 755 $@


# Utilities
#==========

run-%: %
	./$*

# Clean
#-------
.PHONY: clean
clean: cleantest
	-rm -f $(C_OBJ) $(CPP_OBJ) $(THIS_DIR)/test/bin/* core.* $(TARGETS)

.PHONY: cleandep
cleandep:
	-rm $(DEP)


# Debugging
#----------
print-%:
	@echo $* = $($*)


# Testing
#===========

# Definitions
#------------
CATCH_DIR :=$(VENDOR_DIR)/Catch
TEST_DIR :=$(THIS_DIR)/test
TEST_SUPPORT_DIR :=$(TEST_DIR)/support
TEST_SRC_EXTENSION =.cpp
TEST_EXTENSION =.out
TEST_PREFIX =test_
TEST_SUBDIRS :=$(filter-out $(TEST_SUPPORT_DIR) $(TEST_DIR)/data,$(wildcard $(TEST_DIR)/*))
TESTS        :=$(shell find $(TEST_SUBDIRS) -type f -name '$(TEST_PREFIX)*$(TEST_SRC_EXTENSION)' 2>/dev/null)
TEST_OBJ :=$(TESTS:%$(TEST_SRC_EXTENSION)=%$(TEST_SRC_EXTENSION).o)
TEST_EXES :=$(TESTS:%$(TEST_SRC_EXTENSION)=%$(TEST_EXTENSION))
TEST_SUPPORT_SRC :=$(TEST_SUPPORT_DIR)/test_helper$(TEST_SRC_EXTENSION)
TEST_SUPPORT_OBJ :=$(TEST_SUPPORT_DIR)/test_helper$(TEST_SRC_EXTENSION).o


# Rules
#------
$(TEST_SUPPORT_DIR):
	@echo [mkdir] $@
	@mkdir -p $@

$(TEST_SUPPORT_SRC): | $(TEST_SUPPORT_DIR)
	@echo [touch] $@
	@touch $@

%$(TEST_EXTENSION): OPT =-O0
%$(TEST_EXTENSION): CFLAGS +=$(OPT) $(WARNINGS) $(DISABLED_WARNINGS)
%$(TEST_EXTENSION): CPPFLAGS +=$(OPT) $(WARNINGS) $(DISABLED_WARNINGS)
%$(TEST_EXTENSION): INCLUDES +=-I$(CATCH_DIR) -I$(TEST_SUPPORT_DIR)
%$(TEST_EXTENSION): $(TEST_SUPPORT_OBJ) %$(TEST_SRC_EXTENSION).o $(CPP_LIB_OBJ) $(C_LIB_OBJ) | %$(TEST_SRC_EXTENSION) $(C_HEADERS) $(CPP_HEADERS)
	@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	@echo [LD] $@
	$(CPP) $(CPPFLAGS) $(TO_FILE) $@ $^ $(INCLUDES) $(LDLIBS)
	@chmod 755 $@

.PHONY: compiletest
compiletest: $(TEST_EXES)

.PHONY: test
test: $(TEST_EXES)
	@for test in $^; do echo ; echo [TEST] $$test; \
		echo "===============================================================\n";\
		$$test | grep -v -P '^\s*\#'; done

.PHONY: cleantest
cleantest:
	-rm -f $(TEST_SUPPORT_OBJ) $(TEST_OBJ) $(TEST_EXES)

test-%: $(TEST_DIR)/$(TEST_PREFIX)%$(TEST_EXTENSION)
	./$(TEST_DIR)/$(TEST_PREFIX)$*$(TEST_EXTENSION)
