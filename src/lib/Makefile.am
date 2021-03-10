AUTOMAKE_OPTIONS = foreign
lib_LIBRARIES = libalolangcore.a
libalolangcore_a_SOURCES = unsafe.c testPuts.c types.c testrand.c

alolanglibdir=$(libdir)
alolanglib_PROGRAMS = libalolangcore.so
libalolangcore_so_SOURCES = unsafe.c testPuts.c types.c testrand.c
libalolangcore_so_LDFLAGS = -shared -fpic
