library(igraph)
elist2graph<-function(fname){
  #note that skip=1, in our edgelist there is
  #heading line with numbwer of vertices and edges
  elist<-as.matrix(read.table(fname,skip=1));
  return(graph_from_edgelist(elist, directed = FALSE));
}

ccf<-function(g){
  # function: because of a hard to remember options
  ccf<-mean(transitivity(g,type='local',isolates = "zero"));
}

# system.time(res<-diameter(g,directed = FALSE,unconnected = FALSE))
# specifying undirected and connected doesnt nake faster
crn<-coreness(g,mode = 'all')
mx=max(crn);
res<-hist(crn,breaks = -1:mx)$counts