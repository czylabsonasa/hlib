CC=g++ -std=c++11


WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

pDEPS=artipt.h csillagos.h graph.h tartaly.h treap.h common.h
DEPS=$(addprefix ../,$(pDEPS))


default:all

app: app.cc $(DEPS)
	$(CC) $(LF) app.cc -o app


pgapp: 
	$(CC) $(LF) -pg app.cc -o app; ./app ; gprof ./app > gp.out

openall: 
	kate *.h *.cc makefile model.conf run&

all: app

clean:
	rm -f app
