CC=g++ -std=c++11
PCC=g++-4.9 -std=c++11

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=csillagos.h pagerank.h cluster.h
aDEPS=$(addprefix ../,$(aD))

bD=common.h inc.h mrand.h utils.h destat.h
bDEPS=$(addprefix ../,$(bD))

cD=graph.h tartaly.h treap.h
cDEPS=$(addprefix ../,$(cD))

default:all
all: app


app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o app

pgapp: 
	$(PCC) $(LF) -pg app.cc -o app; ./app ; gprof ./app > gp.out


clean:
	rm -f app
