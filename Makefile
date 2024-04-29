CC ?= gcc
ZIP ?= zip

CFLAGS += -Wall -Wextra -Wpedantic -Iinclude/
LDFLAGS += -shared -fPIC
VDFLAGS += --leak-check=full --show-leak-kinds=all -s

EXECUTABLE ?= build/puzzle
SHARED_LIB  = build/graph_search.so

ZIPFILE    ?= ./zipfile.zip
CFILES      = $(wildcard ./**/*.c)
OFILES      = $(patsubst **/%.c, objs/%.o, $(CFILES))

.PHONY: all clean zip run test debug

test: $(EXECUTABLE)
all:  $(SHARED_LIB)

objs/%.o: A_star/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(ZIPFILE)
	@rm -rf build/
	@rm -rf objs/*.o

zip: clean
	$(ZIP) $(ZIPFILE) ./*

run: $(EXECUTABLE)
	@./$(EXECUTABLE) $(ARGS)

debug: CFLAGS+= -g
debug: clean
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OFILES)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^

$(SHARED_LIB): $(OFILES)
	@mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

valgrind: $(EXECUTABLE)
	valgrind $(VDFLAGS) ./$(EXECUTABLE)