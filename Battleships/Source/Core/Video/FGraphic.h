////////////////////////////////////////////////////////////////////////////////
// Filename: FGraphic.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FGraphic_H_
#define _FGraphic_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////

/* Base */
#include <iostream>
#include "string"
// #include <windows.h>
#include <math.h>

/* Opengl (GLEW / GLFW) */
#define GLEW_STATIC 
#define GLFW_STATIC
#include <GLEW\glew.h>
#include <GLFW/glfw3.h>

/* */
#include "..\Support\Callback\WCallback.h"
#include "..\Support\Math\WMath.h"

/////////////
// DEFINES //
/////////////

// A ID handle type defined to be used by all opengl IDs
#define IDHANDLE unsigned int

////////////////////////////////////////////////////////////////////////////////
// Class name: FGraphic
////////////////////////////////////////////////////////////////////////////////
class FGraphic
{
public:

public:
	FGraphic();
	FGraphic(const FGraphic&);
	~FGraphic();

	// Initialize the opengl context
	bool Initialize(WVector2 _resolution, bool _fullScreen);

	// Create the deferred buffers
	bool CreateDeferredBuffers();

	// Bind the deferred framebuffer
	void BindDeferredFramebuffer();

	// Unbind the deferred framebuffer
	void UnbindDeferredFramebuffer();

	// Shutdown the opengl context
	void Shutdown();

	// Return a reference to the main window
	GLFWwindow* GetWindowReference()
	{
		return m_Window;
	}

	// Return the window resolution
	WVector2 GetWindowResolution()
	{
		return m_WindowResolution;
	}

	// Return the deferred texture
	IDHANDLE GetDeferredTexture()
	{
		return m_DeferredTexture;
	}

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL Return the window resolution
	static WVector2 GetCurrentResolution()
	{
		return m_WindowResolution;
	}

private:

	// The engine window
	GLFWwindow* m_Window;

	// The deferred framebuffer
	IDHANDLE m_DeferredFramebuffer;

	// The deferred texture
	IDHANDLE m_DeferredTexture;

	// The deferred depth buffer
	IDHANDLE m_DeferredDepth;

	////////////
	// GLOBAL //
	////////////

	// The current window resolution
	static WVector2 m_WindowResolution;
};

// The keyboard and cursor callbacks
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorCallback(GLFWwindow* window, int button, int action, int mods);

#endif
