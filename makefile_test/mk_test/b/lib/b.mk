B_MAKEFILE_LIST:=$(MAKEFILE_LIST)
B_LASTWORD:=$(lastword $(B_MAKEFILE_LIST))
B_REALPATH:=$(realpath $(B_LASTWORD))
B_DIRNAME:=$(shell dirname $(B_REALPATH))
B_DIRNAME2:=$(shell dirname $(B_DIRNAME))
B_DIR:=$(shell dirname $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))

include ../a/lib/a.mk

testb:
	@echo "B_MAKEFILE_LIST=" $(B_MAKEFILE_LIST)
	@echo "B_LASTWORD     =" $(B_LASTWORD)
	@echo "B_REALPATH     =" $(B_REALPATH)
	@echo "B_DIRNAME      =" $(B_DIRNAME)
	@echo "B_DIRNAME2     =" $(B_DIRNAME2)
	@echo "B_DIR          =" $(B_DIR)

