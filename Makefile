# This file is for building software with quickbuild and GNU make.


# There are two scripts that need to run to make this GNU makefile
# based software build system to be usable from a git clone download:
#
#   1.  ./bootstrap -- downloads some file(s)
#   2.  ./configure -- generate `config.make`
#
#   3. (optional)  edit `config.make`
#
#     "make clean" will not remove any of these files, but
#     "make gitclean" and "make cleaner" remove more files.
#
#   4.  make
#
#   5.  ./run



# We add checks for the needed files in this make file making this
# make file somewhat dummy proof.

ifeq ($(strip $(filter %clean clean%, $(MAKECMDGOALS))),)
# Not a cleaning target.
ifneq ($(wildcard quickbuild.make),quickbuild.make)
$(error "First run './bootstrap' to download files")
endif
ifneq ($(wildcard config.make),config.make)
$(error "Now run './configure'")
endif
endif


# Add a "clean"-like target to remove files downloaded by bootstrap:
gitclean: cleaner
	rm -f quickbuild.make config.make
	rm -rf d_src


# We choose to "error out" if we get here and quickbuild.make is not
# present.  
include quickbuild.make
