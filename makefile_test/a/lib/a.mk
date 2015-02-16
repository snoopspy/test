A_MAKEFILE_LIST:=$(MAKEFILE_LIST)
A_LASTWORD:=$(lastword $(A_MAKEFILE_LIST))
A_REALPATH:=$(realpath $(A_LASTWORD))
A_DIRNAME:=$(shell dirname $(A_REALPATH))
A_DIRNAME2:=$(shell dirname $(A_DIRNAME))
A_DIR:=$(shell dirname $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))

testa:
	@echo "A_MAKEFILE_LIST=" $(A_MAKEFILE_LIST)
	@echo "A_LASTWORD     =" $(A_LASTWORD)
	@echo "A_REALPATH     =" $(A_REALPATH)
	@echo "A_DIRNAME      =" $(A_DIRNAME)
	@echo "A_DIRNAME2     =" $(A_DIRNAME2)
	@echo "A_DIR          =" $(A_DIR)

