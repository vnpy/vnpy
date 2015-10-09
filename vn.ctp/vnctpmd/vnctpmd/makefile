include ../../../makefile.inc


all: 
	$(CXX) $(COMMON_FLAGS) $(INCLUDE) -I$(ROOTPATH)/vn.ctp/ctpapi -c vnctpmd.cpp -o vnctpmd.o
	$(CXX) $(COMMON_FLAGS) -shared -Wl,-soname,vnctpmd.so -o vnctpmd.so vnctpmd.o -L$(ROOTPATH)/vn.ctp/ctpapi  $(LIBRARIES) -l:thostmduserapi.so -l:thosttraderapi.so
	cp vnctpmd.so ../test
	cp vnctpmd.so $(ROOTPATH)/vn.demo/ctpdemo
	cp vnctpmd.so $(ROOTPATH)/vn.strategy/strategydemo
	
clean:
	rm *.o *.so
