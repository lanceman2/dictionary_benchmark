# dictionary_benchmark

An automatic, configurable, modular dictionary benchmark.

We needed a fast and small C code that makes a dictionary in process
memory.  Using red black tree would be a good start, but we think that an
adaptive trie would be better if we can limit the memory usage.

We also require that the code be free.  Non-free code is not useful for
our use-case.  We'll only use software which we can automate the running
and building of the software with a simple non-interactive wget bash
script.  We require that the source code not change for a given URL so
that test results are automatic and somewhat reproducible.

It would seem that the world runs on dictionaries built on red black
trees, so we'll have at least one test case that uses a red black tree,
maybe even the C++ standard library map class (which is a red black tree);
given C++ and C get along well and C++ is well standardized.  We expect
the red black tree based cases to be the least preferment, at least for
speed.

The idea of this software project is to have one script that you run that
automatically downloads, builds software, and generates plot image files
of the test results.  There may be sub-scripts within the top script.

We limit the operating system to that from a GNU/Linux distribution.   We
started with Debian GNU/Linux 13 KDE Plasma Version 6.3.6 with kernel
version 6.12.74+deb13+1-amd64 (64-bit) with Wayland on 16 × AMD Ryzen 7
255 w/ Radeon 780M Graphics, 32 GiB of RAM.  It may or may not work on
many other computers and operating systems.  We will make a small effort
to keep it runnable on other UNIX-like software distributions.  We make no
effort to port to MS-Window or OS-X, though we may define a DIR-string
macro out of habit.

We make a module for each dictionary code and make the possibility of
having difference test cases that use the same base C code, but with
different configurations.  For example, different build options, or
different wrapper code from this package.

Adding a new C/C++ base data structure code package should be easy by
copying an existing C/C++ base data structure code package module.


## Dependencies

This package has scripts that downloads many needed software packages,
like the non-standard software packages we are benchmarking.  It requires
a standard development computer operating system.  For example if you do
not have "wget" or GCC installed, you do not have the standard development
computer operating system.  Use trial and error (failures) to figure it
out.


## Just run this

We recommend you do not run strange scripts that you do not trust without
protection; at least don't run this script as the root user.  Running this
script will download software packages, including this one, and others.

To get the benchmark image results, run this script in a "sandbox" of your
choosing, in a directory of you choosing:

```bash
 tag=master\
&&\
 tarfile=dictionary_benchmark-tar.gz\
&&\
 wget --no-check-certificate\
 https://github.com/lanceman2/dictionary_benchmark/tarball/$tag\
 -O $tarfile\
&&\
 mkdir dictionary_benchmark\
&&\
 cd dictionary_benchmark\
&&\
 tar --strip-components=1 -xzf ../$tarfile
```

The above script is a little complex in order to make it work without
user interactivity; like finding githubs generated tar file name.  But, of
course, you can just make your own script(s) to run the benchmark by using
that script as a hint.

We keep the above script working in order automate our testing of this
software package, and at the same time letting users, that are not
developers of this software package, quickly see our results.


## List of packages/modules benchmarked

This is a list of the software packages (or parts there of) that are
benchmarked.  Some software packages may be benchmarked more than once
using different configurations and/or software versions.

### rax

https://github.com/antirez/rax.git


### libart

https://github.com/armon/libart.git


### C++ map


### c-rbtree

https://github.com/c-util/c-rbtree.git




