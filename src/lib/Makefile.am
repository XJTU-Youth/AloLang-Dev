AUTOMAKE_OPTIONS = foreign
lib_LIBRARIES = libalolangcore.a
libalolangcore_a_SOURCES = unsafe.c testPuts.c

alolanglibdir=$(libdir)
alolanglib_PROGRAMS = libalolangcore.so
libalolangcore_so_SOURCES = testPuts.c
libalolangcore_so_LDFLAGS = -shared -fpic
