function rajz(fname)
  graphics_toolkit('gnuplot')
  hold off;
  X=dlmread(fname,' ');
  pr=X(:,2)/100.0;
  deg=X(:,3);mdeg=mean(deg);
  deg=deg/sum(deg);
  plot(deg,pr,'x');
  hold on;
  mx=max(deg);mx=max(pr,mx);
  s=mx/50;
  plot(0:s:mx,0:s:mx,'-r;y=x;');
  xlabel('degree');
  ylabel('pagerank');
  title(sprintf('mean degree:%f',mdeg))
  print(fname,'-dpdf')
end