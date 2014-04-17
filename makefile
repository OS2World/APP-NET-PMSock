#
# Makefile for PMSOCK 0.1
#

# directory where IBM TCP/IP is installed
#
TCPIP = D:\tcpip

# Make sure TCPLIB is in your LIBRARY_PATH
# tcp32dll.a and so32dll.a are expected to be found in
# this directory.  If not, they will be created and copied there.
# This can be emx/lib if you prefer.  Note you can't use drive letters..
TCPLIB = \tcpip\lib
TCPLIBS = $(TCPLIB)/tcp32dll.a $(TCPLIB)/so32dll.a
IMP = implib

CC = gcc
CFLAGS = -Zc++-comments -D_System=
LIBS = -ltcp32dll -lso32dll

all: $(TCPLIBS) daytime.exe

$(TCPLIB)/tcp32dll.a: $(TCPIP)\dll\tcp32dll.dll
	socklib $(TCPIP) tcp32dll
	@if not exist $(TCPLIB)\tcp32dll.a copy tcp32dll.a $(TCPLIB)	

$(TCPLIB)/so32dll.a: $(TCPIP)/dll/so32dll.dll
	socklib $(TCPIP) so32dll
	@if not exist $(TCPLIB)\so32dll.a copy so32dll.a $(TCPLIB)	

pmsock.o: pmsock.c pmsock.h
	$(CC) $(CFLAGS) -c pmsock.c 

daytime.o: daytime.c pmsock.h
	$(CC) $(CFLAGS) -c daytime.c

daytime.exe: daytime.o pmsock.o
	$(CC) $(CFLAGS) daytime.o pmsock.o $(LIBS) -o daytime.exe
