FOOBAR_INSTALL_PATH=/usr/local

all:
	make debug
	make release
	make app_

update:
	git pull


debug:	libfoobar_d

libfoobar_d:
	cd lib && \
	qmake libfoobar.pro CONFIG+=debug && \
	make -f Makefile && \
	make clean -f Makefile && \
	cd ..

clean:
	find  -name '*.o' -delete
	find  -name '*.pro.user' -delete
	find  -name 'Makefile' -delete

