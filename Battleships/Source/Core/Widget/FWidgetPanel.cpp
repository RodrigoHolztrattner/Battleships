///////////////////////////////////////////////////////////////////////////////
// Filename: FWidgetPanel.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FWidgetPanel.h"

FWidgetPanel::FWidgetPanel()
{
	// Set the initial data
	m_Root = nullptr;
}

FWidgetPanel::FWidgetPanel(const FWidgetPanel& other)
{
}

FWidgetPanel::~FWidgetPanel()
{
}

bool FWidgetPanel::Initialize(FGraphic* _graphicContext)
{
	// Create the root widget
	m_Root = new IWidget;
	if (m_Root == nullptr)
	{
		return false;
	}
	
	// Set the parent to be null
	m_Root->SetParent(nullptr);

	// Set the position and size to match the screen coordinates
	m_Root->SetLayout(IWidget::LayoutLocationHeight::Top, IWidget::LayoutLocationWidth::Left, IWidget::LayoutSize::Absolute);
	m_Root->SetPosition(WVector2(0, 0));
	m_Root->SetSize(_graphicContext->GetWindowResolution());

	// Set the root flags
	m_Root->SetFlag(IWidget::StatusFlag::Visible);
	m_Root->SetFlag(IWidget::StatusFlag::AcceptEvents);
	m_Root->UnsetFlag(IWidget::StatusFlag::Renderable);
	m_Root->UnsetFlag(IWidget::StatusFlag::Movable);

	return true;
}

void FWidgetPanel::UpdatePanel(float _time)
{
	// Start the update with the main root
	UpdatePanelHelper(m_Root, _time, WVector2(0, 0));
}

void FWidgetPanel::RenderPanel()
{
	// Start the render method with the main root
	RenderPanelHelper(m_Root, WVector2(0, 0));
}

void FWidgetPanel::UpdatePanelHelper(IWidget* _widget, float _time, WVector2 _mousePosition)
{
	// Check if this widget is visible
	if (!_widget->CheckFlag(IWidget::StatusFlag::Visible))
	{
		// Ignore
		return;
	}

	// Check if this widget is updateable
	if (!_widget->CheckFlag(IWidget::StatusFlag::AcceptEvents))
	{
		// Ignore
		return;
	}

	// Update this widget
	_widget->Update(_time, _mousePosition);

	// Get the child array
	TArray<IWidget*>* childArray = _widget->GetChildArray();

	// Call the update function for each child
	for (int i = 0; i < childArray->Size(); i++)
	{
		// Update this child widget
		UpdatePanelHelper((*childArray)[i], _time, _mousePosition);
	}
}

void FWidgetPanel::RenderPanelHelper(IWidget* _widget, WVector2 _mousePosition)
{
	// Check if this widget is visible
	if (!_widget->CheckFlag(IWidget::StatusFlag::Visible))
	{
		// Ignore
		return;
	}

	// Check if this widget is renderable
	if (_widget->CheckFlag(IWidget::StatusFlag::Renderable))
	{
		// Render this widget
		_widget->Render(_mousePosition);
	}

	// Get the child array
	TArray<IWidget*>* childArray = _widget->GetChildArray();

	// Call the render function for each child
	for (int i = 0; i < childArray->Size(); i++)
	{
		// Render this child widget
		RenderPanelHelper((*childArray)[i], _mousePosition);
	}
}