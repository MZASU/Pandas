FLAGS   = -Wall 

SOURCES = $(wildcard *.cpp)
OBJS	= $(patsubst %.cpp,%.o,${SOURCES})

OBJ_DIR = ../.obj

.DEFAULT_GOAL = faire

faire: ${OBJS}

${OBJS} : %.o : %.cpp
	@g++ ${FLAGS} -c $< -o ${OBJ_DIR}/$@
	@echo "Compilation de " $@