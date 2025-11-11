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
    DLL_TARGET = $(OUTDIR)/libhoglib.$(EXT)
    IMPLIB = $(OUTDIR)/libhoglib.a
    TARGET = $(DLL_TARGET)
    OBJECTS = $(patsubst source/%.c,$(OUTDIR)/%.o,$(SOURCES))
    CFLAGS += -DBUILD_DLL
else ifeq ($(PLATFORM),Darwin)
    EXT = dylib
    LDFLAGS = -dynamiclib
    RGFW_LIBS = -framework Cocoa -framework OpenGL -framework IOKit
    TARGET = $(OUTDIR)/libhoglib.$(EXT)
    OBJECTS = $(SOURCES:.c=.o)
else
    EXT = so
    LDFLAGS = -shared
    RGFW_LIBS = -lX11 -lGL -lm -ldl -lpthread -lXrandr
    TARGET = $(OUTDIR)/libhoglib.$(EXT)
    OBJECTS = $(SOURCES:.c=.o)
endif

PLATFORM_BACKEND ?= HL_PLATFORM_RGFW

LIBS = -Iinclude  -Lbuild ./build/libhoglib.a $(RGFW_LIBS)

CFLAGS += -D HL_PLATFORM_RGFW

EXAMPLES = examples/basics/basic \
		   examples/basics/textures \
		   examples/basics/text \


all: $(TARGET) $(OUTDIR)/libhoglib.a

debug: all $(EXAMPLES)
	@for exe in $(EXAMPLES); do \
		echo "Running $$exe..."; \
		./$$exe; \
	done
	make clean

$(OUTDIR)/libhoglib.a: $(OBJECTS) | $(OUTDIR)
	$(AR) rcs $@ $(OBJECTS)

$(DLL_TARGET): $(OBJECTS) | $(OUTDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(RGFW_LIBS)

$(OUTDIR)/libhoglib.so: $(OBJECTS) | $(OUTDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(RGFW_LIBS)

$(OUTDIR)/libhoglib.dylib: $(OBJECTS) | $(OUTDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(RGFW_LIBS)

$(OUTDIR)/%.o: source/%.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXAMPLES): %: %.c $(OUTDIR)/libhoglib.a
	$(CC) $< $(LIBS) -o $@

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
	rm -f source/*.o $(EXAMPLES)


.PHONY: all clean
