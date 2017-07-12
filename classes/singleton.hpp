#ifndef _singleton_pattern_for_unique_instance_one_process_2017_s_04
#define _singleton_pattern_for_unique_instance_one_process_2017_s_04

/* Singleton¼Ò¦¡template class */
template<class T>
class Singleton
{
	static int _refCnt;
	static T* _inst;
	Singleton(Singleton const&);
	Singleton& operator= (Singleton const&);
protected:
	Singleton();
	virtual ~Singleton();
public:
	static T* GetInstance(){
		_refCnt++;
		return _inst? _inst: (_inst = new T);
	}

	static int ReleaseInstance(){
		_refCnt--;
		if (_refCnt <0) _refCnt = 0;
		if (!_refCnt){
			delete _inst;
			_inst = NULL;
		}
		return _refCnt;
	}
};

template<class T> T* Singleton<T>::_inst = NULL;
template<class T> int Singleton<T>::_refCnt = 0;

#endif
