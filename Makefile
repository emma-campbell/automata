TARGET			:=  auto

CC				:= 	gcc
STD				:= 	-std=c99
DEBUG			:= 	-g
CFLAGS			:= 	$(STD) $(DEBUG) -Wall -Werror -Wextra

SHOW_COMMAND	:=	@printf "%-15s%s\n"
SHOW_CC			:=  $(SHOW_COMMAND) "[ $(CC) ]"
SHOW_CLEAN		:= 	$(SHOW_COMMAND) "[ CLEAN ]"
SHOW_LINK		:=	$(SHOW_COMMAND) "[ LINK ]"


# Build Paths
PATHB			:= 	build/
PATHD			:=	build/depends/
PATHO			:= 	build/objs/
PATHR			:= 	build/results/

# Source Paths
PATHS			:= 	src/
PATHI			:=	include/
PATHT			:=	tests/

# Unity Path -- For Unit Tests
UNITY			:=	lib/Unity/src/

BUILD_PATHS		:= 	$(PATHB) $(PATHD) $(PATHO) $(PATHR)

COMPILE			:= 	$(CC) -c
LINK			:= 	$(CC)
DEPEND 			:=  $(CC) -MM -MG -MF

# Includes public headers from include/ directory
CFLAGS 			+= 	-I$(PATHI)

SRCS 			:= 	$(wildcard $(PATHS)*.c)
OBJS			:=	$(SRCS:$(PATHS)%.c=$(PATHO)%.o)

ifneq ($(V),)
  SILENCE           =
else
  SILENCE           = @
endif

all: $(BUILD_PATHS) $(PATHB)$(TARGET)
	@$(RM) $(TARGET)
	$(SHOW_LINK) "$(PATHB)$(TARGET) -> $(TARGET)"
	$(SILENCE)@ln -s $(PATHB)$(TARGET) $(TARGET)

$(PATHB)$(TARGET): $(OBJS)
	$(SHOW_CC) $@
	$(SILENCE)$(LINK) -o $@ $^

# Compiles the source files
$(PATHO)%.o: $(PATHS)%.c
	$(SHOW_CC) $@
	$(SILENCE)$(COMPILE) $(CFLAGS) $< -o $@

# Compiles the test files
$(PATHO)%.o: $(PATHT)%.c
	$(SHOW_CC) $@
	$(SILENCE)$(COMPILE) $(CFLAGS) $< -o $@

# Compiles unity test framework
$(PATHO)%.o: $(PATHU)%.c $(PATHU)%.h
	$(SHOW_CC) $@
	$(SILENCE)$(COMPILE) $(CFLAGS) $< -o $@

# Generates Dependency Files for the Source src/
$(PATHD)%.d: $(PATHS)%.c
	$(SILENCE) $(DEPEND) $@ $<

# Generates the dependency files to the build/depends directory.
$(PATHD)%.d: $(PATHT)%.c
	$(SILENCE) $(DEPEND) $@ $<

# #############################################################################
# Targets that create neccesary directories
# #############################################################################

$(PATHB): 
	mkdir -p $(PATHB)

$(PATHD):
	mkdir -p $(PATHD)

$(PATHO):
	mkdir -p $(PATHO)

$(PATHR):
	mkdir -p $(PATHR)


# ##############################################################################
# Cleaning things up a lil
# ##############################################################################

.PHONY: clean
clean:
	$(SHOW_CLEAN) $(PATHO)*.o 
	$(SHOW_CLEAN) $(TARGET) 
	$(SHOW_CLEAN) $(PATHB)$(TARGET)
	$(SILENCE)rm -rf $(PATHO)*.o
	$(SILENCE)rm -rf $(TARGET)
	$(SILENCE)rm -rf $(PATHB)$(TARGET)

# ##############################################################################
# Debug Make
#
# This command will print any variable to understand wth is going on
# ##############################################################################
print-% :
	@echo $* = $($*)