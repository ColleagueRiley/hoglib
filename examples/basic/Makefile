
CC = gcc
CFLAGS = -Wall -I../../include -I./../../include
LDFLAGS = -L./build -lmediahog -Wl,-rpath=\$$ORIGIN
SOURCES = $(wildcard source/*.c)
OBJECTS = $(patsubst source/%.c, build/%.o, $(SOURCES))
OUTDIR = build
OUTPUT = basic
TARGET = $(OUTDIR)/$(OUTPUT)
PLATFORM = $(shell uname -s)

all: mediahog_lib $(TARGET)
debug: mediahog_lib $(TARGET)
	cd build && ./$(OUTPUT)

$(TARGET): $(OBJECTS) | $(OUTDIR)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

build/%.o: source/%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

mediahog_lib: ../../source/*.c ../../source/external/*.h ../../include/*/*.h $(OUTDIR)
	$(MAKE) -C ../..
	cp ../../build/* ./build

clean:
	rm -rf $(OUTDIR)
	rm -f source/*.o
	$(MAKE) -C mediahog clean

.PHONY: all clean mediahog_lib
