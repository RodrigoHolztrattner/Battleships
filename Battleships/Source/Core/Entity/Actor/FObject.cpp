///////////////////////////////////////////////////////////////////////////////
// Filename: FObject.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FObject.h"

FObject::FObject()
{
	// Set the initial data
	m_Renderable = nullptr;
	m_Location = WVector3(0, 0, 0);
	m_Rotation = WVector3(0, 0, 0);
	m_Size = WVector3(1, 1, 1);
	m_LastLocation = m_Location;
	m_CollisionFlags = CanCollide | CanOverlap;
}

FObject::FObject(const FObject& other)
{
}

FObject::~FObject()
{
	// Release the renderable
	if (m_Renderable)
	{
		m_Renderable->Release();
	}
}

bool FObject::VerifyCollision(FObject* _other)
{
	// Check if there is a need to verify the collision
	if (!(m_CollisionFlags & CollisionFlag::CanCollide) && !(m_CollisionFlags & CollisionFlag::CanOverlap) || (!_other->CheckCollisionFlag(CanCollide) && !_other->CheckCollisionFlag(CanOverlap)))
	{
		return false;
	}

	// Check if both objects are colliding
	bool isColliding = SquareCollision(GetLocation(), GetSize(), _other->GetLocation(), _other->GetSize());
	if (!isColliding)
	{
		// No collision at all, return a null ptr
		return false;
	}

	// Check if the target have a renderable object
	if (_other->GetRenderable() != nullptr)
	{
		// For each collision dot
		for (int i = 0; i < m_CollisionDots.Size(); i++)
		{
			// Translate the dot position (TO-BE IMPLEMENTED)
			WVector2 translatedDot = m_CollisionDots[i];

			// Check if this dot collides with the target renderable object
			isColliding = _other->GetRenderable()->VerifyPreciseCollision(translatedDot);
			if (isColliding)
			{
				break;
			}
		}
	}

	// Check if this object and the target can collide
	if ((m_CollisionFlags & CollisionFlag::CanCollide) && _other->CheckCollisionFlag(CanCollide))
	{
		// Do a position rollback
		m_Location = m_LastLocation;

		// Yeah there is a collision, call the OnCollision method
		OnCollision(_other);

		return true;
	}

	// Check if this object and the target can overlap (but not collide)
	if ((m_CollisionFlags & CollisionFlag::CanOverlap) && _other->CheckCollisionFlag(CanOverlap))
	{
		// Yeah there is an overlap, call the OnOverlap method
		OnOverlap(_other);

		return true;
	}

	return nullptr;
}

void FObject::SetLocation(WVector3 _location)
{
	// Save the current position
	m_LastLocation = GetLocation();

	// Set the new location
	m_Location = _location;
}