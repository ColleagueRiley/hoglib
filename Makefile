
CC = gcc
INCLUDES = -I./include -I./source -I./source/external/ -I./source/external/renderers/
CFLAGS = -Wall -fPIC $(INCLUDES)
OUTDIR = build
SOURCES = $(wildcard source/*.c)
PLATFORM = $(shell uname -s)

ifeq ($(OS),Windows_NT)
    EXT = dll
    LDFLAGS = -shared
    RGFW_LIBS = -lgdi32 -lopengl32 -luser32 -lkernel32
    DLL_TARGET = $(OUTDIR)/libmediahog.$(EXT)
    IMPLIB = $(OUTDIR)/libmediahog.a
    TARGET = $(DLL_TARGET)
    OBJECTS = $(patsubst source/%.c,$(OUTDIR)/%.o,$(SOURCES))
    CFLAGS += -DBUILD_DLL
else ifeq ($(PLATFORM),Darwin)
    EXT = dylib
    LDFLAGS = -dynamiclib
    RGFW_LIBS = -framework Cocoa -framework OpenGL -framework IOKit
    TARGET = $(OUTDIR)/libmediahog.$(EXT)
    OBJECTS = $(SOURCES:.c=.o)
else
    EXT = so
    LDFLAGS = -shared
    RGFW_LIBS = -lX11 -lGL -lm -ldl -lpthread -lXrandr
    TARGET = $(OUTDIR)/libmediahog.$(EXT)
    OBJECTS = $(SOURCES:.c=.o)
endif

all: $(TARGET)

$(DLL_TARGET): $(OBJECTS) | $(OUTDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(RGFW_LIBS) -Wl,--out-implib,$(IMPLIB)

$(OUTDIR)/libmediahog.so: $(OBJECTS) | $(OUTDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(RGFW_LIBS)

$(OUTDIR)/libmediahog.dylib: $(OBJECTS) | $(OUTDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(RGFW_LIBS)

$(OUTDIR)/%.o: source/%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
	rm -f source/*.o

.PHONY: all clean
