headers = timespan.h wave.h

main : main.o timespan.o 
	$(CXX) -o $@ $^

timespan.o : timespan.cpp $(headers)
	$(CXX) -c -o $@ $<

main.o : main.cpp $(headers)
	$(CXX) -c -o $@ $<

clean : 
	rm -f *.o main

.PHONY : clean
