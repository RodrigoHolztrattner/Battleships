///////////////////////////////////////////////////////////////////////////////
// Filename: IEntity.cpp
///////////////////////////////////////////////////////////////////////////////
#include "IEntity.h"

IEntity::IEntity()
{
	// Set the initial data
	m_DeletionMark = false;
}

IEntity::IEntity(const IEntity& other)
{
}

IEntity::~IEntity()
{
}

////////////
// GLOBAL //
////////////

// <GLOBAL> The global entity array
TArray<IEntity*> IEntity::m_EntityArray;

void IEntity::RegisterEntity(IEntity* _entity)
{
	m_EntityArray.Add(_entity);
}

void IEntity::UpdateEntities(float _time)
{
	// For each registered entity
	for (int i = 0; i < m_EntityArray.Size(); i++)
	{
		// Update this entity
		m_EntityArray[i]->Update(_time);

		// Check if we should delete this entity
		if (m_EntityArray[i]->DeleteMarked())
		{
			// Call the log class
			LEntityLog::PrintEntityDeleted(m_EntityArray[i]);

			// Delete it
			delete m_EntityArray[i];

			// Remove it from the array
			m_EntityArray.Remove(i);

			// Come back a index
			i--;
		}
	}
}