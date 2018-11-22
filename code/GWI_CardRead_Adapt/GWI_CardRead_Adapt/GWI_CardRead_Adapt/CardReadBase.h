#ifndef __CARD__READ__BASE__H__
#define  __CARD__READ__BASE__H__

template<class T>
class CCardReadBase
{
public:
	CCardReadBase();
	~CCardReadBase();
	T* getInstance();
private:
	T* t;
};


#endif
