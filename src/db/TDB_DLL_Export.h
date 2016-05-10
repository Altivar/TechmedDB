#ifndef TDB_DLL_EXPORT
#define TDB_DLL_EXPORT

#if TDB_DLL
	#if TDB_DLL_BUILD
		#define DLLEXPORT __declspec(dllexport)
	#else
		#define DLLEXPORT __declspec(dllimport)
	#endif
#endif


#endif // DLL_EXPORT