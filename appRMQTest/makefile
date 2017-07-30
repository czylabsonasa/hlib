CC=g++-6 -std=c++14 

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=
aDEPS=$(addprefix ../,$(aD))

bD=rmqtest.h common.h inc.h mrand.h utils.h destat.h
bDEPS=$(addprefix ../,$(bD))

cD=
cDEPS=$(addprefix ../,$(cD))

default:all
all: app


app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o app

old: 
	touch app.cc

pgapp: 
	$(CC) $(LF) -pg app.cc -o app; ./app ; gprof ./app > gp.out


clean:
	rm -f app
