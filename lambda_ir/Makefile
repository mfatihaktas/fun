CPP = g++

.PHONY: all clean

APPS := ir_test

all: ${APPS}

ir_test: ir_test.o
	$(CPP) -g -o $@ $^ $(INC) $(LIB)

$(ODIR)/%.o: %.cpp
	$(CPP) -g -c -o $@ $< $(INC) $(LIB)

clean:
	rm -f *.o ${APPS}