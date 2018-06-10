C++ = g++
CPPFLAGS = -std=gnu++17
LIBS = -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -L/usr/local/lib -L../glew/lib
objects = $(patsubst %.cpp, build/%.o, $(wildcard *.cpp))

target/triangle: $(objects)
	$(C++) $(CPPFLAGS) $(LIBS) $^ -o $@

build/%.o: %.cpp
	$(C++) -c $(CPPFLAGS) $(LIBS) $^ -o $@

.PHONY: clean

clean:
	rm -r build/*

