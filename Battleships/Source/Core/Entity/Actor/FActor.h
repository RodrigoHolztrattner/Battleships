////////////////////////////////////////////////////////////////////////////////
// Filename: FActor.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FActor_H_
#define _FActor_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Containers\Array\TArray.h"
#include "..\..\Support\Math\WMath.h"
#include "..\IEntity.h"
#include "FObject.h"

// Declare we know IRenderable
class IRenderable;
class FShaderBase;

/////////////
// DEFINES //
/////////////

/*

	=> Actor (props/doodads and unit will extend this class)

		- Placeable in world (3D)
		- Have an array of renderables

		- Can have more actors linked
		- Can have IA or movements
		- Can block path
		- Extend entity

*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FActor
////////////////////////////////////////////////////////////////////////////////
class FActor : public FObject, public IEntity
{
private:

public:

	///////////////////////////////////
	// CREATION / DESTRUCTION / BASE //
	///////////////////////////////////

	// Create a instance of this object and return a ptr to it
	template <typename ActorClass>
	static ActorClass* Create()
	{
		return IEntity::Create<ActorClass>();
	}

	// Create a instance of this object, link to another actor and return a ptr to it
	template <typename ActorClass>
	static ActorClass* Create(FActor* _owner)
	{
		// Check if the owner is NOT marked to deletion
		// ...

		// Create a new actor
		ActorClass* newActor = new ActorClass;

		// Link those 2 actors
		newActor->LinkActors(_owner);

		// Register the new actor/entity
		RegisterEntity(newActor);

		return newActor;
	}

	// Release this object (mark it for deletion), also, mark any child for deletion too
	virtual void Release()
	{
		// If we have an owner actor, remove the link
		// ... TO-BE IMPLEMENTED!

		// Release all childs
		while (m_LinkedActors.Size())
		{
			// Release this child
			m_LinkedActors[0]->Release();

			// Remove it from the array
			m_LinkedActors.Remove(0);
		}

		// Set the main release
		IEntity::Release();
	}

	// Return the owner
	FActor* GetOwner()
	{
		return m_Owner;
	}

protected:

	// Same as Entity, constructor, copy-constructor and deconstructor are protected
	FActor();
	FActor(const FActor&);
	virtual ~FActor();

	// Update this actor
	virtual void Update(float _time) = 0;

private:

	///////////////////////
	// LINKAGE AND CHILD //
	///////////////////////

	// Link 2 actors (making a relationship between them)
	void LinkActors(FActor* _owner)
	{
		// Set the owner
		m_Owner = _owner;

		// Add this (the child) to the owner linked actor array
		_owner->AddChildActor(this);
	}

	// Add a child to this actor
	void AddChildActor(FActor* _child)
	{
		m_LinkedActors.Add(_child);
	}

protected:

	// Promote this actor physically (allowing it to collide and be picked in the world)
	void Promote();

private:

	// The owner (only valid if this actor is linked with another one, else this ptr is null)
	FActor* m_Owner;

	// The array of linked actors
	TArray<FActor*> m_LinkedActors;

	// If this actor is promoted
	bool m_Promoted;

private:

	///////////////
	// OVERRIDED //
	///////////////

	// Set the actor location
	public: virtual void SetLocation(WVector3 _location);

protected:

	///////////////
	// CALLBACKS //
	///////////////

	// Called when a renderable animation expired
	public: virtual void OnRenderableAnimationExpired(IRenderable* _who){};
};

#endif
