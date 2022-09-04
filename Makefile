#
# makefile for ppm2fli
# Copyright (C) 1995-2002 Klaus Ehrenfried
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#

# ---------------- Config Section ----------------------------------
# Compiler to be used
CC=gcc

#
# Cflags
#
CFLAGS=-O2 -Wall
# ------------------------------------------------------------------

.c.o:
	$(CC) $(CFLAGS) -c $*.c

#
# All targets
#
all: ppm2fli unflick

#
# Objects for ppm2fli
#
OBJA = \
	amain.o \
	alist.o \
	aoctree.o \
	aimage.o \
	aframe.o \
	acolor.o \
	abrun.o \
	alc.o \
	adelta.o \
	ainput.o \
	appm.o \
	afbm.o

#
# Objects for unflick
#
OBJU = \
	umain.o \
	uunfli.o \
	uwchunks.o \
	uoutput.o

#
# Executables
#
ppm2fli: $(OBJA)
	gcc -o $@ $(OBJA)

unflick: $(OBJU)
	gcc -o $@ $(OBJU)

#
# Dependecies
#
$(OBJA) : apro.h
$(OBJU) : upro.h
