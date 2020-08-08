CXXFLAGS = -std=gnu++11 -g -O2 -Wall -Werror

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.exe

.PHONY: clean
