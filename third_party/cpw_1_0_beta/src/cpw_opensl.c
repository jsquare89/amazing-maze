/*

** OpenSL - the open string library

**

** See include file for more info.

*/



#include "cpw_opensl.h"
#include <ctype.h>


/****************************************************

** platform dependent - replace implementations with

** platform specific unicode calls.

****************************************************/



int slLength(char *s)

{

    return slstrlen(s);

}



char *slStringOfSize(int size)

{

    char *ns;

    /* needs to be adjusted for unicode */

    size++; /* add space for null character on end */

    ns = (char *)slmalloc(size);

    memset(ns, 0, size);

    return ns;

}



void slFree(char *s)

{

    slfree(s);

}



void slClear(char *s)

{

    /* needs to be adjusted for unicode */

    int len = slLength(s);

    if (s == NULL) { return; }

    memset(s, (char)0x00, len);

}



/****************************************************

** string creation

****************************************************/



char *slStringFromBuffer(void* buf, int size)

{

    char *ns = slStringOfSize(size+1);

    memcpy(ns, buf, size);

    ns[size] = 0;

    return ns;

}



char *slSizeTo(char *s, int inLen)

{

    char *ns;

    int len;

    if ( s == NULL ) return slStringOfSize(0);

    len = slLength(s);



    /*if ( len > inLen ) return s;*/

    ns = slStringOfSize(inLen+1);

    memset(ns, ' ', inLen);

    memcpy(ns, s, len);

    ns[inLen] = 0;

    return ns;

}



char *slCopy(char *s)

{

    char *ns;

    int len;

    if ( s == NULL ) return slStringOfSize(0);

    len = slLength(s);

    ns = slStringOfSize(len+1);

    memcpy(ns, s, len+1);

    ns[len] = 0;

    return ns;

}



/****************************************************

** character operations

** unicode may mess with these...

****************************************************/



char slCharAt(char *s, int pos ) 

{

    int len = slLength(s);

    if ( len == -1 || pos > len ) { return (char)0x00; }

    return s[slWrapPos(s, pos)];

}



int slSetCharAt(char *s, int pos, char c ) 

{

    int len = slLength(s);

    if ( len == -1 || pos > len ) { return 0; }

    s[slWrapPos(s, pos)] = c;

    return 1;

}



void slDropLastChar(char *s)

{

    int len = slLength(s) - 1;

    if ( len > 0 ) { s[len]=(char)0x00; }

}



void slDropCharAt(char *s, int pos ) 

{

    int len = slLength(s);

    if ( len < 1 ) return;

    /*if ( pos > len+1 ) return;*/

    pos = slWrapPos(s, pos);

    memmove(s+pos*CHARSIZE, s+(pos+1)*CHARSIZE, (len-pos+1)*CHARSIZE);



/*    

    for ( i=pos; i < len+1; i++) 

      s[i] = s[i+1];

    s[len-1]=(char)0x00;

*/

}



/****************************************************

** string modification operations

** new string is returned that caller must free

****************************************************/





char *slAppend(char *s, char *s2)

{

    int len  = slLength(s);

    int len2 = slLength(s2);

    char *ns = slStringOfSize(len+len2+1);

    memcpy(ns, s, len);

    memcpy(ns+(len*CHARSIZE), s2, len2); 

    ns[len+len2] = 0;

    return ns;

}



char *slAppendAndFree(char *s, char *s2)

{

    /* frees s before returning new string */

    char *ns = slAppend(s, s2);

    slFree(s);

    return ns;

}



/*

char *slPreppend(char *s, char *s2)

{

    return slAppend(s2, s);

}

*/



char *slSubString(char *s, int startpos, int endpos ) 

{

    char *ns;

    int newlen;

    startpos = slWrapPos(s, startpos);

    endpos   = slWrapPos(s, endpos);

    newlen = endpos - startpos+1;

    if ( newlen < 1 ) return slStringOfSize(0);

    

    ns = slStringOfSize(newlen+1);

    memcpy(ns, s+(startpos*CHARSIZE), newlen*CHARSIZE);

    ns[newlen] = 0;

    return ns;

}



char *slInsert(char *s, char *s2, int pos ) 

{

    char *ns;

    int len  = slLength(s);

    int len2 = slLength(s2);

    pos = slWrapPos(s, pos);

    

    if (pos == len) return slAppend(s, s2); 

    

    ns = slStringOfSize(len+len2+1);



    memcpy(ns, s, pos);

    memcpy(ns+pos, s2, len2);

    memcpy(ns+pos+len2, s+pos, len-pos);

    ns[len+len2] = 0;

    return ns;

}



char *slLower(char *s)

{

   int len = slLength(s);

   char *ns = slStringOfSize(len+1);

   int i;

   for ( i = 0; i <= len; i++ )

     ns[i] = sltolower(s[i]);

   ns[len] = 0;

   return ns;

}



char *slUpper(char *s)

{

   int len = slLength(s);

   char *ns = slStringOfSize(len+1);

   int i;

   for ( i = 0; i <= len; i++ )

     ns[i] = sltoupper(s[i]);

   ns[len] = 0;

   return ns;

}



/****************************************************

** string comparision operations

****************************************************/





int slEquals( char *s, char *s2 )		

{

    /* returns 1 if equal, 0 if not equal. */

    int len = slLength(s);

    if ( len != slLength(s2) ) return 0;

    return (memcmp(s, s2, len*CHARSIZE)==0);

}



int slEqualsAnyCase( char *s, char *s2 )		

{

    if ( slLength(s) != slLength(s2) ) return 0;

    return slContainsAnyCase(s, s2);

}



int slContains( char *s, char *s2 )		

{

  return (slFind(s, s2) != -1);

}



int slContainsAnyCase( char *s, char *s2 )		

{

  return (slFindAnyCase(s, s2) != -1);

}



int slFind( char *s, char *s2 )		

{

    return slFindFrom(s, s2, 0);

}



int slFindAnyCase( char *s, char *s2 )		

{

    return slFindAnyCaseFrom(s, s2, 0);

}



int slFindFrom( char *s, char *s2, int from )		

{

    /* return -1 for no match, starting position of match if found */

    int len;

    int len2;

    int n, m;



    if ( s == NULL || s2 == NULL ) { return -1; }



    len  = slLength(s);

    len2 = slLength(s2);    

    from = slWrapPos(s, from);



    if ( len < len2 ) return -1; /* too big */

    if ( len2 <= 0 )  return -1; /* too small */

    for ( n = from; n <= len-len2; n++ ) {

        m = 0;

        while ( s[n+m] == s2[m] && m < len2+1) {

            if ( m == len2-1 ) return n;

            m++;

        }

    }



    return -1;

}



int slRFindFrom( char *s, char *s2, int from)		

{

    /* search from end to begining of string */

    /* return -1 for no match, starting position of match if found */

    int len;

    int len2;

    int n, m;



    if ( s == NULL || s2 == NULL ) { return -1; }

    

    len  = slLength(s);

    len2 = slLength(s2);

    from = slWrapPos(s, from);

    

    if ( len < len2 ) return -1; /* too big */

    if ( len2 <= 0 )  return -1; /* too small */



    for ( n = from-len2+2; n > 0; n-- ) {

        m = 0;

        /*printf("n=%d m=%d\n", n, m);*/

        while ( s[n+m] == s2[m] && m < len2+1) {

            /*printf("s[n+m]=%d s2[m]=%d\n", s[n+m], s2[m]);

              printf("m=%d len2-1=%d\n", m, len2-1);*/



            if ( m == len2-1 ) { return n; }

            m++;

        }

    }



    return -1;

}



int slFindAnyCaseFrom( char *s, char *s2, int from )		

{

    /* return -1 for no match */

    int len;

    int len2;

    int n, m;



    if ( s == NULL || s2 == NULL ) { return -1; }

    

    len  = slLength(s);

    len2 = slLength(s2);

    from = slWrapPos(s, from);



    if ( len < len2 ) return -1; /* too big */

    if ( len2 <= 0 )  return -1; /* too small */

            

    for ( n = from; n <= len-len2; n++ ) {

        m = 0;

        while ( (sltolower(s[n+m]) == sltolower(s2[m]) && (m < len2+1)) ) {

            if ( m == len2-1 ) 

            { return n; }

            m++;

        }

    }

    return -1;

}



int slCount( char *s, char *s2 )		

{

    /* return number of occurances of s2 in s 

    ** (overlapping occurances of s2 are included) */

    int len  = slLength(s);

    int len2 = slLength(s2);

    int count = 0;

    int index = 0;

            

    if ( s == NULL || s2 == NULL ) { return 0; }



    if ( len < len2 ) return 0; /* too big */

    if ( len2 <= 0 )  return 0; /* too small */

        

    index = slFindFrom(s, s2, 0);

    while ( index != -1 ) {

      index = slFindFrom(s, s2, index+len2);

      count++;

    }

    return count;

}



char *slReplace( char *s, char *s2, char *s3 )		

{

    /* replace occurances of s2 with s3 */

    int len  = slLength(s);

    int len2 = slLength(s2);

    int len3 = slLength(s3);



    char *ns = slStringOfSize(0);

    char *sub;

    int index;

    int lastindex = 0;



    if ( s == NULL || s2 == NULL || s3 == NULL ) { return 0; }



    if ( len < len2 ) return 0; /* too big */

    if ( len2 <= 0 )  return 0; /* too small */

        

    /* not so inefficient */

    index = slFindFrom(s, s2, 0);
    if ( index == -1 ) return slCopy(s);

    while ( index != -1 ) {

      int si = index-1;
      if (si <0) { si = 0; }

      if (lastindex != si) 
      { 
        sub = slSubString(s, lastindex, si); 

        ns = slAppendAndFree(ns, sub);
        slFree(sub);

      }

      ns = slAppendAndFree(ns, s3);

      lastindex = index+len2;

      index = slFindFrom(s, s2, lastindex);

    }

    sub = slSubString(s, lastindex, len);

    ns = slAppendAndFree(ns, sub);

    slFree(sub);

    return ns;

}





/****************************************************

** private utility functions

****************************************************/





int slWrapPos(char *s, int pos)

{

   int len = slLength(s);

   if ( pos > len ) return len; 

   if ( pos < 0 ) return len + pos;

   return pos;

}


/****************************************************

** test

****************************************************/
/*
int main(int argc, const char *argv[])
{
  char *s = slReplace("some strings", "s", "" );
  printf("OpenSL TEST\n");
  printf("slReplace: ");
  if (strcmp(s, "ome tring")==1)
  { printf("ERROR: s = '%s'\n", s); }
  else 
  { printf("OK\n"); }
}
*/
