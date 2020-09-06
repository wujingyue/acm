CXXFLAGS = -std=gnu++11 -g -Wall -Werror -O2

%.exe: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.exe *.o

test_%: %.exe
	./$< < $(subst .exe,.in,$<)

.PHONY: clean test_*
