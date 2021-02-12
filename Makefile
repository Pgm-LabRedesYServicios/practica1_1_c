.PHONY: all
all : build/ping_noc

build/ping_noc : src/ping_noc.c
	cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
	cmake --build build
