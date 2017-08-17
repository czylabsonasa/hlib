CC=g++ -std=c++11


WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

pDEPS=artipt.hpp csillagos.hpp graph.hpp tartaly.hpp treap.hpp common.hpp
DEPS=$(addprefix ../,$(pDEPS))


default:_app

_app: app.cc $(DEPS)
	$(CC) $(LF) app.cc -o _app


pgapp: 
	$(CC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > gp.out

clean:
	rm -f _app
