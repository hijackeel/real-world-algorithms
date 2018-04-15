CC = clang
CFLAGS = -std=c11 -MMD -MP -g -O3 -Wall
srcs = $(wildcard *.c)
execs = $(basename $(filter-out %lib.c, $(srcs)))

define compile_and_link_so
$(CC) $(CFLAGS) $@.o -o $@\
  -l$(patsubst lib%.so, %, $<) -L. -Wl,-rpath,'$$ORIGIN'
endef

.PRECIOUS: %.o
.PHONY: all clean

all: $(execs)

lib%.so: %.o
	$(CC) $(CFLAGS) $^ -o $@ -shared

1.1-array-based-stack-lib-test:\
lib1.1-array-based-stack-lib.so\
1.1-array-based-stack-lib-test.o
	$(compile_and_link_so)
	./$@

1.2-stock-span-problem-with-stack:\
lib1.1-array-based-stack-lib.so\
1.2-stock-span-problem-with-stack.o
	$(compile_and_link_so)

clean:
	rm -f *.o *.d *.so $(execs)

-include $(srcs:%.c=%.d)
