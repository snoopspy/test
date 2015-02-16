C_MAKEFILE_LIST:=$(MAKEFILE_LIST)
C_LASTWORD:=$(lastword $(C_MAKEFILE_LIST))
C_REALPATH:=$(realpath $(C_LASTWORD))
C_DIRNAME:=$(shell dirname $(C_REALPATH))
C_DIRNAME2:=$(shell dirname $(C_DIRNAME))
C_DIR:=$(shell dirname $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))

include ../b/lib/b.mk

testc:
	@echo "C_MAKEFILE_LIST=" $(C_MAKEFILE_LIST)
	@echo "C_LASTWORD     =" $(C_LASTWORD)
	@echo "C_REALPATH     =" $(C_REALPATH)
	@echo "C_DIRNAME      =" $(C_DIRNAME)
	@echo "C_DIRNAME2     =" $(C_DIRNAME2)
	@echo "C_DIR          =" $(C_DIR)

