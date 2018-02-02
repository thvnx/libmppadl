system-name := bare

# build.rb defines the following variables: O, CLUSTER_TARGET, CFLAGS, INSTALL_LIBDIR, INSTALL_INCLUDEDIR, DOXYGEN_DIR

MPPADL_SRCS = 			\
	src/mppa_dl.c 		\
	src/mppa_dl_load.c 	\
	src/mppa_dl_sym.c 	\
	src/mppa_dl_error.c 	\
	src/mppa_dl_mem.c

use-module := strict-flags

mppadl-srcs := $(MPPADL_SRCS)
mppadl-cflags := -O2 -Iinclude $(CFLAGS)
mppadl-name := mppadl

somppadl-srcs := src/empty.c
somppadl-cflags := -O2 -fPIC -shared $(CFLAGS)
somppadl-lflags := -shared -nostdlib -nostartfiles
somppadl-name := libsomppadl.so

$(CLUSTER_TARGET)-lib := mppadl
$(CLUSTER_TARGET)-bin := somppadl # trick: use -bin rule to build a dynamic, shared library for io/cluster targets
# this will create a .so in bin/, a post-build-hooks rule will move it to lib/ 

post-build-hooks := mv-so-from-bin-to-lib

include $(K1_TOOLCHAIN_DIR)/share/make/Makefile.kalray

mv-so-from-bin-to-lib:
	mv $(O)/bin/libsomppadl.so $(O)/lib/$(CLUSTER_TARGET)

install:
	cp $(O)/lib/$(CLUSTER_TARGET)/lib*mppadl.{a,so} $(INSTALL_LIBDIR)
	cp include/*.h $(INSTALL_INCLUDEDIR)

doc:
	$(DOXYGEN_DIR)/bin/doxygen Doxyfile
	[ ! -s $(O)/doxygen_errors.log ] || echo "Missing documentation, see $(O)/doxygen_errors.log"
	[ ! -s $(O)/doxygen_errors.log ] || exit 1

.PHONY: doc