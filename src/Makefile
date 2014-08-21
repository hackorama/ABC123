# 
# ABC123 for Curious Toddlers www.hackorama.com Summer 2008
#
# nmake /f Makefile run/clean/res/all
#

PROGRAM = ABC123.exe

CPP = cl
LD  = cl 
RC  = rc

RES 		= resource.rc 
INCLUDEDIRS =  /I "C:\Program Files\Microsoft SDKs\Windows\v6.1\Include"
LIBDIRS 	= /LIBPATH:"C:\Program Files\Microsoft SDKs\Windows\v6.1\Lib" 
CPPFLAGS 	= /D "WIN32" /EHsc  $(INCLUDEDIRS)
LDFLAGS 	= /link /OUT:$(PROGRAM)  $(LIBDIRS)

LIBS =  resource.RES user32.lib gdi32.lib  
SRCS = winmain.cpp win.cpp
OBJS = winmain.obj win.obj

.c.obj:
	$(CPP) $(CPPFLAGS) -c $< -Fo$@

$(PROGRAM) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(LIBS)

all : $(PROGRAM)  

clean:
	del $(OBJS) $(PROGRAM) 

run: all
	$(PROGRAM)

res: 
	$(RC) $(RES)
