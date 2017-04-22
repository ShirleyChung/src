#ifndef thread_class_for_crosse_platform_adapter_common_201704_s
#define thread_class_for_crosse_platform_adapter_common_201704_s

#include <pthread.h>

typedef void* (*THREADPROC)(void*);

template<class T>
class Thread{

	pthread_t _threadhandle;
	
	static void* thread_proc(void* pt){
		T* pThis = (T*)pt;
		pThis->run();
	};
	
	THREADPROC _thdprc;
	
public:
	Thread():_thdprc(thread_proc){}
	Thread(THREADPROC thdprc):_thdprc(thdprc){}
		
	virtual ~Thread();
	
	void run();
};

#endif