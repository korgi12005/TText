#include "TText.h";

struct  TMemory{
	TLink* pFirst;
	TLink* pLast;
	TLink* pFree;
	friend class TLink;
};

class TLink {
public:
	char str[80];
	TLink* pNext, * pDown;
	bool isFree;
	static TMemory mem;
	
	TLink(char* _str = NULL, TLink* pN = NULL, TLink* pD = NULL);
	~TLink() {}

	void* operator new(size_t s);
	void operator delete(void* p);

	static void InitMem(size_t s);
	static void MemCleaner(TText& txt);

	void SetStr(char* _str = "\0");
};
