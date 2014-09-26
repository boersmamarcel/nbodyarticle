SHELL = bash

OBJS = main 

BUILDPATH = build/
INCLUDES = 
CFLAGS = -std=c++11 $$(sdl2-config --cflags) -O3 $(INCLUDES)
CLIBS = -framework OpenGL $$(sdl2-config --libs) 

PATHOBJS = $(patsubst %,$(BUILDPATH)%.o,$(OBJS))

all: sim
	
sim: $(PATHOBJS)
	g++ $(CFLAGS) $(CLIBS) $(PATHOBJS) -o sim

-include $(PATHOBJS:.o=.d)

$(BUILDPATH)%.o: %.cpp
	g++ -c $(CFLAGS) $*.cpp -o $(BUILDPATH)$*.o
	@echo -n $(BUILDPATH) > $(BUILDPATH)$*.d
	@g++ -MM $(CFLAGS) $*.cpp >> $(BUILDPATH)$*.d


clean:
	rm $(BUILDPATH)*.o $(BUILDPATH)*.d sim
