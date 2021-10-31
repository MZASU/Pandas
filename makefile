FLAGS   = -Wall
BUILDFLAGS = faire

DIRS = io brain

SOURCES = $(wildcard *.cpp)
OBJS	= $(patsubst %.cpp,%.o,${SOURCES})

OBJ_DIR = .obj

.DEFAULT_GOAL = faire

debug: FLAGS += -g 
debug: BUILDFLAGS = debug
debug: faire

opti: FLAGS += -O3
opti: BUILDFLAGS = opti
opti: faire

compile: do_main do_others

faire: compile link

.PHONY: do_others ${DIRS}

link:
	@g++ $(FLAGS) $(wildcard ${OBJ_DIR}/*.o) -o main.out

do_others: ${DIRS}

${DIRS}:
	@make -C $@ $(BUILDFLAGS)

do_main: ${OBJS} 


${OBJS} : %.o : %.cpp
	@g++ $(addprefix -I ,${DIRS}) $(FLAGS) -c $< -o ${OBJ_DIR}/$@
	@echo "Compilation de " $@

