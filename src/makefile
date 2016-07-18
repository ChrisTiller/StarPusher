#compiler
CXX:= g++

#Program Name
EXE:= StarPusher

#SDL2 include/libraries
SDL_LIB:= -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE:= -I/usr/include 

#File Folders
DEPS:= ../include/*.h
PRJCTFLDR:= ~/Development/StarPusher/src/
DEPENDSFLDR:= ../depends/
OBJFLDR:= ../obj/
EXEFLDR:= ../bin/

#Files
SOURCES:=  $(wildcard *.cpp)
OBJECTS:= $(SOURCES:.cpp=.o)

#Flags
CXXFLAGS += -MD -MP -Wall -c -std=c++14 $(SDL_INCLUDE)
LDFLAGS += $(SDL_LIB)

.PHONY: all clean distclean

all: getFiles $(EXEFLDR)$(EXE) putFiles

$(EXEFLDR)$(EXE): $(OBJECTS)
	@echo "Buidling" $(EXE) "..."
	@$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "Build Successful"

.cpp.o:
	@echo "Compiling" $< "..."
	@$(CXX) $(CXXFLAGS) $< -o $@

getFiles:
	-@mv $(OBJFLDR)*.o $(PRJCTFLDR)
	-@mv $(DEPENDSFLDR)*.d $(PRJCTFLDR)

putFiles:
	-@mv *.o $(OBJFLDR)
	-@mv *.d $(DEPENDSFLDR)

clean: getFiles
	-@rm $(OBJECTS) 
	-@rm $(EXEFLDR)$(EXE)
	-@rm *.d

distclean: clean

-include $(SOURCES:%.cpp=%.d) $(DEPS:%.h=%.d)
