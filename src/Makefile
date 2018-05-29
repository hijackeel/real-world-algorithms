CC = clang
CFLAGS = -std=c11 -MMD -MP -g -O3 -Weverything\
  -Wno-disabled-macro-expansion -Wno-float-equal
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

1.1-array-stack-%-lib-test:\
lib1.1-array-stack-%-lib.so\
1.1-array-stack-%-lib-test.o
	$(compile_and_link_so)
	./$@

lib1.2-stock-span-lib.so: lib1.1-array-stack-size_t-lib.so 1.2-stock-span-lib.o
	$(CC) $(CFLAGS) 1.2-stock-span-lib.o -o $@ -shared\
    -l$(patsubst lib%.so, %, $<) -L. -Wl,-rpath,'$$ORIGIN'

1.2-stock-span-lib-test: lib1.2-stock-span-lib.so 1.2-stock-span-lib-test.o
	$(compile_and_link_so)
	./$@

1.2-stock-span-trial: lib1.2-stock-span-lib.so 1.2-stock-span-trial.o
	$(compile_and_link_so) `curl-config --libs`

lib1.3-rpn-lib.so: lib1.1-array-stack-double-lib.so 1.3-rpn-lib.o
	$(CC) $(CFLAGS) 1.3-rpn-lib.o -o $@ -shared\
    -l$(patsubst lib%.so, %, $<) -L. -Wl,-rpath,'$$ORIGIN'

1.3-rpn-lib-test: lib1.3-rpn-lib.so 1.3-rpn-lib-test.o
	$(compile_and_link_so)
	./$@

1.3-rpn: lib1.3-rpn-lib.so 1.3-rpn.o
	$(compile_and_link_so)

clean:
	rm -f *.o *.d *.so callgrind.* $(execs)

-include $(srcs:%.c=%.d)
