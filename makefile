FLAGS   = -Wall 

DIRS = io brain

SOURCES = $(wildcard *.cpp)
OBJS	= $(patsubst %.cpp,%.o,${SOURCES})

OBJ_DIR = .obj

.DEFAULT_GOAL = faire

compile: do_main do_others

faire: compile link

.PHONY: do_others ${DIRS}

link:
	@g++ ${FLAGS} $(wildcard ${OBJ_DIR}/*.o) -o main.out

do_others: ${DIRS}

${DIRS}:
	@make -C $@

do_main: ${OBJS} 


${OBJS} : %.o : %.cpp
	@g++ $(addprefix -I ,${DIRS}) ${FLAGS} -c $< -o ${OBJ_DIR}/$@
	@echo "Compilation de " $@

