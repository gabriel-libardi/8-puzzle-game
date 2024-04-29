CC ?= gcc
ZIP ?= zip

CFLAGS += -Wall -Wextra -Wpedantic -Iinclude/
LDFLAGS += 
VDFLAGS += --leak-check=full --show-leak-kinds=all -s

EXECUTABLE ?= build/puzzle

ZIPFILE    ?= ./zipfile.zip
CFILES      = $(wildcard ./A_star/*.c)
OFILES      = $(patsubst A_star/%.c, objs/%.o, $(CFILES))

.PHONY: all clean zip run test debug

all: $(EXECUTABLE)

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
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

valgrind: $(EXECUTABLE)
	valgrind $(VDFLAGS) ./$(EXECUTABLE)