//******************************************************************************
// Automated platform detection
//******************************************************************************

// _WIN32 is used by
// Visual C++
#ifdef _WIN32
#define __NT__
#endif

// Define __MAC__ platform indicator
#ifdef macintosh
#define __MAC__
#endif

// Define __OSX__ platform indicator
#ifdef __APPLE__
#define __OSX__
#endif

// Define __WIN16__ platform indicator 
#ifdef _Windows_
#ifndef __NT__
#define __WIN16__
#endif
#endif

// Define Windows CE platform indicator
#ifdef WIN32_PLATFORM_HPCPRO
#define __WINCE__
#endif

#if (_WIN32_WCE == 300) // for Pocket PC
#define __POCKETPC__
#define __WINCE__
//#if (_WIN32_WCE == 211) // for Palm-size PC 2.11 (Wyvern)
//#if (_WIN32_WCE == 201) // for Palm-size PC 2.01 (Gryphon)  
//#ifdef WIN32_PLATFORM_HPC2000 // for H/PC 2000 (Galileo)
#endif