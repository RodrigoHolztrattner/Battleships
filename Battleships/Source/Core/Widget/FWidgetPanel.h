////////////////////////////////////////////////////////////////////////////////
// Filename: FWidgetPanel.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FWidgetPanel_H_
#define _FWidgetPanel_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Video\FGraphic.h"
#include "IWidget.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FWidgetPanel
////////////////////////////////////////////////////////////////////////////////
class FWidgetPanel
{
private:

	// Widget is a friend class
	friend IWidget;

public:
	FWidgetPanel();
	FWidgetPanel(const FWidgetPanel&);
	~FWidgetPanel();

	// Initialize the widget panel
	bool Initialize(FGraphic* _graphicContext);

	// Update the main panel
	void UpdatePanel(float _time);

	// Render all widget inside the main panel
	void RenderPanel();

private:

	// Return the root widget
	IWidget* GetRoot()
	{
		return m_Root;
	}

	// The update panel helper function
	void UpdatePanelHelper(IWidget* _widget, float _time, WVector2 _mousePosition);

	// The render panel helper function
	void RenderPanelHelper(IWidget* _widget, WVector2 _mousePosition);

private:

	// The root widget
	IWidget* m_Root;
};

#endif
