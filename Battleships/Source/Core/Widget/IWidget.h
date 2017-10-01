////////////////////////////////////////////////////////////////////////////////
// Filename: IWidget.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IWidget_H_
#define _IWidget_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Video\FGraphic.h"
#include "..\Containers\Array\TArray.h"
#include "..\Support\Math\WMath.h"

/////////////
// DEFINES //
/////////////

// We know the widget panel and the widget input classes
class FWidgetPanel;
class FWidgetInput;

// We know the Shader Base type
class FShaderBase;

// We know the widget message type
struct WidgetMessageType;

////////////////////////////////////////////////////////////////////////////////
// Class name: IWidget
////////////////////////////////////////////////////////////////////////////////
class IWidget
{
protected:

	// Widget panel and widget input are friend classes
	friend FWidgetPanel;
	friend FWidgetInput;

	// All the status flags
	enum StatusFlag
	{
		Visible			= 1 << 0, // If it's not visible, we ignore all other flags and just dont do any processing for the widget
		Renderable		= 1 << 1, // If it's not renderable, we will ignore this widget at the render stage
		Movable			= 1 << 2, // If the user can move the widget position (currently not implemented)
		AcceptEvents	= 1 << 3, // If we should process input events for this widget and if it is updateable
	};

public:

	// Pre-declare the function that return the root widget (so we can use it inside the Create() method) //

	// <GLOBAL> Return the root widget
	static IWidget* RootWidget();

	// Pre-declare the function that return the root widget (so we can use it inside the Create() method) //

	// Create a instance of this object and return a ptr to it
	template <typename WidgetClass>
	static WidgetClass* Create(IWidget* _parent = IWidget::RootWidget())
	{
		// Create a new widget
		WidgetClass* newWidget = new WidgetClass;

		// Set the parent
		newWidget->SetParent(_parent);

		// Call the log class
		// LEntityLog::PrintEntityCreated(newWidget);

		return newWidget;
	}

	// Release this object (mark it for deletion)
	virtual void Release()
	{
		// If this widget has a parent...
		if (m_Parent)
		{
			// Remove this object from the parent child array
			m_Parent->RemoveChild(this);

			// Delete this object
			delete this;
		}
	}

	// The update virtual functions
	virtual void Update(float _time, WVector2 _mousePosition){};

	// The input method
	virtual bool Input(WidgetMessageType _input);

	// The render function
	virtual void Render(WVector2 _mousePosition);

	// Check if a given flag is active
	bool CheckFlag(IWidget::StatusFlag _flag)
	{
		return (m_StatusFlags & _flag);
	}

protected:

	// The constructor and destructor are protected because we can only create or delete objects using the Create() or Release() functions
	IWidget();
	~IWidget();

	// Copy constructor is private because we cant share directly data (only ptrs)
	IWidget(const IWidget&);

protected:

	// Return the parent
	IWidget* GetParent()
	{
		return m_Parent;
	}

	// Return the child array
	TArray<IWidget*>* GetChildArray()
	{
		return &m_ChildArray;
	}

	// Add a child widget
	void AddChild(IWidget* _child)
	{
		m_ChildArray.Add(_child);
	}

	// Remove a child widget
	void RemoveChild(IWidget* _child)
	{
		// Find the child
		for (int i = 0; i < m_ChildArray.Size(); i++)
		{
			// Check if is the one that we are looking
			if (m_ChildArray[i] == _child)
			{
				// Remove from the array
				m_ChildArray.Remove(i);

				break;
			}
		}
	}

	// Set the shader that will render this widget
	void SetShader(FShaderBase* _shader)
	{
		m_Shader = _shader;
	}
	
public:

	// Set a flag
	void SetFlag(IWidget::StatusFlag _flag)
	{
		m_StatusFlags = (IWidget::StatusFlag)(m_StatusFlags | _flag);
	}

	// Remove a flag
	void UnsetFlag(IWidget::StatusFlag _flag)
	{
		m_StatusFlags = (IWidget::StatusFlag)(m_StatusFlags & ~_flag);
	}

private:

	// Set the parent
	void SetParent(IWidget* _parent)
	{
		// Set the parent
		m_Parent = _parent;

		// Add to the parent child array
		if (m_Parent != nullptr) m_Parent->AddChild(this);
	}

private:

	// The parent object (null if this is the root)
	IWidget* m_Parent;

	// The child array
	TArray<IWidget*> m_ChildArray;

	// The status flags
	StatusFlag m_StatusFlags;

	// The shader that will render this widget
	FShaderBase* m_Shader;
	
public:

	//////////////
	// 2D WORLD //
	//////////////

	// The base resolution that we will set the Widget world
	static const unsigned int BaseResolutionWidth = 1600;
	static const unsigned int BaseResolutionHeight = 900;

	// The position padding value
	static const unsigned int PositionPadding = 10;

	enum class Layout
	{
		Normal,					
		ParentProportional,		// The values are proportional from parent size
		ScreenProportional,		// The values are proportional from the screen
		WidthLocked,			// The width will not be affected by different resolutions
		HeightLocked			// The height will not be affected by different resolutions
	};

	// The layout types
	enum class LayoutLocationWidth
	{
		Absolute,				// The value is set regardless of the resolution
		Right,					// Right aligned
		Left,					// Left aligned
		Center,					// Center aligned
		Proportional			// Screen proportional
	};
	enum class LayoutLocationHeight
	{
		Absolute,				// The value is set regardless of the resolution
		Top,					// Top aligned
		Bottom,					// Bottom aligned
		Center,					// Center aligned
		Proportional			// Screen proportional
	};
	enum class LayoutSize
	{
		Absolute,				// The values are set regardless of the resolution
		WidthProportional,		// The height will not change regardless of the resolution
		HeightProportional,		// The width will not change regardless of the resolution
		Proportional			// Screen proportional
	};

	// Set the layout type
	virtual void SetLayout(LayoutLocationHeight _layoutHeight = LayoutLocationHeight::Absolute, LayoutLocationWidth _layoutWidth = LayoutLocationWidth::Absolute, LayoutSize _layoutSize = LayoutSize::Absolute, WVector2 _positionPadding = WVector2(PositionPadding, PositionPadding));

	// Set the position
	virtual void SetPosition(WVector2 _position);

	// Set the size (the base value is relative to the value that is proportional)
	virtual void SetSize(WVector2 _size, float _base = 0);

	// Set the rotation
	virtual void SetRotation(float _angle)
	{
		m_Rotation = _angle;
	}

	// Return the position
	WVector2 GetPosition();

	// Return the size
	WVector2 GetSize()
	{
		return m_Size;
	}

	// Return the rotation
	float GetRotation()
	{
		return m_Rotation;
	}

protected:

	// The screen position
	WVector2 m_ScreenPosition;

	// The widget size
	WVector2 m_Size;

	// The rotation angle
	float m_Rotation;

	// The layouts
	LayoutLocationWidth m_LayoutWidth;
	LayoutLocationHeight m_LayoutHeight;
	LayoutSize m_LayoutSize;

	// The current position padding
	WVector2 m_PositionPadding;

	Layout m_Layout;

protected:

	///////////////
	// CALLBACKS //
	///////////////

	// When the layout changes
	virtual void OnLayoutChange(){};

public:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Initialize the widget system
	static bool InitializeWidgetSystem(FGraphic* _graphicContext);

	// <GLOBAL> Update all widgets
	static void UpdateWidgets(float _time);

	// <GLOBAL> Render all widgets
	static void RenderWidgets();

private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The widget panel and input objects
	static FWidgetPanel* m_WidgetPanel;
	static FWidgetInput* m_WidgetInput;
};

#endif
