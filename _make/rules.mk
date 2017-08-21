default: app

.PHONY: depend
depend: .depend

.depend: app.cc
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;

#ebben van az app.o rule
include .depend

app.o: 
	$(CC) $(OPT) $(CFLAGS) -c app.cc

app: app.o
	$(CC) $(OPT) $(LFLAGS) app.o -o app


clean:
	rm -f app app.o 
