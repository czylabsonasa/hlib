function rgbvsap(p)
  B=load("gapr");
  A=B(B(:,4)==p,:);
    
  rgb=A(:,3)./A(:,1);
  ap=A(:,2)./A(:,1);
  graphics_toolkit("gnuplot");
  plot(rgb,ap,'.');
end