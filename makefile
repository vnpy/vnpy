include makefile.inc

DYLIBS= vnctpmd.so vnctptd.so
#vnltsmd.so vnltstd.so vnltsl2.so

all: $(DYLIBS)


vnltsmd.so:
	cd vn.lts/vnltsmd/pyltsmd;make all

vnltstd.so:
	cd vn.lts/vnltstd/pyltstd;make all

vnltsl2.so:
	cd vn.lts/vnltsl2/vnltsl2;make all

vnctpmd.so:
	cd vn.ctp/vnctpmd/vnctpmd;make all

vnctptd.so:
	cd vn.ctp/vnctptd/vnctptd;make all
