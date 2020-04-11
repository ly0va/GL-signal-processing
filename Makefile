headers = timespan.h wave.h cli.h

main : main.o timespan.o cli.o
	$(CXX) -o $@ $^ -lsndfile

timespan.o : timespan.cpp $(headers)
	$(CXX) -c -o $@ $<

main.o : main.cpp $(headers)
	$(CXX) -c -o $@ $<

cli.o : cli.cpp $(headers)
	$(CXX) -c -o $@ $<

clean : 
	rm -f *.o main

.PHONY : clean
