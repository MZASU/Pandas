FLAGS   = -Wall

DIRS = ../io ../brain

SOURCES = $(wildcard *.cpp)
OBJS	= $(patsubst %.cpp,%.o,${SOURCES})

OBJ_DIR = ../.obj

.DEFAULT_GOAL = faire

debug: FLAGS += -g 
debug: faire

opti: FLAGS += -O3
opti: MAKEFLAGS += opti
opti: faire
	
faire: ${OBJS}

${OBJS} : %.o : %.cpp
	@g++ $(addprefix -I ,${DIRS}) $(FLAGS) -c $< -o ${OBJ_DIR}/$@
	@echo "Compilation de " $@