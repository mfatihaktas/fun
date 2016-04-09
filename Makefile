CPP = g++
BOOST_DIR ?= /cac/u01/mfa51/Desktop/boost_1_56_0/install
# 
BOOST_INC = -I$(BOOST_DIR)/include
BOOST_LIB = -L$(BOOST_DIR)/lib -lboost_system -lpthread -lboost_thread -lboost_serialization
# 
IDIR = include
ODIR = obj

INC = -I$(IDIR) $(BOOST_INC)
LIB = $(BOOST_LIB)

.PHONY: all clean

APPS := exp

all: ${APPS}

exp: $(ODIR)/exp.o $(ODIR)/dp.o
	$(CPP) -g -o $@ $^ $(INC) $(LIB)

$(ODIR)/%.o: %.cpp
	$(CPP) -g -c -o $@ $< $(INC) $(LIB)

clean:
	rm -f $(ODIR)/*.o ${APPS}