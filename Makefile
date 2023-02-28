
.DEFAULT_GOAL := stock

MAKEFLAGS += --always-make



clean:
	rm -f stock
	rm -Rf *.dSYM

stock:
	g++ stock.cpp -lcurl -lpugixml -o stock 

debug:
	g++ stock.cpp -lcurl -lpugixml -g -o debug 