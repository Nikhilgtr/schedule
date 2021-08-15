bin_PROGRAMS = schedule
schedule_SOURCES = main.c task.c timer.c  $(top_srcdir)/log.c/src/log.c
include_HEADERS = $(top_srcdir)/inc/task.h  $(top_srcdir)/inc/timer.h $(top_srcdir)/log.c/src/log.h
AM_CFLAGS = -I../inc -I../log.c/src/ -DLOG_USE_COLOR -g
AM_LDFLAGS = -lrt -lpthread

