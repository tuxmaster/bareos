#
# BAREOS® - Backup Archiving REcovery Open Sourced
#
# Copyright (C) 2014-2014 Bareos GmbH & Co. KG
#
# This program is Free Software; you can redistribute it and/or
# modify it under the terms of version three of the GNU Affero General Public
# License as published by the Free Software Foundation and included
# in the file LICENSE.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.
#
VPATH = .:../../console

include ../Makefile.inc

INCLUDES = -I../.. \
	   -I../../include \
	   -I../include \
	   -I../compat/include \
	   -I../vss/include
LDLIBS = ../lib/libbareos.a \
	 ../lib/libbareos.dll \
         $(MINGW_LIB)/libwinpthread.a \
         $(MINGW_LIB)/libz.dll.a \
         $(MINGW_LIB)/libreadline.dll.a \
         $(MINGW_LIB)/libjansson.a \
	 $(WINSOCKLIB) -lole32 -loleaut32 -luuid

CONSSRCS = console.c console_conf.c
CONSOBJS = $(CONSSRCS:.c=.o)

WINDRESSRCS = consoleres.rc
WINDRESOBJS = $(WINDRESSRCS:.rc=.o)

all: bconsole.exe

bconsole.exe: DLL_USAGE = -DUSING_DLL
bconsole.exe: $(CONSOBJS) $(WINDRESOBJS)
	$(CXX) $(LDFLAGS_CONS) $(CONSOBJS) $(LDLIBS) $(WINDRESOBJS) -o $@

clean:
	rm -f *.o

distclean:: clean
	rm -f bconsole.exe

# inference rules
.c.o:
	@echo "Compiling $<"
	$(CXX) $(DLL_USAGE) $(CXXFLAGS) -c -o $@ $<

%.o : %.rc
	@echo "Ressource Compiling $^"
	$(WINDRES) $^ -o $@

