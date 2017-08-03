CC=g++-6 -std=c++14

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=
aDEPS=$(addprefix ../,$(aD))

bD=inc.h mrand.h utils.h destat.h
bDEPS=$(addprefix ../,$(bD))

cD=graph.h tartaly.h treap.h
cDEPS=$(addprefix ../,$(cD))

default:all
all: app


app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o _app

pgapp: 
	$(CC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > _gp.out


clean:
	rm -f _app
