///////////////////////////////////////////////////////////////////////////////
// Filename: FActor.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FActor.h"
#include "FActorController.h"

FActor::FActor() : IEntity()
{
	// Set a null ptr for the owner
	m_Owner = nullptr;

	// Set the initial data
	m_DepthPlane = DepthPlane::Ground;
	m_Promoted = false;
}

FActor::FActor(const FActor& other) : IEntity(other)
{
}

FActor::~FActor()
{
	// Remove this actor from the actor controller
	if (m_Promoted)
	{
		FActorController::RemoveActor(this);
	}
}

void FActor::Promote()
{
	// Insert the actor inside the actor controller
	FActorController::InsertActor(this);

	// Set that this actor is promoted
	m_Promoted = true;
}

void FActor::SetLocation(WVector3 _location)
{
	// Call the base set location method
	FObject::SetLocation(_location);

	// Check if we should do any collision check 
	if (!m_Promoted)
	{
		return;
	}

	// Pick all actors around this actor
	unsigned int totalPickedActors;
	FActor** pickedActors = FActorController::PickAllActorsInRange(GetLocation(), std::max(GetSize().x, GetSize().y), totalPickedActors);

	// For each picked actor, check the collision
	for (int i = 0; i < totalPickedActors; i++)
	{
		// Check if the picked actor is differente from self
		if (pickedActors[i] == this)
		{
			// Ignore
			continue;
		}

		// Check if we collided with this actor
		if (VerifyCollision(pickedActors[i]))
		{
			// Dont return because we still need to check for overlap with all other actors
			// return;
		}
	}

	// Update this actor inside the actor controller
	FActorController::UpdateActorPosition(this, GetLocation());
}