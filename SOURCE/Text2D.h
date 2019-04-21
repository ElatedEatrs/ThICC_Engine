#pragma once
#include "pch.h"
#include "GameObject2D.h"
#include "GameFilepaths.h"
#include "RenderData.h"
#include "DeviceData.h"
#include <string>

class Text2D :
	public GameObject2D
{
public:
	Text2D(std::string _text);
	virtual ~Text2D() {};

	void SetText(std::string _text);
	std::string GetText() { return m_text; }

	Vector2 GetSize() { return Locator::getRD()->m_2dFont->MeasureString(m_wText.c_str()); }
	void CentreOrigin() override {};

	void Render();

protected:
	std::string m_text;
	std::wstring m_wText;
};

