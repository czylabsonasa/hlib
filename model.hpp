struct Model{
   int Step;
   int aStep;
   String mname;
   virtual void step1st()=0;
   virtual void gen()=0;
   String name();
   virtual void clear(int=0)=0;
};
