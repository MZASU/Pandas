FLAGS   = -Wall 

DIRS = ../io ../brain

SOURCES = $(wildcard *.cpp)
OBJS	= $(patsubst %.cpp,%.o,${SOURCES})

OBJ_DIR = ../.obj

.DEFAULT_GOAL = faire

faire: ${OBJS}

${OBJS} : %.o : %.cpp
	@g++ $(addprefix -I ,${DIRS}) ${FLAGS} -c $< -o ${OBJ_DIR}/$@
	@echo "Compilation de " $@