#pragma once
#include <iostream>
#include "TStack.h"
#include <fstream>
#include "FontColor.h"

using namespace std;
class TLink;
class TText;




class TText {
	TLink *pFirst, *pCurr;
	TStack<TLink *> st;
	int level;
public:
	TText() {}
	TText(TLink *first);



	TLink GetCurr();
	TLink *GetpFirst();
	void SetCurrFalse();
	void GoFirstLink();
	
	void GoNextLink();
	void GoDownLink();
	void GoPrevLink();

	void InsNextLine(char *s);
	void InsNextSection(char *s);
	void InsDownLine(char *s);
	void InsDownSection(char *s);

	void DelNext();
	void DelDown();

	char *GetLine();
	void SetLine(char *s);

	TLink *ReadRec(ifstream& file);
	void Read(char *fn);

	void PrintText(TLink *tmp);
	void Print();

	void WriteRec(TLink *tmp, ofstream& f);
	void Write(char *name);

	

	void Reset();
	bool IsEnd();
	void GoNext();
};