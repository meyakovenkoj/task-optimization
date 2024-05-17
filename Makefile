override CFLAGS   += -c -Wall
override CPPFLAGS += -D_GNU_SOURCE
override LDFLAGS  +=
SOURCES=main.c reduction.c arithm.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=program
LINKER?=$(CC)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINKER) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
