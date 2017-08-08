CC=g++-6 -std=c++14 

WR=-Wall

CF=$(WR) 
LF=$(WR) -I..

aD=
aDEPS=$(addprefix ../,$(aD))

bD=rmqtest.hpp common.hpp inc.hpp mrand.hpp utils.hpp destat.hpp
bDEPS=$(addprefix ../,$(bD))

cD=
cDEPS=$(addprefix ../,$(cD))

default:all
all: app


app: app.cc $(aDEPS) $(bDEPS) $(cDEPS)
	$(CC) $(LF) app.cc -o _app

old: 
	touch app.cc

pgapp: 
	$(CC) $(LF) -pg app.cc -o _app; ./_app ; gprof ./_app > gp.out


clean:
	rm -f _app
