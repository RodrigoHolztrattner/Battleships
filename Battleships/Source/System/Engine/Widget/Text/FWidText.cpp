///////////////////////////////////////////////////////////////////////////////
// Filename: FWidText.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FWidText.h"
#include "..\..\..\..\Core\Widget\FWidgetInput.h"
#include "..\..\..\..\Core\Video\FShaderBase.h"
#include "FWidTextShader.h"
#include "..\View\FWidView.h"

FWidText::FWidText()
{
	// Set the shader
	SetShader(FShaderBase::GetShader<FWidTextShader>());

	// Set the initial data
	m_FontFace = nullptr;
	m_TextSize = 0;
	m_TextFormat = TextFormat::Left;

	// Set the flags
	UnsetFlag(IWidget::StatusFlag::AcceptEvents);
}

FWidText::FWidText(const FWidText& other)
{
}

FWidText::~FWidText()
{
}

void FWidText::Update(float _time, WVector2 _mousePosition)
{

}

bool FWidText::Input(WidgetMessageType _input)
{
	// Do nothing
	return false;
}

bool FWidText::SetFont(FHashedString _fontName, unsigned int _fontResolution)
{
	// Get the font face from the font loader
	return m_FontFace = FFontLoader::GetFont(_fontName, _fontResolution);
}

void FWidText::SetText(const char* _text, unsigned int _textSize)
{
	m_Text = _text;
	m_TextSize = _textSize;

	// Update the glyph info
	UpdateGlyphInfo();
}

FWidText::GlyphInfo FWidText::GetGlyphInfo(unsigned int _glyphIndex)
{
	// Translate the glyph position to the widget position
	return GlyphInfo(WVector2(m_GlyphInfo[_glyphIndex].worldLocation.x + GetPosition().x, m_GlyphInfo[_glyphIndex].worldLocation.y + GetPosition().y),
		m_GlyphInfo[_glyphIndex].worldSize, m_GlyphInfo[_glyphIndex].textureCoordinates, m_GlyphInfo[_glyphIndex].glyphChar, m_GlyphInfo[_glyphIndex].lineNumber);
}

void FWidText::SetTextFormat(FWidText::TextFormat _format)
{
	// Set the text format
	m_TextFormat = _format;

	// Update the glyph info
	UpdateGlyphInfo();
}

void FWidText::UpdateGlyphInfo()
{
	// Clear the old info array
	m_GlyphInfo.Zero();

	// Zero the glyph pad
	WVector2 glyphPad = WVector2(0, 0);

	// The current line number
	int lineNumber = 0;

	// For each glyph
	for (int i = 0; i < m_Text.length(); i++)
	{
		GlyphInfo newGlyphInfo;
		WVector2 glyphPadIncrement;

		// Check if the char is a line jump
		if (m_Text[i] == '\n')
		{
			// Jump a line
			glyphPadIncrement.y = m_FontFace->glyphMaxSize;
			glyphPadIncrement.x = -glyphPad.x;

			// Increment the line number
			lineNumber++;
		}
		// Check if the char is a space
		else if (m_Text[i] == ' ')
		{
			// Increment the glyph pad
			glyphPadIncrement.y = 0;
			glyphPadIncrement.x = m_FontFace->glyphMaxSize * 0.3;
		}
		else
		{
			// Increment the glyph pad
			glyphPadIncrement.y = 0;
			glyphPadIncrement.x = m_FontFace->glyphLocation[m_Text[i]].realSize.x;
		}

		// Check if the x pad coordinate is ok
		if (glyphPad.x + glyphPadIncrement.x >= GetSize().x)
		{
			// Enforce a line jump
			glyphPad.y += m_FontFace->glyphMaxSize;
			glyphPad.x = 0;

			// Increment the line number
			lineNumber++;
		}

		// Check if the y pad coordinate is ok
		if (glyphPad.y + glyphPadIncrement.y >= GetSize().y)
		{
			// We should stop here
			glyphPad.y = 9999;
			glyphPad.x = 9999;
		}

		// Set the glyph info
		newGlyphInfo.glyphChar = m_Text[i];
		newGlyphInfo.textureCoordinates = m_FontFace->glyphLocation[m_Text[i]].textureCoordinate;
		newGlyphInfo.worldLocation = WVector2(glyphPad.x, glyphPad.y);
		newGlyphInfo.worldSize = WVector3(m_FontFace->glyphMaxSize, m_FontFace->glyphMaxSize, 1);
		newGlyphInfo.pad = glyphPadIncrement;

		// Get the glyph metrics
		FT_Glyph_Metrics glyphMetrics = m_FontFace->glyphLocation[m_Text[i]].glyphMetrics;
		float hori = (glyphMetrics.horiBearingY / (float)m_FontFace->face->units_per_EM) * m_FontFace->glyphMaxSize - m_FontFace->glyphLocation[m_Text[i]].realSize.y;
		float adv = (glyphMetrics.horiAdvance / (float)m_FontFace->face->units_per_EM);

		newGlyphInfo.worldLocation.y -= hori;

		// Set the line number
		newGlyphInfo.lineNumber = lineNumber;

		// Add the new glyph info to the glyph array
		m_GlyphInfo.Add(newGlyphInfo);

		// Increment the glyph pad
		glyphPad.x += glyphPadIncrement.x;
		glyphPad.y += glyphPadIncrement.y;
	}

	// Update the glyph format
	UpdateGlyphFormat();
}

void FWidText::UpdateGlyphFormat()
{
	// If the format is left we are done
	if (m_TextFormat == TextFormat::Left)
	{
		return;
	}

	// We need to have at last one glyph to continue
	if (!m_GlyphInfo.Size())
	{
		return;
	}

	// Ok we can use the first glyph for reference //
	
	// If the format is centralized...
	if (m_TextFormat == TextFormat::Center)
	{
		// Horizontal centralization //

		// Set the initial index
		int initialIndex = 0;

		// Set the initial line number
		int lineNumber = 0;

		// While we reach the glyph array end
		while (true)
		{
			// The old line number
			int oldLineNumber = lineNumber;

			// The line lenght
			int lineLenght = 0;

			// Set the old index
			int oldIndex = initialIndex;

			// Count the line lenght
			for (int i = initialIndex; i < m_GlyphInfo.Size(); i++)
			{
				// Check if the line number is different
				if (m_GlyphInfo[i].lineNumber != lineNumber)
				{
					GlyphInfo info = m_GlyphInfo[i];
					// Set the new line number
					lineNumber = m_GlyphInfo[i].lineNumber;

					// Set the new initial index
					initialIndex = i;

					break;
				}
				else
				{
					// Increment the line lenght
					lineLenght += m_GlyphInfo[i].pad.x;

					// Set the new initial index
					initialIndex = i + 1;
				}
			}

			// Calc the line pad
			float linePad = (GetSize().x - lineLenght) / 2.0;

			// Set the glyph positions
			for (int i = oldIndex; i < initialIndex; i++)
			{
				// Increment the glyph position
				m_GlyphInfo[i].worldLocation.x += linePad;
			}

			// Check if we reached the end
			if (initialIndex >= m_GlyphInfo.Size() || lineNumber == oldLineNumber)
			{
				// End!
				break;
			}
		}
	}
}
