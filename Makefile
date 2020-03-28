# O~~       O~~      O~       O~~   O~~  O~~~~~~~~O~~~~~~~~O~~O~~      O~~~~~~~~
# O~ O~~   O~~~     O~ ~~     O~~  O~~   O~~      O~~      O~~O~~      O~~      
# O~~ O~~ O O~~    O~  O~~    O~~ O~~    O~~      O~~      O~~O~~      O~~      
# O~~  O~~  O~~   O~~   O~~   O~ O~      O~~~~~~  O~~~~~~  O~~O~~      O~~~~~~  
# O~~   O~  O~~  O~~~~~~ O~~  O~~  O~~   O~~      O~~      O~~O~~      O~~      
# O~~       O~~ O~~       O~~ O~~   O~~  O~~      O~~      O~~O~~      O~~      
# O~~       O~~O~~         O~~O~~     O~~O~~~~~~~~O~~      O~~O~~~~~~~~O~~~~~~~~

TARGET  	?=	auto
CC 	    	?=	gcc
LINKER  	?= 	gcc

OBJ_DIR 	:= 	build
BIN_DIR 	:= 	bin
SRC_DIR 	:= 	src
INC_DIR 	:= 	include

SRCEXT  	:= 	c
OBJEXT  	:=	o
INCEXT  	:=	h

SRCS 		:=	$(shell find $(SRC_DIR) -type f -name '*.$(SRCEXT)')
OBJS		:=	$(SRCS:$(SRC_DIR)/%.$(SRCEXT)=$(OBJ_DIR)/%.o)

INC_FLAGS   := -I $(INC_DIR)
STD    	    := -std=c99
DEBUG 	    := -g
CFLAGS 		+= $(STD) $(INC_FLAGS) $(DEBUG) -Wall -Wextra -Werror
LFLAGS 		+=

# Obtains the OS type, either 'Darwin' (OS X) or 'Linux'
UNAME_S:=$(shell uname -s)

# Macros for timing compilation
ifeq ($(UNAME_S),Darwin)
	CUR_TIME = awk 'BEGIN{srand(); print srand()}'
	TIME_FILE = $(dir $@).$(notdir $@)_time
	START_TIME = $(CUR_TIME) > $(TIME_FILE)
	END_TIME = read st < $(TIME_FILE) ; \
		$(RM) $(TIME_FILE) ; \
		st=$$((`$(CUR_TIME)` - $$st)) ; \
		echo $$st
else
	TIME_FILE = $(dir $@).$(notdir $@)_time
	START_TIME = date '+%s' > $(TIME_FILE)
	END_TIME = read st < $(TIME_FILE) ; \
		$(RM) $(TIME_FILE) ; \
		st=$$((`date '+%s'` - $$st - 86400)) ; \
		echo `date -u -d @$$st '+%H:%M:%S'`
endif

all: $(BIN_DIR)/$(TARGET)
	@echo "Making symlink: $(TARGET) -> $<"
	@$(RM) $(TARGET)
	@ln -s $(BIN_DIR)/$(TARGET) $(TARGET)

# Link the executable
$(BIN_DIR)/$(TARGET): $(OBJS)
	@echo "Linking: $@"
	@$(START_TIME)
	$(CC) $(OBJS) $(LFLAGS) -o $@
	@echo -en "\t Link time: "
	@$(END_TIME)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRCEXT)
	@echo "Compiling: $< -> $@"
	@$(START_TIME)
	$(CMD_PREFIX)$(CC) $(CFLAGS) $(INC_FLAGS) -MP -MMD -c $< -o $@
	@echo -en "\t Compile time: "
	@$(END_TIME)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -rf $(TARGET)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	
.PHONY: memcheck
memcheck: all
	valgrind -v --show-leak-kinds=all --leak-check=full --track-origins=yes \
	./$(TARGET)

# debugging make
print-% :
	@echo $* = $($*)