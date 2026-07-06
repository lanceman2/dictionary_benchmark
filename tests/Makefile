#! This is a "GNU make" make file.

# This is mostly testing that we know how to compile the C/C++ codes that
# we are benchmarking.

# Adding a test that is a bash script does not require editing this file.

src := ../d_src

CPPFLAGS += -I$(src) -DNO_LIBDEBUG_CONSTRUCTOR


BUILD_NO_INSTALL :=\
 002_debug\
 010_qsDictionary\
 020_rax\
 030_art\
 040_rbtree

002_debug_SOURCES := $(src)/debug.c debug.c

010_qsDictionary_SOURCES := $(src)/debug.c $(src)/Dictionary.c 010_qsDictionary.c

020_rax_SOURCES := $(src)/debug.c $(src)/rax.c 020_rax.c
020_rax_LDFLAGS := -lm # looks like it calls log() and floor()
020_rax_CPPFLAGS := -Wno-use-after-free #-DRAX_DEBUG_MSG

030_art_SOURCES := $(src)/debug.c $(src)/art.c 030_art.c
#030_art_LDFLAGS := -lm
#030_art_CPPFLAGS :=

040_rbtree_SOURCES := $(src)/debug.c $(src)/c-rbtree.c 040_rbtree.c



include ../quickbuild.make
