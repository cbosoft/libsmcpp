CXX ?= g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2

HDR = src/smc.hpp src/data.hpp src/util.hpp src/exception.hpp src/colour.hpp src/formatter.hpp src/smc_kext.hpp
OBJ = obj/smc.o obj/data.o obj/util.o obj/list.o
LINK = -lpthread
FRMWK = -framework IOKit
DEFS =

## Colours
COL_OBJ = $(shell tput setaf 3 2>/dev/null)
COL_EXE = $(shell tput setaf 4 2>/dev/null)
COL_SOO = $(shell tput setaf 5 2>/dev/null)
COL_RST = $(shell tput sgr0 2>/dev/null)
COL_BLD = $(shell tput bold 2>/dev/null)

## install dir
PREFIX = /usr/local

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


.PHONY: all options

all: libsmcpp.so options

install:
	mkdir -p $(PREFIX)/lib
	cp libsmcpp.so $(PREFIX)/lib/.
	mkdir -p $(PREFIX)/include/smcpp
	cp $(HDR) $(PREFIX)/include/smcpp/.

libsmcpp.so: $(OBJ) $(HDR)
	@printf "$(COL_SOO)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) -shared $(FRMWK) $(DEFS) $(CLIENT) $(OBJ) -o libsmcpp.so $(LINK)

smctool: obj/main.o libsmcpp.so $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(FRMWK) $(DEFS) $(CLIENT) libsmcpp.so obj/main.o -o $@ $(LINK)

tests: $(OBJ) obj/tests.o $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(FRMWK) $(DEFS) $(CLIENT) $(OBJ) obj/tests.o -o $@ $(LINK)

options:
	@printf "Compiler: $(COL_BLD)$(CXX)$(COL_RST)\n"

clean:
	rm -rf obj smctool *.so
