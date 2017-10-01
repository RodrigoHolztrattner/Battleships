////////////////////////////////////////////////////////////////////////////////
// Filename: FActorController.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FActorController_H_
#define _FActorController_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\WMath.h"
#include "..\..\Containers\Tree\TQuadtree.h"

/////////////
// DEFINES //
/////////////

// We know the actor class
class FActor;

////////////////////////////////////////////////////////////////////////////////
// Class name: FActorController
////////////////////////////////////////////////////////////////////////////////
class FActorController
{
private:

	// FActor is a friend class
	friend FActor;

private:

	// The quadtree size and depth
	static const unsigned int QuadtreeWidth = 10000;
	static const unsigned int QuadtreeHeight = 10000;
	static const unsigned int QuadtreeDepth = 4;

public:
	FActorController();
	FActorController(const FActorController&);
	~FActorController();

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Initialize the actor controller
	static bool Initialize();

	//////////
	// PICK //
	//////////

	// Pick all actors in range
	static FActor** PickAllActorsInRange(WVector2 _center, float _range, unsigned int& _pickCounter)
	{
		return m_ActorQuadtree.PickInRange(_center, _range, _pickCounter);
	}

	// Pick all actors from class in range
	template <typename ClassType>
	static FActor** PickAllActorsInRange(WVector2 _center, float _range, unsigned int& _pickCounter)
	{
		return m_ActorQuadtree.PickInRangeFromClass<ClassType>(_center, _range, _pickCounter);
	}

private:

	// Insert an actor inside the controller
	static bool InsertActor(FActor* _actor);

	// Remove an actor from the controller
	static bool RemoveActor(FActor* _actor);

	// Update an actor position inside the controller
	static bool UpdateActorPosition(FActor* _actor, WVector2 _position);

private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The actor quadtree
	static TQuadtree<FActor, QuadtreeWidth, QuadtreeHeight, QuadtreeDepth> m_ActorQuadtree;
};

#endif
