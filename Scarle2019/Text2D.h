#pragma once
#include "GameObject2D.h"
#include <string>

//GEP:: Draws a line of text to the screen
// DirectXTK12 wiki page: https://github.com/Microsoft/DirectXTK12/wiki/Drawing-text

class Text2D :
	public GameObject2D
{
public:
	Text2D(string _text);
	virtual ~Text2D();

	void SetText(string _text);
	string GetText() { return m_text; }
	XMFLOAT4 GetSize() { return size; }

	//place the origin at the middle of the string
	void CentreOrigin();

	void Render();
	virtual void Reset() override {};

protected:

	string m_text;
	std::wstring m_wText;
	bool m_dirtyOrigin = false;

	GameFilepaths m_filepath;
	XMFLOAT4 size;    //the float where we copy the v2 vector members

};

