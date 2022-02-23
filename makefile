TARGET = strelitzia

SOURCEDIR = sources
HEADERDIR = headers

PARAMS =
LIBS = -lm
CFLAGS = -g -O0 -Wextra -I./$(HEADERDIR)

HEADERS = $(wildcard $(HEADERDIR)/*.h)
SOURCES = $(wildcard $(SOURCEDIR)/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

.PHONY: all run clean debug valgrind

all: $(TARGET)

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f $(SOURCEDIR)/*.o
	-rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) $(PARAMS)

debug: $(TARGET)
	gdb -d $(SOURCEDIR) -d $(HEADERDIR) -ex="break main" -ex="layout src" -ex="run" --args ./$(TARGET) $(PARAMS)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) $(PARAMS)
