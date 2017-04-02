#ifndef _singleton_pattern_for_unique_instance_one_process_2017_s_04
#define _singleton_pattern_for_unique_instance_one_process_2017_s_04

template<class T>
class Singleton
{
	static T* _inst;
	Singleton(Singleton const&);
	Singleton& operator= (Singleton const&);
protected:
	Singleton();
	virtual ~Singleton();
public:
	static T* GetInstance(){
		return _inst? _inst: (_inst = new T);
	}
};

template<class T> T* Singleton<T>::_inst = NULL;

#endif
