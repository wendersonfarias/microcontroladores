///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////


#include <ctype.h>

BYTE gethex1() {
   char digit;

   digit = getch();

   putc(digit);

   if(digit<='9')
     return(digit-'0');
   else
     return((toupper(digit)-'A')+10);
}

BYTE gethex() {
   unsigned int8 lo,hi;

   hi = gethex1();
   lo = gethex1();
   if(lo==0xdd)
     return(hi);
   else
     return( hi*16+lo );
}

void get_string(char* s, unsigned int8 max) {
   unsigned int8 len;
   char c;

   --max;
   len=0;
   do {
     c=getc();
     if(c==8) {  // Backspace
        if(len>0) {
          len--;
          putc(c);
          putc(' ');
          putc(c);
        }
     } else if ((c>=' ')&&(c<='~'))
       if(len<=max) {
         s[len++]=c;
         putc(c);
       }
   } while(c!=13);
   s[len]=0;
}

// stdlib.h is required for the ato_ conversions
// in the following functions
#ifdef _STDLIB
#if !defined(__PCD__)
signed int8 get_int() {
  char s[5];
  signed int8 i;

  get_string(s, 5);

  i=atoi(s);
  return(i);
}
#endif

#if defined(__PCD__)
signed int16 get_int() {
  char s[5];
  signed int16 i;

  get_string(s, 7);

  i=atoi(s);
  return(i);
}
#endif

#if !defined(__PCD__)
signed int16 get_long() {
  char s[7];
  signed int16 l;

  get_string(s, 7);
  l=atol(s);
  return(l);
}
#endif

#if defined(__PCD__)
signed int32 get_long() {
  char s[7];
  signed int32 l;

  get_string(s, 10);
  l=atoi32(s);
  return(l);
}
#endif

float get_float() {
  char s[20];
  float f;

  get_string(s, 20);
  f = atof(s);
  return(f);
}

#endif
