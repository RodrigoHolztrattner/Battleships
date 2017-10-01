///////////////////////////////////////////////////////////////////////////////
// Filename: IWidget.cpp
///////////////////////////////////////////////////////////////////////////////
#include "IWidget.h"
#include "FWidgetPanel.h"
#include "FWidgetInput.h"
#include "..\Video\FGraphic.h"
#include "..\Input\FInput.h"
#include "..\Video\FShaderBase.h"

IWidget::IWidget()
{
	// Set the initial data
	m_Parent = nullptr;
	m_Shader = nullptr;
	m_StatusFlags = (IWidget::StatusFlag)0;
	m_ScreenPosition = WVector2(0, 0);
	m_Size = WVector2(0, 0);
	m_Rotation = 0;
	m_Layout = Layout::Normal;

	// Set the initial flags
	SetFlag(IWidget::StatusFlag::AcceptEvents);
	SetFlag(IWidget::StatusFlag::Visible);
	SetFlag(IWidget::StatusFlag::Renderable);
	UnsetFlag(IWidget::StatusFlag::Movable);
}

IWidget::IWidget(const IWidget& other)
{
}

IWidget::~IWidget()
{
}

bool IWidget::Input(WidgetMessageType _input)
{
	// Do nothing
	return false;
}

void IWidget::Render(WVector2 _mousePosition)
{
	if (m_Shader != nullptr) m_Shader->AddObject(this);
}

//////////////
// 2D WORLD //
//////////////

void IWidget::SetLayout(LayoutLocationHeight _layoutHeight, LayoutLocationWidth _layoutWidth, LayoutSize _layoutSize, WVector2 _positionPadding)
{
	// Set the layouts
	m_LayoutWidth = _layoutWidth;
	m_LayoutHeight = _layoutHeight;
	m_LayoutSize = _layoutSize;

	// Set the position padding
	m_PositionPadding = _positionPadding;

	///////////
	// WIDTH //
	///////////

	// Check the width layout type
	switch (m_LayoutWidth)
	{
		// Left aligned
		case LayoutLocationWidth::Left:
		{
			// Left is always zero + padding
			m_ScreenPosition.x = 0 + _positionPadding.x;

			break;
		}

		// Right aligned
		case LayoutLocationWidth::Right:
		{
			// For Right we need to consider the screen resolution
			m_ScreenPosition.x = FGraphic::GetCurrentResolution().x - m_Size.x - _positionPadding.y;

			break;
		}

		// Center aligned
		case LayoutLocationWidth::Center:
		{
			// For center we need to consider the size and the screen resolution
			m_ScreenPosition.x = (FGraphic::GetCurrentResolution().x / 2) - (m_Size.x / 2);

			break;
		}
	}

	////////////
	// HEIGHT //
	////////////

	// Check the height layout type
	switch (m_LayoutHeight)
	{
		// Left aligned
		case LayoutLocationHeight::Top:
		{
			// Top is always zero + padding
			m_ScreenPosition.y = 0 + _positionPadding.y;

			break;
		}

		// Right aligned
		case LayoutLocationHeight::Bottom:
		{
			// For bottom we need to consider the screen resolution
			m_ScreenPosition.y = FGraphic::GetCurrentResolution().y - m_Size.y - _positionPadding.y;

			break;
		}

		// Center aligned
		case LayoutLocationHeight::Center:
		{
			// For center we need to consider the size and the screen resolution
			m_ScreenPosition.y = (FGraphic::GetCurrentResolution().y / 2) - (m_Size.y / 2);

			break;
		}
	}

	// Call the on layout change
	OnLayoutChange();
}

void IWidget::SetPosition(WVector2 _position)
{
	///////////
	// WIDTH //
	///////////

	// Check if the layout is absolute or proportional, else, set to absolute (standard)
	if (m_LayoutWidth != LayoutLocationWidth::Absolute && m_LayoutWidth != LayoutLocationWidth::Proportional)
	{
		m_LayoutWidth = LayoutLocationWidth::Absolute;
	}

	// Check the width layout type
	switch (m_LayoutWidth)
	{
		// The value is set regardless of the resolution
		case LayoutLocationWidth::Absolute:
		{
			// Just set the absolute position
			m_ScreenPosition.x = _position.x;

			break;
		}

		// Screen proportional
		case LayoutLocationWidth::Proportional:
		{
			// Check if we have a valid parent
			if (m_Parent)
			{
				// Proportional we need to consider the screen resolution
				m_ScreenPosition.x = m_Parent->GetPosition().x + m_Parent->GetSize().x * _position.x;
			}
			else
			{
				// Proportional we need to consider the screen resolution
				m_ScreenPosition.x = FGraphic::GetCurrentResolution().x * _position.x;
			}

			break;
		}			
	}

	////////////
	// HEIGHT //
	////////////

	// Check if the layout is absolute or proportional, else, set to absolute (standard)
	if (m_LayoutHeight != LayoutLocationHeight::Absolute && m_LayoutHeight != LayoutLocationHeight::Proportional)
	{
		m_LayoutHeight = LayoutLocationHeight::Absolute;
	}

	// Check the height layout type
	switch (m_LayoutHeight)
	{
		// The value is set regardless of the resolution
		case LayoutLocationHeight::Absolute:
		{
			// Just set the absolute position
			m_ScreenPosition.y = _position.y;

			break;
		}

		// Screen proportional
		case LayoutLocationHeight::Proportional:
		{
			// Check if we have a valid parent
			if (m_Parent)
			{
				// Proportional we need to consider the screen resolution
				m_ScreenPosition.y = m_Parent->GetPosition().y + m_Parent->GetSize().y * _position.y;
			}
			else
			{
				// Proportional we need to consider the screen resolution
				m_ScreenPosition.y = FGraphic::GetCurrentResolution().y * _position.y;
			}

			break;
		}
	}

	// Call the on layout change
	OnLayoutChange();
}

void IWidget::SetSize(WVector2 _size, float _base)
{
	//////////
	// SIZE //
	//////////

	// Check the layout type
	switch (m_LayoutSize)
	{
		// The values are set regardless of the resolution
		case LayoutSize::Absolute:
		{
			// Just set the size normally
			m_Size = _size;

			break;
		}

		// The height will not change regardless of the resolution
		case LayoutSize::WidthProportional:
		{
			// Check if we have a base value
			if (_base)
			{
				// Set the absolute size
				m_Size.y = (_size.y * FGraphic::GetCurrentResolution().x) / _base;
			}
			else
			{
				// Set the absolute size
				m_Size.y = _size.y;
			}


			// Calc the proportional size
			m_Size.x = Lerp(0.0f, FGraphic::GetCurrentResolution().x, _size.x);
			
			break;
		}

		// The width will not change regardless of the resolution
		case LayoutSize::HeightProportional:
		{
			// Check if we have a base value
			if (_base)
			{
				// Set the absolute size
				m_Size.x = (_size.x * FGraphic::GetCurrentResolution().y) / _base;
			}
			else
			{
				// Set the absolute size
				m_Size.x = _size.x;
			}

			// Calc the proportional size
			m_Size.y = Lerp(0.0f, FGraphic::GetCurrentResolution().y, _size.y);

			break;
		}

		// Screen proportional
		case LayoutSize::Proportional:
		{
			// Check if we have a valid parent
			if (m_Parent)
			{
				// Proportional we need to consider the screen resolution
				m_Size.x = Lerp(0.0f, m_Parent->GetSize().x, _size.x);
				m_Size.y = Lerp(0.0f, m_Parent->GetSize().y, _size.y);
			}
			else
			{
				// Calc the proportional size
				m_Size.x = Lerp(0.0f, FGraphic::GetCurrentResolution().x, _size.x);
				m_Size.y = Lerp(0.0f, FGraphic::GetCurrentResolution().y, _size.y);
			}

			break;
		}

	}

	// Re-set the layout because changing the size maybe affect the position scheme (just use the current values for the layout, we need the recalculations only)
	SetLayout(m_LayoutHeight, m_LayoutWidth, m_LayoutSize, m_PositionPadding);
}

WVector2 IWidget::GetPosition()
{
	// return WVector2(m_ScreenPosition.x - FGraphic::GetCurrentResolution().x/2 + m_Size.x, m_ScreenPosition.y - FGraphic::GetCurrentResolution().y/2 + m_Size.y);
	return m_ScreenPosition;
}

////////////
// GLOBAL //
////////////

// Declare the widget panel and widget input variables
FWidgetPanel* IWidget::m_WidgetPanel = nullptr;
FWidgetInput* IWidget::m_WidgetInput = nullptr;

bool IWidget::InitializeWidgetSystem(FGraphic* _graphicContext)
{
	// Create the widget panel
	m_WidgetPanel = new FWidgetPanel;
	if (m_WidgetPanel == nullptr)
	{
		return false;
	}

	// Create the widget input
	m_WidgetInput = new FWidgetInput;
	if (m_WidgetInput == nullptr)
	{
		return false;
	}

	// Initialize the widget panel
	if (!m_WidgetPanel->Initialize(_graphicContext))
	{
		return false;
	}

	// Initialize the widget input
	if (!m_WidgetInput->Initialize())
	{
		return false;
	}

	return true;
}

void IWidget::UpdateWidgets(float _time)
{
	// Process the input for all widget
	m_WidgetInput->ProcessInput(m_WidgetPanel->GetRoot());

	// Update the panel
	m_WidgetPanel->UpdatePanel(_time);
}

void IWidget::RenderWidgets()
{
	// Render the panel
	m_WidgetPanel->RenderPanel();
}

IWidget* IWidget::RootWidget()
{
	return m_WidgetPanel->GetRoot();
}