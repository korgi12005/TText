#include "TText.h"
#include "TLink.h"
TLink::TLink(char* _str, TLink* pN, TLink* pD) {
	pNext = pN;
	pDown = pD;
	isFree = true;
	if (_str == NULL)
		str[0] = '\0';
	else
		strncpy_s(str, _str, 80);
}



void* TLink::operator new(size_t s) {
	TLink* tmp = mem.pFree;

	if (tmp == NULL) {
		throw "pFree is NULL";
	}
	else {
		mem.pFree = mem.pFree->pNext;
	}
	return (void*)tmp;
}

void TLink::operator delete(void* p) {
	TLink* tmp = (TLink*)p;
	tmp->pNext = mem.pFree;
	mem.pFree = tmp;
}

void TLink::InitMem(size_t s) {
	mem.pFirst = (TLink*) new char[sizeof(TLink) * s];
	mem.pFree = mem.pFirst;
	mem.pLast = mem.pFirst + (s - 1);
	TLink* pLink = mem.pFirst;


	for (int i = 0; i < s - 1; i++) {
		pLink->str[0] = '\0';
		pLink->pNext = pLink + 1;
		pLink++;
	}
	pLink->pNext = NULL;
}

void TLink::MemCleaner(TText& txt) {
	for (txt.Reset(); !txt.IsEnd(); txt.GoNext()) {

		txt.SetCurrFalse();
	}

	TLink* tmp = mem.pFree;
	while (tmp != NULL) {
		tmp->isFree = false;
		tmp = tmp->pNext;
	}

	tmp = mem.pFirst;
	while (tmp != mem.pLast) {
		if (tmp->isFree) {
			delete tmp;
		}
		tmp++;
	}
}



void TLink::SetStr(char* _str) {
	strncpy_s(str, _str, 80);
}

