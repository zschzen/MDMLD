#ifndef MDMLD_MDAPI_H
#define MDMLD_MDAPI_H

#ifdef MD_SHARED
#if defined _WIN32 || defined __CYGWIN__
    #ifdef dura2d_EXPORTS
      #ifdef __GNUC__
        #define MD_API __attribute__ ((dllexport))
      #else
        #define MD_API __declspec(dllexport)
      #endif
    #else
      #ifdef __GNUC__
        #define MD_API __attribute__ ((dllimport))
      #else
        #define MD_API __declspec(dllimport)
      #endif
    #endif
  #else
    #if __GNUC__ >= 4
      #define MD_API __attribute__ ((visibility ("default")))
    #else
      #define MD_API
    #endif
  #endif
#else
#define MD_API
#endif

#endif //MDMLD_MDAPI_H

