///////////////////////////////////////////////////////////////////////////////
// Filename: FActorController.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FActorController.h"
#include "FActor.h"

FActorController::FActorController()
{
}

FActorController::FActorController(const FActorController& other)
{
}

FActorController::~FActorController()
{
}

////////////
// GLOBAL //
////////////

// Declare the actor quadtree
TQuadtree<FActor, FActorController::QuadtreeWidth, FActorController::QuadtreeHeight, FActorController::QuadtreeDepth> FActorController::m_ActorQuadtree;

bool FActorController::Initialize()
{
	return true;
}

bool FActorController::InsertActor(FActor* _actor)
{
	bool result;

	// Insert the actor inside the quadtree
	result = m_ActorQuadtree.Insert(_actor);
	if (!result)
	{
		return false;
	}

	return true;
}

bool FActorController::RemoveActor(FActor* _actor)
{
	bool result;

	// Remove the actor from the quadtree
	result = m_ActorQuadtree.Remove(_actor);
	if (!result)
	{
		return false;
	}

	return true;
}

bool FActorController::UpdateActorPosition(FActor* _actor, WVector2 _position)
{
	bool result;

	// Update the actor from the quadtree
	result = m_ActorQuadtree.Update(_actor, _position);
	if (!result)
	{
		return false;
	}

	return true;
}