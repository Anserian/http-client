CPPC=g++
CPPFLAGS= -Wc++11-extensions -Wc++11-extra-semi -lcurl

client: client.cpp client.h index.cpp
	$(CPPC) $(CPPFLAGS) -o httpclient client.cpp index.cpp

clean:
	rm httpclient
