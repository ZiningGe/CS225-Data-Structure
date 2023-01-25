#Executable names:
EXE = main
TEST = test

#Add all object files needed for compiling:
EXE_OBJ = main.o 
OBJS = main.o Graph.o Vertex.o Edge.o fileio.o Layout.o Earth.o

#Generated files

#Use the cs225 makefile template:
include cs225/make/cs225.mk


# EXENAME = main
# TEST = test
# OBJS = main.o Graph.o Vertex.o Edge.o fileio.o Layout.o cs225/PNG.o cs225/HSLAPixel.o cs225/lodepng/lodepng.o

# CXX = clang++
# CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
# LD = clang++
# LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# .PHONY: all test clean output_msg

# all : $(EXENAME)

# # Custom Clang version enforcement Makefile rule:
# # for using 'make test'
# ccred=$(shell echo -e "\033[0;31m")
# ccyellow=$(shell echo -e "\033[0;33m")
# ccend=$(shell echo -e "\033[0m")

# IS_EWS=$(shell hostname | grep "ews.illinois.edu")
# IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
# ifneq ($(strip $(IS_EWS)),)
# ifeq ($(strip $(IS_CORRECT_CLANG)),)
# CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1'. $(ccend))
# endif
# else
# CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
# endif

# output_msg: ; $(CLANG_VERSION_MSG)

# $(EXENAME) : output_msg $(OBJS)
# 	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# #include cs225/make/cs225.mk

# #object file dependncies
# main.o : main.cpp Graph.cpp Graph.h 
# 	$(CXX) $(CXXFLAGS) main.cpp

# Graph.o : Graph.cpp Graph.h Vertex.cpp Vertex.h Edge.h Edge.cpp
# 	$(CXX) $(CXXFLAGS) Graph.cpp

# Vertex.o : Vertex.cpp Vertex.h 
# 	$(CXX) $(CXXFLAGS) Vertex.cpp 

# Edge.o : Edge.cpp Edge.h Vertex.cpp Vertex.h
# 	$(CXX) $(CXXFLAGS) Edge.cpp

# fileio.o : fileio.cpp fileio.h
# 	$(CXX) $(CXXFLAGS) fileio.cpp

# Layout.o : Layout.cpp Layout.h Graph.cpp Graph.h Vertex.cpp Vertex.h Edge.h Edge.cpp
# 	$(CXX) $(CXXFLAGS) Layout.cpp

# PNG.o : cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
# 	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

# HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
# 	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

# lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
# 	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp


# test: output_msg cs225/catch/catchmain.cpp tests/tests.cpp Edge.cpp Vertex.cpp Graph.cpp fileio.cpp
# 	$(LD) cs225/catch/catchmain.cpp tests/tests.cpp Edge.cpp Vertex.cpp Graph.cpp fileio.cpp $(LDFLAGS) -o test

# clean:
# 	rm -rf *.d $(OBJS) test cs225/*.d cs225/lodepng/*.d