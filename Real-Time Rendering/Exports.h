//This header allows the ability to switch between dll and static libs
//Add the preprocessor directive REALTIME_EXPORTS if wanting to build DLL
//Add STATICLIB if going to build a static lib
//The two are mutually exclusive


#ifndef EXPORTS_H

#if defined REALTIME_EXPORTS && !defined STATICLIB
#define REALTIME_API __declspec(dllexport)
#elif !defined REALTIME_EXPORTS && !defined STATICLIB
#define REALTIME_API __declspec(dllimport)
#elif defined STATICLIB && !defined REALTIME_EXPORTS
#define REALTIME_API 
#endif

#endif // !EXPORTS_H



