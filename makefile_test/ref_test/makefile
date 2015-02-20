VAL=1
REF1=$(VAL)  # recursively expanded variable
CPY1:=$(VAL) # simply expanded variable
VAL=2
REF2=$(VAL)
CPY2:=$(VAL)

test:
	@echo "VAL=" $(VAL)   # 2 last value
	@echo "REF1=" $(REF1) # 2 referenced
	@echo "CPY1=" $(CPY1) # 1 copied
	@echo "REF2=" $(REF2) # 2 referenced
	@echo "CPY2=" $(CPY2) # 2 copied

