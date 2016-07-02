include ../../../makefile.inc


all: 
	$(CXX) $(COMMON_FLAGS) $(INCLUDE) -I$(ROOTPATH)/vn.ctp/ctpapi -c vnctptd.cpp -o vnctptd.o
	$(CXX) $(COMMON_FLAGS) -shared -Wl,-soname,vnctptd.so -o vnctptd.so vnctptd.o -L$(ROOTPATH)/vn.ctp/ctpapi  $(LIBRARIES) -l:thostmduserapi.so -l:thosttraderapi.so
	cp vnctptd.so ../test
	cp vnctptd.so $(ROOTPATH)/vn.demo/ctpdemo
	cp vnctptd.so $(ROOTPATH)/vn.strategy/strategydemo
	
clean:
	rm *.o *.so
