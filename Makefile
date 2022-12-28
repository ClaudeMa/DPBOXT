CC		= gcc
CPP		= $(CC) -E
CFLAGS		= -funsigned-char -O2 -DDPBOXT_LINUX
LD		= $(CC)
LDFLAGS		=  
DEFS		=
LIBS		= -ltermcap

HDRS		= tnt.h \
		  window.h \
                  init.h \
                  config.h \
                  keys.h \
                  iface.h \
		  ifacedef.h \
                  boxlist.h

OBJS		= main.o \
		  keyboard.o \
                  display.o \
		  window.o \
                  file.o \
                  codconv.o \
                  init.o \
                  iface.o \
                  boxlist.o

SRCS		= main.c \
                  keyboard.c \
                  display.c \
		  window.c \
                  file.c \
                  codconv.c \
                  init.c \
                  iface.c \
                  boxlist.c

OTHERS          = dpboxt.ini \
                  fkeys.tnt \
                  Makefile

all:		dpboxt

tgz:
		@echo Creating dpboxtsrc.tgz
		@tar -cvzf dpboxtsrc.tgz $(SRCS) $(HDRS) $(OTHERS)

dpboxt:		$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o dpboxt;

clean:
	rm -f   *.o *~ .*~ dpboxt .depend

dep:
	$(CPP) -M $(CFLAGS) $(SRCS) > .depend

#
# include a dependency file if one exists
#
ifeq (.depend,$(wildcard .depend))
include .depend
endif
