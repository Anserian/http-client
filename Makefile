CPPC=g++
CPPFLAGS= -Wc++11-extensions -Wc++11-extra-semi -lcurl

httpclient: client.o client.h index.cpp
	$(CPPC) $(CPPFLAGS) -o httpclient index.cpp client.o

client.o: client.h
	$(CPPC) $(CPPFLAGS) -c -o client.o client.cpp

clean:
	rm client.o httpclient
