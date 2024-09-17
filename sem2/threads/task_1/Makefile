TARGETS = thread thread_5 joinable_thread thread_inf struct_thread_join struct_thread_detach thread_inf_print thread_signals

CC=gcc
RM=rm
CFLAGS= -g -Wall -Werror -Wpedantic
LIBS=-lpthread
INCLUDE_DIR="."

all: ${TARGETS}

thread: thread.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} thread.c ${LIBS} -o thread

thread_5: thread_5.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} thread_5.c ${LIBS} -o thread_5

thread_signals: thread_signals.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} thread_signals.c ${LIBS} -o thread_signals

joinable_thread: joinable_thread.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} joinable_thread.c ${LIBS} -o joinable_thread

thread_inf: thread_inf.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} thread_inf.c ${LIBS} -o thread_inf

thread_inf_print: thread_inf_print.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} thread_inf_print.c ${LIBS} -o thread_inf_print

struct_thread_join: struct_thread_join.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} struct_thread_join.c ${LIBS} -o struct_thread_join

struct_thread_detach: struct_thread_detach.c
	${CC} ${CFLAGS} -I${INCLUDE_DIR} struct_thread_detach.c ${LIBS} -o struct_thread_detach

clean:
	${RM} -f *.o ${TARGETS}
