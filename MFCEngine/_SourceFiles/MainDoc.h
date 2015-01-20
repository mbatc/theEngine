#pragma once
#include <afxwin.h>

class MainDoc : public CDocument
{
	DECLARE_DYNCREATE(MainDoc)
public:
	MainDoc();
private:
	virtual BOOL OnNewDocument();
};