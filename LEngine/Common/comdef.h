#ifndef __COMDEF_H__
#define __COMDEF_H__

#ifdef CountOf
  #error CountOf already defined
#else
  #define CountOf(arr) sizeof(arr)/sizeof(arr[0])
#endif

#else
  #error File already included
#endif

