#include "MainDoc.h"

MainDoc::MainDoc()
{

}

BOOL MainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}