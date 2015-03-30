#include <afxwin.h>

class TextEditor : public CDialog
{
public:
	TextEditor();
	~TextEditor();

	void ChangeFile(char* filename);
	void SetText(char* newText);

private:
	afx_msg void OnSave(){ ONSAVE(); };
	afx_msg void OnSaveAndClose(){ ONSAVEANDCLOSE(); };
	afx_msg void OnCancel(){ ONCANCEL(); };

	void ONSAVE();
	void ONSAVEANDCLOSE();
	void ONCANCEL();

	char* curFilename;
	char* fileText;

	DECLARE_MESSAGE_MAP()
};