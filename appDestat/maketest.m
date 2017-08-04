% veletelen vektort general
% kiirja a id.in file-ba, majd 
% ugyanezen vektor néhány leíróját 
% az id.out fájlba. 
% a hlib/destat tesztelésénél használva
function maketest(n,id)
  a=rand(n,1);
  fp=fopen(sprintf("%d.in",id),"w");
  fprintf(fp,"%d\n",n);
  fprintf(fp,"%.15f\n",a);
  fclose(fp);
  fp=fopen(sprintf("%d.out",id),"w");
  b=[min(a),max(a),max(a)-min(a),mean(a),std(a,1)];
  fprintf(fp,"5\n");
  fprintf(fp,"%.15f ",b);
  fclose(fp);
  
end