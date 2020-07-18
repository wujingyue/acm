CXXFLAGS = -std=gnu++11 -g -Wall -Werror

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lbenchmark -lgtest_main -pthread

%_benchmark.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@ -L/usr/local/lib -lgtest -lbenchmark -lbenchmark_main -pthread

clean:
	rm -f *.exe

test_%: %.exe
	./$<

benchmark_%: %_benchmark.exe
	./$<

.PHONY: clean test_* benchmark_*
