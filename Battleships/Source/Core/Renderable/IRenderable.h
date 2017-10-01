////////////////////////////////////////////////////////////////////////////////
// Filename: IRenderable.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IRenderable_H_
#define _IRenderable_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Containers\Array\TArray.h"
#include "..\Video\FShaderBase.h"
#include "..\Support\Callback\WCallback.h"

// #include "..\Entity\Actor\FActor.h"

// Declare we know FActor
class FActor;

/////////////
// DEFINES //
/////////////

/*
	=> Renderable (model 3D and epecial effects will extend this class)

		- Linked with an actor (use the actor position, scale and rotation)
		- Renderable (has a unique shader to render it)
		- NOT USED BY UI RENDERING
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: IRenderable
////////////////////////////////////////////////////////////////////////////////
class IRenderable
{
private:

	// Actor is a friend class
	friend FActor;

public:

	// Create a instance of this object and return a ptr to it
	template <typename RenderableClass>
	static RenderableClass* Create(FActor* _owner, FShaderBase* _shader)
	{
		// Create a new renderable
		RenderableClass* newRenderable = new RenderableClass(_owner, _shader);

		// Register the new renderable
		RegisterRenderable(newRenderable);

		// Call the log class
		LRenderableLog::PrintRenderableCreated(newRenderable);

		return newRenderable;
	}

	// Release this object (mark it for deletion)
	virtual void Release()
	{
		// Set the deletion mark to true
		m_DeletionMark = true;
	}

	// Return the owner
	FActor* GetOwner()
	{
		return m_Owner;
	}

	///////////////
	// COLLISION //
	///////////////

	// Set the collision status
	void CollisionStatus(bool _collide)
	{
		m_IgnoreCollision = !_collide;
	}

	// Check if the given position is inside the colision region for this renderable (if there is a collision, call the m_CollisionFunction function)
	virtual bool VerifyPreciseCollision(WVector2 _location, bool _takeParentPosition = true){ return false; };

protected:

	// The constructor and destructor are protected because we can only create and delethe those type of objects using the Create() and Release() functions
	IRenderable(FActor* _owner, FShaderBase* _shader);
	IRenderable(){}
	IRenderable(const IRenderable&);

	// We can only share ptrs, not the object itself
	~IRenderable();

	// Update this object
	virtual void Update(float _time) = 0;

private:

	// Try to render this object
	virtual void Render()
	{
		// Add this object to be rendered
		m_Shader->AddObject(this);
	}

	// Check if this object is marked to be deleted
	bool DeleteMarked()
	{
		return m_DeletionMark;
	}

private:

	////////////
	// GLOBAL //
	////////////

	// Register a renderable object
	static void RegisterRenderable(IRenderable* _renderable);

public:

	// <GLOBAL> Update all objects here
	static void UpdateRenderables(float _time);

	// <GLOBAL> Try to render all objects that are renderable
	static void RenderRenderables();

	// <GLOBAL> Return a reference to the renderable array
	static TArray<IRenderable*>* GetRenderableReference()
	{
		return &m_RenderableArray;
	}

protected:

	// If this renderable ignore collision
	bool m_IgnoreCollision;

private:

	// The actor owner of this renderable
	FActor* m_Owner;

	// The shader ptr that render this object
	FShaderBase* m_Shader;

	// If this object is marked to be deleted
	bool m_DeletionMark;

private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The global renderable object array
	static TArray<IRenderable*> m_RenderableArray;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: IRenderableLog
////////////////////////////////////////////////////////////////////////////////
class LRenderableLog
{
	// Renderable is a friend class
	friend IRenderable;

	// This will tell the pre-processor the log force
	static const int LogForce = 1;

public:

	// Print the number of renderables
	inline static void PrintNumberRenderables()
	{
		if (LogForce >= 1)
			std::cout << "=> Number of renderables: " << (IRenderable::GetRenderableReference())->Size() << std::endl;
	}

	// Tell that a renderable was created
	inline static void PrintRenderableCreated(IRenderable* _who)
	{
		if (LogForce >= 3)
			std::cout << "=> Renderable with ID: " << (unsigned int)_who << " was created." << std::endl;
	}

	// Tell that a renderable was deleted
	inline static void PrintRenderableDeleted(IRenderable* _who)
	{
		if (LogForce >= 3)
			std::cout << "=> Renderable with ID: " << (unsigned int)_who << " was deleted." << std::endl;
	}
};

#endif
