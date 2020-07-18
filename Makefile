CXXFLAGS = -std=gnu++11 -g -Wall -Werror

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.exe

.PHONY: clean
