#include <afxwin.h>

#include "resource.h"
#include "TextEditor.h"

BEGIN_MESSAGE_MAP(TextEditor,CDialog)
	ON_COMMAND(IDC_TEXTEDITOR_SAVE, OnSave)
	ON_COMMAND(IDC_TEXTEDITOR_SAVECLOSE, OnSaveAndClose)
	ON_COMMAND(IDCANCEL, OnCancel)
END_MESSAGE_MAP()

TextEditor::TextEditor():
	curFilename(NULL),
	fileText(NULL)
{
	Create(IDD_TEXTEDITOR);
	ShowWindow(SW_SHOW);
}

TextEditor::~TextEditor()
{

}

void TextEditor::ChangeFile(char* filename)
{
	int strLen = strlen(filename);

	if (curFilename)
		delete [] curFilename;
	curFilename = new char[strLen];

	strcpy(curFilename, filename);

	FILE* pfile = fopen(curFilename, "r");

		fseek(pfile, 0, SEEK_END);
		int fileLen = ftell(pfile);
		rewind(pfile);

		if (fileLen != 0)
		{
			fileText = new char[fileLen];
			ZeroMemory(fileText, sizeof(char)*fileLen );
			fread(fileText, sizeof(char), fileLen, pfile);
		}
		else
		{
			fileText = new char[1];
			fileText[0] = '\0';
		}

	fclose(pfile);

	int FileNameIndex = 0;
	for (int i = strLen; i >= 0; i--)
	{
		if (filename[i - 1] == '\\')
		{
			break;
			FileNameIndex = i;
		}
	}

	CEdit* t_name = (CEdit*)GetDlgItem(IDC_TEXTEDITOR_FILENAME);
	t_name->SetWindowTextA(&filename[FileNameIndex]);

	SetText(fileText);
}

void TextEditor::SetText(char* newText)
{
	CEdit* t_edit = (CEdit*)GetDlgItem(IDC_TEXTEDITOR);
	t_edit->SetWindowTextA(newText);

	int strLen = strlen(newText);

	if (strLen != 0)
	{
		if (fileText)
			delete fileText;
		fileText = new char[strLen];

		for (int i = 0; i < strLen; i++)
		{
			fileText[i] = newText[i];
		}
	}
	else
	{
		if (fileText)
			delete fileText;
		fileText = new char[1];
		fileText[0] = '\0';
	}
}


void TextEditor::ONSAVE()
{
	CEdit* t_edit = (CEdit*)GetDlgItem(IDC_TEXTEDITOR);
	int textLen = t_edit->GetWindowTextLengthA() + 1;
	char* temp = new char[textLen];

	t_edit->GetWindowTextA(temp, textLen);
	SetText(temp);

	FILE* pfile = fopen(curFilename, "w");

	fprintf(pfile, "%s", fileText);

	fclose(pfile);
}

void TextEditor::ONSAVEANDCLOSE()
{
	ONSAVE();
	ONCANCEL();
}
void TextEditor::ONCANCEL()
{
	this->~TextEditor();
}