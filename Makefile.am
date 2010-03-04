ACLOCAL_AMFLAGS = -I m4

# includes append to these:
SUFFIXES =
PHONY =
TESTS =
CLEANFILES =
bin_PROGRAMS =
noinst_HEADERS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
noinst_PROGRAMS =
include_HEADERS =
nobase_include_HEADERS =
EXTRA_HEADERS =
BUILT_SOURCES=
EXTRA_DIST = 

SUBDIRS =

test-docs:
	(cd docs && $(MAKE) test-docs)
include libcassandra/include.am
include libgenthrift/include.am

check-local: test-no-outputdiff


fedora:
	rm -f ~/rpmbuild/RPMS/x86_64/libcassandra-$(VERSION)*.rpm
	rm -f ~/rpmbuild/SRPMS/libcassandra-$(VERSION)*.rpm
	cp libcassandra-$(VERSION).tar.gz ~/rpmbuild/SOURCES/
	rpmbuild -ba support/libcassandra.spec
	cp ~/rpmbuild/RPMS/x86_64/libcassandra-$(VERSION)*.rpm .
	cp ~/rpmbuild/SRPMS/libcassandra-$(VERSION)*.rpm .

generic:
	rm -f ~/rpmbuild/RPMS/x86_64/libcassandra-$(VERSION)*.rpm
	rm -f ~/rpmbuild/SRPMS/libcassandra-$(VERSION)*.rpm
	cp libcassandra-$(VERSION).tar.gz ~/rpmbuild/SOURCES/
	rpmbuild -ba support/libcassandra.spec
	cp ~/rpmbuild/RPMS/x86_64/libcassandra-$(VERSION)*.rpm .
	cp ~/rpmbuild/SRPMS/libcassandra-$(VERSION)*.rpm .

rpm: all dist generic fedora

lcov: lcov-clean check
	@echo
	@echo "	------------------------------------------------------"
	@echo "Make sure ./configure was run with '--enable-coverage'"
	@echo "------------------------------------------------------"
	@echo
	cd libcassandra && lcov --capture --directory . --base-directory .. --output-file lcov.out
	genhtml -o lcov --function-coverage -t libcassandra libcassandra/lcov.out

lcov-clean: clean
	rm -rf lcov */lcov.out 
	find . -name '*.gcno' | xargs rm -f
	find . -name '*.gcda' | xargs rm -f



