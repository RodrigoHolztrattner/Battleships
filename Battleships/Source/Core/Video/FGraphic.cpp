///////////////////////////////////////////////////////////////////////////////
// Filename: FGraphic.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FGraphic.h"
#include "..\Input\FInput.h"

FGraphic::FGraphic()
{
}

FGraphic::FGraphic(const FGraphic& other)
{
}

FGraphic::~FGraphic()
{
}

bool FGraphic::Initialize(WVector2 _resolution, bool _fullScreen)
{
	bool result;

	// Set the window resolution
	m_WindowResolution = _resolution;

	// Initialize the GLFW library
	result = glfwInit();
	if (!result)
	{
		return false;
	}

	// Create the window
	m_Window = glfwCreateWindow(_resolution.x, _resolution.y, "Battleships", _fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!m_Window)
	{
		// Terminate the GLFW process
		glfwTerminate();
		
		return false;
	}

	// Make the GLFW window context current
	glfwMakeContextCurrent(m_Window);

	// Initialize the GLEW library
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		return false;
	}

	// Set the keyboard and cursors callbacks
	glfwSetKeyCallback(m_Window, KeyCallback);
	glfwSetMouseButtonCallback(m_Window, CursorCallback);

	// Create the deferred buffers
	result = CreateDeferredBuffers();
	if (!result)
	{
		return false;
	}

	return true;
}

bool FGraphic::CreateDeferredBuffers()
{
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	m_DeferredFramebuffer = 0;
	glGenFramebuffers(1, &m_DeferredFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DeferredFramebuffer);

	// The texture we're going to render to
	glGenTextures(1, &m_DeferredTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, m_DeferredTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_WindowResolution.x, m_WindowResolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// The depth buffer
	glGenRenderbuffers(1, &m_DeferredDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DeferredDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_WindowResolution.x, m_WindowResolution.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DeferredDepth);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_DeferredTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}

	// Unbind the deferred framebuffer to continue
	UnbindDeferredFramebuffer();

	return true;
}

void FGraphic::BindDeferredFramebuffer()
{
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_DeferredFramebuffer);
	glViewport(0, 0, m_WindowResolution.x, m_WindowResolution.y); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

void FGraphic::UnbindDeferredFramebuffer()
{
	// Render to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_WindowResolution.x, m_WindowResolution.y); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

void FGraphic::Shutdown()
{
	glfwTerminate();
}

/////////////
// GLOBALS //
/////////////

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputMessage input;

	/*
		- We are using a hack here because the engine itself will take place here...
		- Please remember that the engine and the core data should be at different places. DO NOT FOLLOW THIS WAY!
	*/

	// Prepare the input message
	input.type = InputTypes::Keyboard;
	input.button = key;
	input.actionID = action;
	input.longParam = 0;
	input.shortParam = 0;

	// Register the message
	FInput::RegisterInputMessage(input);
}

void CursorCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputMessage input;

	/*
	- We are using a hack here because the engine itself will take place here...
	- Please remember that the engine and the core data should be at different places. DO NOT FOLLOW THIS WAY!
	*/

	// Prepare the input message
	input.type = InputTypes::Mouse;
	input.button = button;
	input.actionID = action;
	input.longParam = 0; // Get the x mouse coordinate
	input.shortParam = 0; // Get the y mouse coordinate

	// Register the message
	FInput::RegisterInputMessage(input);
}

////////////
// GLOBAL //
////////////

// Declare the current window resolution variable
WVector2 FGraphic::m_WindowResolution = WVector2(0, 0);