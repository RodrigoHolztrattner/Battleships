////////////////////////////////////////////////////////////////////////////////
// Filename: FObject.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FObject_H_
#define _FObject_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\WMath.h"
#include "..\..\Renderable\IRenderable.h"

/////////////
// DEFINES //
/////////////

/*

	=> Objects have a representation in the 3D world (or a faked 2D one), their attributes are:
	
		- Position (location)
		- Rotation
		- Size
		- A Renderable object

	=> They can generate collisions and a collision system can (and should) be build on top of them.

*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FObject
////////////////////////////////////////////////////////////////////////////////
class FObject
{
private:

public:
	FObject();
	FObject(const FObject&);
	virtual ~FObject();

	//////////////
	// 3D WORLD //
	//////////////

	// Set the actor location
	virtual void SetLocation(WVector3 _location);

	// Return the actor location
	virtual WVector3 GetLocation()
	{
		return m_Location;
	}

	// Set the actor rotation
	virtual void SetRotation(WVector3 _rotation)
	{
		m_Rotation = _rotation;
	}

	// Return the rotation
	virtual WVector3 GetRotation()
	{
		return m_Rotation;
	}

	// Set the actor size
	virtual void SetSize(WVector3 _size)
	{
		m_Size = _size;
	}

	// Return the size
	virtual WVector3 GetSize()
	{
		return m_Size;
	}

	// Return the transform matrix for this actor
	virtual WMatrix4 GetTransformMatrix()
	{
		// Build the transform matrix
		m_Transform.BuildTransform(m_Location, m_Rotation, m_Size);

		return m_Transform;
	}

private:

	// The location, rotation and size
	WVector3 m_Location;
	WVector3 m_Rotation;
	WVector3 m_Size;

	// The last location
	WVector3 m_LastLocation;

	// The transform matrix
	WMatrix4 m_Transform;

public:

	///////////
	// DEPTH //
	///////////

	// The depth planes
	enum DepthPlane
	{
		Air3,
		Air2,
		Air1,
		Ground,
		Onwater,
		Water,
		Underground1,
		Underground2,
		Underground3
	};

	// Set the depth plane
	void SetDepthPlane(DepthPlane _plane)
	{
		m_DepthPlane = _plane;
	}

	// Return the depth plane
	DepthPlane GetDepthPlane()
	{
		return m_DepthPlane;
	}

protected:

	// The depth plane
	DepthPlane m_DepthPlane;

public:

	////////////////
	// RENDERABLE //
	////////////////

	// Set the renderable for this actor
	void SetRenderable(IRenderable* _renderable)
	{
		m_Renderable = _renderable;
	}

	// Return the renderable
	IRenderable* GetRenderable()
	{
		return m_Renderable;
	}

private:

	// The array of renderables
	IRenderable* m_Renderable;

public:

	///////////////
	// COLLISION //
	///////////////

	// The collision flags
	enum CollisionFlag
	{
		CanCollide		= 1 << 0,
		CanOverlap		= 1 << 1
	};

	// Set the collision flags
	virtual void SetCollisionFlags(int _collisionFlags)
	{
		m_CollisionFlags = _collisionFlags;
	}

	// Check a collision flag
	virtual bool CheckCollisionFlag(CollisionFlag _collisionFlag)
	{
		return m_CollisionFlags & _collisionFlag;
	}

	// Add a collision dot (they are used to determine the collision positions
	void AddCollisionDot(WVector2 _dot)
	{
		m_CollisionDots.Add(_dot);
	}

protected:

	// Verify if a collision occured
	virtual bool VerifyCollision(FObject* _other);

protected:

	///////////////
	// CALLBACKS //
	///////////////

	// The on collision virtual method
	virtual void OnCollision(FObject* _other){};

	// The on overlap virtual method
	virtual void OnOverlap(FObject* _other){};

private:

	// The collision flags
	int m_CollisionFlags;

	// The collision dots
	TArray<WVector2> m_CollisionDots;
};

#endif
