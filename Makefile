export CXX := $(shell wx-config --cxx)
export CFLAGS := -g -O2 -Wall $(shell wx-config --cxxflags)
export LIBS := $(shell wx-config --libs adv,core) -lasound -lusb-1.0

DummyRepeater:	Common.a
	make -C DummyRepeater
	echo $(LIBS)

Common.a:
	make -C Common

clean:
	make -C Common clean
	make -C DummyRepeater clean
