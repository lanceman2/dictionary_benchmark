# This file is for building and installing software with quickbuild and
# GNU make.


# There are two scripts that need to run to make this GNU makefile
# based software build system to be usable from a git clone download:
#
#   1.  ./bootstrap -- downloads some file(s)
#   2.  ./configure -- generate some file(s)
#
#   "make clean" will not remove any of these files. 
#
# We add checks for the needed files in this make file making this
# make file somewhat dummy proof.
#
ifneq ($(wildcard quickbuild.make),quickbuild.make)
$(error "First run './bootstrap'")
endif


BOOTSTRAP_FILES :=\
 quickbuild.make\
 config.make\
 debug.c\
 debug.h\
 c-rbtree.h\
 c-rbtree.c\
 c-rbtree-private.h\
 c-stdaux-generic.h\
 c-stdaux.h\
 c-stdaux-gnuc.h\
 c-stdaux-unix.h

# Add a "clean"-like target to remove files downloaded by bootstrap:
gitclean: cleaner
	rm -f $(BOOTSTRAP_FILES)


#$(warning thingy=$(strip $(filter %clean clean%, $(MAKECMDGOALS)) ))

# If the make targets include a "clean" like thing we clean
# the tests directory too.
ifeq ($(strip $(filter %clean clean%, $(MAKECMDGOALS))),)
ifneq ($(wildcard config.make),config.make)
$(error "Now run './configure'")
endif
endif


include quickbuild.make
