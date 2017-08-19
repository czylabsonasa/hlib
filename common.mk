CC=g++ -std=c++14

WR=-Wall -Wno-sign-compare -Wno-unused-results

CFLAGS=$(WR) -I..
LFLAGS=$(WR)


default: app

depend: .depend

.depend: app.cc
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;

include .depend

app.o: 
	$(CC) $(CFLAGS) -c app.cc

app: app.o
	$(CC) $(LFLAGS) app.o -o app


clean:
	rm -f app app.o 
