ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
NULL =

SUBDIRS = build-aux src data demo po docs

INTLTOOL_FILES =				\
	intltool-extract.in			\
	intltool-merge.in			\
	intltool-update.in			\
	$(NULL)

DISTCLEANFILES =				\
	intltool-extract			\
	intltool-merge				\
	intltool-update				\
	po/.intltool-merge-cache		\
	$(NULL)

DISTCHECK_CONFIGURE_FLAGS= \
	--with-systemdsystemunitdir=$$dc_install_base/$(systemdsystemunitdir)

EXTRA_DIST =					\
	.version				\
	COPYING					\
	$(INTLTOOL_FILES)			\
	$(NULL)

MAINTAINERCLEANFILES =				\
	ABOUT-NLS				\
	aclocal.m4				\
	config.h.in				\
	build-aux/ar-lib			\
	build-aux/compile			\
	build-aux/config.guess			\
	build-aux/config.rpath			\
	build-aux/config.sub			\
	build-aux/depcomp			\
	build-aux/install-sh			\
	build-aux/ltmain.sh			\
	build-aux/missing			\
	build-aux/mkinstalldirs			\
	m4/intltool.m4				\
	m4/libtool.m4				\
	m4/ltoptions.m4				\
	m4/ltsugar.m4				\
	m4/ltversion.m4				\
	m4/lt~obsolete.m4			\
	po/Makefile.in.in			\
	po/Makevars.template			\
	po/Rules-quot				\
	po/boldquot.sed				\
	po/en@boldquot.header			\
	po/en@quot.header			\
	po/insert-header.sin			\
	po/quot.sed				\
	po/remove-potcdate.sin			\
	$(NULL)

BUILT_SOURCES = $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@

all:

-include $(top_srcdir)/git.mk
