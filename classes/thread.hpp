#ifndef thread_class_for_crosse_platform_adapter_common_201704_s
#define thread_class_for_crosse_platform_adapter_common_201704_s

#include <pthread.h>

typedef void* (*THREADPROC)(void*);

class Thread{

	pthread_t _handle;
	pthread_attr_t _attr;

	static void* thread_proc(void* pt){
		Thread* pThis = (Thread*)pt;
		pThis->run();
		pThis->_handle = 0;
		pthread_exit(NULL);
	};

	THREADPROC _thdprc;
	
	void ThdInit(){
		pthread_attr_init(&_attr);
	}
	
	void UnInit(){
			pthread_attr_destroy(&_attr);
	}

public:
	Thread():_thdprc(thread_proc), _handle(0){
		ThdInit();
	}
	Thread(THREADPROC thdprc):_thdprc(thdprc){
		ThdInit();
	}

	virtual ~Thread(){
		UnInit();
	}
	
	void start(){
		if (_handle) return;
		pthread_create(&_handle, NULL, _thdprc, (void*)this);
	}
	
	void stop(){
		if (_handle)
			pthread_cancel(_handle);
		_handle = 0;
	}
	
	virtual void run(){};
	
	void setcancelable(bool can){
		pthread_setcancelstate(can? PTHREAD_CANCEL_ENABLE: PTHREAD_CANCEL_DISABLE, NULL);
	}
};

#endif