#ifndef __XPTR_H__
#define __XPTR_H__


template<class T>
class XPointer
{
public:
	XPointer()
	{ _pX = NULL; }
	XPointer(T* pX)
	{ _pX = pX; }
	~XPointer()
	{ delete _pX; }
	void operator=(XPointer<T>);
private:
	T* _pX;
};


#else
	#error File already included
#endif
