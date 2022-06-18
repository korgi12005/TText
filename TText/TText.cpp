#include "TText.h"
#include "TLink.h"
#include "TStack.h"



TText::TText(TLink *first) {
	pCurr = pFirst = first;
}



void TText::GoNextLink() {
	if (pCurr->pNext != NULL) {
		st.Push(pCurr);
		pCurr = pCurr->pNext;
	}
}
void TText::GoFirstLink() {
	
		pCurr = pFirst;
		st.Clear();
	}
TLink TText::GetCurr() {
	return *pCurr;
}

TLink *TText::GetpFirst() {
	return pFirst;
}

void TText::SetCurrFalse() {
	pCurr->isFree = false;
}

void TText::GoDownLink() {
	if (pCurr->pDown != NULL) {
		st.Push(pCurr);
		pCurr = pCurr->pDown;
	}
}

void TText::GoPrevLink() {
	if (!st.IsEmpty()) {
		pCurr = st.Pop();
	}
}



void TText::InsNextLine(char *s) {
	TLink *NewLink = new TLink(s, pCurr->pNext, NULL);
	pCurr->pNext = NewLink;
}

void TText::InsNextSection(char *s) {
	TLink *NewLink = new TLink(s, NULL, pCurr->pNext);
	pCurr->pNext = NewLink;
}

void TText::InsDownLine(char *s) {
	TLink *NewLink = new TLink(s, pCurr->pDown, NULL);
	pCurr->pDown = NewLink;
}

void TText::InsDownSection(char *s) {
	TLink *NewLink = new TLink(s, NULL, pCurr->pDown);
	pCurr->pDown = NewLink;
}



void TText::DelNext() {
	if (pCurr->pNext != NULL) {
		TLink *tmp = pCurr->pNext;
		pCurr->pNext = tmp->pNext;
		delete tmp;
	}
}

void TText::DelDown() {
	if (pCurr->pDown != NULL) {
		TLink *tmp = pCurr->pDown;
		pCurr->pDown = tmp->pNext;
		delete tmp;
	}
}

char *TText::GetLine() {
	TLink *tmp = pCurr;
	char *res = tmp->str;
	return res;
}

void TText::SetLine(char *s) {
	strncpy_s(pCurr->str, s, 80);
}

TLink *TText::ReadRec(ifstream& file) {
	TLink* pHead, * p, * tmp;
	pHead = p = NULL;
	char str[81];
	while (!file.eof()) {
		file.getline(str, 80, '\n');
		if (str[0] == '}') { break; }
		else if (str[0] == '{') {
			p->pDown = ReadRec(file);
		}
		else
		{
			tmp = new TLink(str);
			if (pHead == NULL) {
				pHead = p = tmp;
			}
			else
			{
				p->pNext = tmp;
				p = p->pNext;
			}

		}
		if (!p->pDown) {}

	}
	return pHead;
}

void TText::Read(char *fn) {
	ifstream ifs(fn);
	if (fn)
		pCurr = pFirst = ReadRec(ifs);
	if (pFirst == NULL)
		throw "ошибка чтения";
}

void TText::PrintText(TLink *tmp) {
	if (tmp != NULL) {
		if (tmp == pCurr) {	
			cout << "-> ";	
		}
		else {
			cout << "   ";
		}

		for (int i = 0; i < level; i++)
			cout << "   ";

		cout << tmp->str << endl;
		level++;
		PrintText(tmp->pDown);
		level--;
		PrintText(tmp->pNext);
	}
}

void TText::Print() {
	level = 0;
	PrintText(pFirst);
}




void TText::Reset() {
	pCurr = pFirst;

	while (!st.IsEmpty())
		st.Pop();

	st.Push(pCurr);

	if (pCurr->pNext != NULL)
		st.Push(pCurr->pNext);
	if (pCurr->pDown != NULL)
		st.Push(pCurr->pDown);
}

bool TText::IsEnd() {
	return st.IsEmpty();
}

void TText::GoNext() {
	pCurr = st.Pop();

	if (pCurr != pFirst) {
		if (pCurr->pNext != NULL)
			st.Push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			st.Push(pCurr->pDown);
	}
}


void TText::WriteRec(TLink* tmp, ofstream& f) {
	f << tmp->str << endl;

	if (tmp->pDown != NULL) {
		f << "{\n";
		WriteRec(tmp->pDown, f);
		f << "}\n";
	}

	if (tmp->pNext != NULL)
		WriteRec(tmp->pNext, f);
}

void TText::Write(char* name) {
	ofstream ofs(name);
	WriteRec(pFirst, ofs);
	cout << "текс сохнанен в файл - " <<name<< endl;
}