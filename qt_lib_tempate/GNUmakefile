FOOBAR_INSTALL_PATH=/usr/local

all:
	make debug
	make release
	make app_

update:
	git pull


debug:	libfoobar_d libfoobar_gui_d

release: libfoobar libfoobar_gui

libfoobar_d:
	cd lib && \
	qmake libfoobar.pro CONFIG+=debug && \
	make -f Makefile && \
	make clean -f Makefile && \
	cd ..

libfoobar_gui_d:
	cd lib && \
	qmake libfoobar_gui.pro CONFIG+=debug && \
	make -f Makefile && \
	make clean -f Makefile && \
	cd ..

libfoobar:
	cd lib && \
	qmake libfoobar.pro CONFIG+=release && \
	make -f Makefile && \
	make clean -f Makefile && \
	cd ..

libfoobar_gui:
	cd lib && \
	qmake libfoobar_gui.pro CONFIG+=release && \
	make -f Makefile && \
	make clean -f Makefile && \
	cd ..

app_:
	cd app && \
	qmake && \
	make && \
	cd ..
clean:
	find  -name '*.o' -delete
	find  -name '*.pro.user' -delete
	find  -name 'Makefile' -delete

