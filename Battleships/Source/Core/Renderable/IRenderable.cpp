///////////////////////////////////////////////////////////////////////////////
// Filename: IRenderable.cpp
///////////////////////////////////////////////////////////////////////////////
#include "IRenderable.h"

IRenderable::IRenderable(FActor* _owner, FShaderBase* _shader)
{
	// Set the owner and the shader
	m_Owner = _owner;
	m_Shader = _shader;

	// Set the deletion mark to false
	m_DeletionMark = false;

	// Set to ignore collision
	m_IgnoreCollision = true;
}

IRenderable::IRenderable(const IRenderable& other)
{
}

IRenderable::~IRenderable()
{
}

////////////
// GLOBAL //
////////////

// <GLOBAL> The global renderable object array
TArray<IRenderable*> IRenderable::m_RenderableArray;

void IRenderable::RegisterRenderable(IRenderable* _renderable)
{
	m_RenderableArray.Add(_renderable);
}

void IRenderable::UpdateRenderables(float _time)
{
	// For each renderable
	for (int i = 0; i < m_RenderableArray.Size(); i++)
	{
		// Check if this object is marked to be deleted
		if (m_RenderableArray[i]->DeleteMarked())
		{
			// Call the log class
			LRenderableLog::PrintRenderableCreated(m_RenderableArray[i]);

			// Delete the object
			delete m_RenderableArray[i];

			// Remove it from the array
			m_RenderableArray.Remove(i);

			// Come back 1 index
			i--;
		}
		else
		{
			// Update this object
			m_RenderableArray[i]->Update(_time);
		}
	}
}

void IRenderable::RenderRenderables()
{
	// For each renderable
	for (int i = 0; i < m_RenderableArray.Size(); i++)
	{
		// Try to render this object
		m_RenderableArray[i]->Render();
	}
}