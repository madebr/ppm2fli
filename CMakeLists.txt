cmake_minimum_required(VERSION 3.0)
project(ppm2fli C)

if(CMAKE_COMPILER_ID MATCHES "MSVC")
else()
	add_compile_options(-Wall)
endif()

set_source_files_properties(amain.c PROPERTIES COMPILE_DEFINITIONS MAIN)

add_executable(ppm2fli
	apro.h
	amain.c
	alist.c
	aoctree.c
	aimage.c
	aframe.c
	acolor.c
	abrun.c
	alc.c
	adelta.c
	ainput.c
	appm.c
	afbm.c
)

add_executable(unflick
	upro.h
	umain.c
	uunfli.c
	uwchunks.c
	uoutput.c
)
