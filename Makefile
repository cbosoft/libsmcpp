CXX ?= g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -O2

HDR = src/smc.hpp src/data.hpp src/util.hpp
OBJ = obj/smc.o obj/data.o obj/util.o
LINK = -lpthread
FRMWK = -framework IOKit
DEFS =

## Colours
COL_OBJ = $(shell tput setaf 3 2>/dev/null)
COL_EXE = $(shell tput setaf 4 2>/dev/null)
COL_RST = $(shell tput sgr0 2>/dev/null)
COL_BLD = $(shell tput bold 2>/dev/null)

.SECONDARY:

obj/%.o: src/%.cpp $(HDR)
	@printf "$(COL_OBJ)ASSEMBLING OBJECT $@$(COL_RST)\n"
	@mkdir -p `dirname $@`
	@$(CXX) $(CFLAGS) $(DEFS) $< -c -o $@


.PHONY: all options

smctool: $(CLIENT) $(OBJ) obj/main.o $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(FRMWK) $(DEFS) $(CLIENT) $(OBJ) obj/main.o -o $@ $(LINK)

tests: $(CLIENT) $(OBJ) obj/tests.o $(HDR)
	@printf "$(COL_OBJ)LINKING OBJECTS TO EXECUTABLE $@$(COL_RST)\n"
	@$(CXX) $(CFLAGS) $(FRMWK) $(DEFS) $(CLIENT) $(OBJ) obj/tests.o -o $@ $(LINK)

options:
	@printf "Compiler: $(COL_BLD)$(CXX)$(COL_RST)\n"

prof_pdf:
	gprof aite gmon.out > analysis.txt
	gprof2dot -o d.dot analysis.txt
	dot -Tpdf d.dot > prof.pdf


clean:
	rm -rf obj smctool
