/*
Cai dat ham theo nguyen mau va 
kiem thu
*/
Quiz1:
int BSearch(void* a, 
            int sz, int l, int r,
            void* item,
            int (*compare)(void*, void*));
  /*
    Test:
      int
      float 
      double
  */
Quiz2:
int BSearch(Jval* a,
            int l, int r,
            const Jval* item,
            int (*compare)(Jval*, Jval*));
  /*
    Test:
      int
      float 
      double
  */