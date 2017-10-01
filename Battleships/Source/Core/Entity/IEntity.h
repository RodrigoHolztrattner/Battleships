////////////////////////////////////////////////////////////////////////////////
// Filename: IEntity.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IEntity_H_
#define _IEntity_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <iostream>
#include "..\Containers\Array\TArray.h"

/////////////
// DEFINES //
/////////////

/*
		- Map

			- Placeable in world (3D/2D)
			- Renderable
			- Can have props/doodads *
			- Static
			- Can block path

		- GUI

			- Not placeable in world
			- Renderable
			- Can have special effects *
			- Static (in general)
			- GUI itself is independent from the other objects

		=> Renderable

			- If an object is renderable, he must be placeable because we need to know where is the object to render ir properly.
			- In the other way, if the object is placeable, not necessarly he is renderable.
*/

/*
	=> What can be an entity?

		- Props/Doodads
		- Units/Ships
		- Actors (in general)
		- Special effects
		- Map
		- GUI

	=> Entity (actor will extend this class)

		- Updateable
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: IEntity
////////////////////////////////////////////////////////////////////////////////
class IEntity
{
private:

public:

	// Create a instance of this object and return a ptr to it
	template <typename EntityClass>
	static EntityClass* Create()
	{
		// Create a new entity
		EntityClass* newEntity = new EntityClass;

		// Register the new entity
		RegisterEntity(newEntity);

		// Call the log class
		LEntityLog::PrintEntityCreated(newEntity);

		return newEntity;
	}

	// Release this object (mark it for deletion)
	virtual void Release()
	{
		// Set the deletion mark to true
		m_DeletionMark = true;
	}

protected:

	// The constructor and destructor are protected because we can only create or delete objects using the Create() or Release() functions
	IEntity();
	virtual ~IEntity();

	// Copy constructor is private because we cant share directly data (only ptrs)
	IEntity(const IEntity&);

	// Update this object
	virtual void Update(float _time) = 0;

private:

	// Check if this object is marked to be deleted
	bool DeleteMarked()
	{
		return m_DeletionMark;
	}

public:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> Register an entity inside the global array
	static void RegisterEntity(IEntity* _entity);

	// <GLOBAL> Update all entities inside the global array (and check if any of them need to be deleted)
	static void UpdateEntities(float _time);

	// <GLOBAL> Return a reference to the entity array
	static TArray<IEntity*>* GetEntitiesReference()
	{
		return &m_EntityArray;
	}

protected:

	// If this object is marked to be deleted
	bool m_DeletionMark;

private:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The global entity array
	static TArray<IEntity*> m_EntityArray;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: IEntityLog
////////////////////////////////////////////////////////////////////////////////
class LEntityLog
{
	// Entity is a friend class
	friend IEntity;

	// This will tell the pre-processor the log force
	static const int LogForce = 1;

public:

	// Print the number of entities
	inline static void PrintNumberEntities()
	{
		if (LogForce >= 1)
		std::cout << "=> Number of entities: " << (IEntity::GetEntitiesReference())->Size() << std::endl;
	}

	// Tell that a entitie was created
	inline static void PrintEntityCreated(IEntity* _who)
	{
		if (LogForce >= 3)
		std::cout << "=> Entity with ID: " << (unsigned int)_who << " was created." << std::endl;
	}

	// Tell that a entitie was deleted
	inline static void PrintEntityDeleted(IEntity* _who)
	{
		if (LogForce >= 3)
		std::cout << "=> Entity with ID: " << (unsigned int)_who << " was deleted." << std::endl;
	}
};

#endif
