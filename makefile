FLAGS   = -Wall 

DIRS = io brain

SOURCES = ${wildcard *.cpp}
OBJS	= $(patsubst %.cpp,%.o,${SOURCES})

OBJ_DIR = .obj

.DEFAULT_GOAL = faire

faire: compile link

link:
	@g++ ${FLAGS} ${wildcard ${OBJ_DIR}/*.o} -o main.out

compile: do_others do_main

do_others:         
		@for dir in $(DIRS); do \
          make -C $$dir; \
        done



do_main: ${OBJS} 

${OBJS} : %.o : %.cpp
	@g++ ${FLAGS} -c $< -o ${OBJ_DIR}/$@
	@echo "Compilation de " $@

