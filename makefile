TARGET = strelitzia

SOURCEDIR = sources
HEADERDIR = headers

PARAMS =
LIBS = -lm
WARNS = -Wextra -Wimplicit-fallthrough=0
CFLAGS = -g -O0 -I./$(HEADERDIR) $(WARNS)

HEADERS = $(wildcard $(HEADERDIR)/*.h)
SOURCES = $(wildcard $(SOURCEDIR)/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: all run clean rebuild debug valgrind

all: $(TARGET)

%.o: %.c $(HEADERS)
	@gcc $(CFLAGS) -c $< -o $@
	@echo compiling $@ from $<

$(TARGET): $(OBJECTS)
	@gcc $(OBJECTS) $(CFLAGS) $(LIBS) -o $@
	@echo linking $@

clean:
	-rm -f $(SOURCEDIR)/*.o
	-rm -f $(TARGET)

rebuild: clean $(TARGET)

run: $(TARGET)
	./$(TARGET) $(PARAMS)

debug: $(TARGET)
	gdb -d $(SOURCEDIR) -d $(HEADERDIR) -ex="break main" -ex="layout src" -ex="run" --args ./$(TARGET) $(PARAMS)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) $(PARAMS)
