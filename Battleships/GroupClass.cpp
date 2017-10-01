///////////////////////////////////////////////////////////////////////////////
// Filename: GroupClass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "GroupClass.h"

/*
template<typename T>
GroupClass<T>::GroupClass()
{
	// Set the expand size
	expandSize = EXPAND_SIZE;
}

template<typename T>
GroupClass<T>::GroupClass(const GroupClass<T>& other)
{
}

template<typename T>
GroupClass<T>::~GroupClass()
{
	// Delete the old array if we have at last 1 on it
	if(numberUnits)
	{
		delete [] data;
		data = 0;
	}
}


template<typename T>
void GroupClass<T>::SetExpandSize(_u32int size)
{
	expandSize = size;
}

template<typename T>
void GroupClass<T>::Add(T value)
{
	T* tempArray;
	
	// Check if the size its ok
	if((numberUnits + 1) >= currentSize)
	{
		// Set the new current size
		currentSize += expandSize;

		// Alocate space for the tempArray
		tempArray = new T[currentSize];
		
		// Copy the old array
		memcpy(tempArray, data, sizeof(T) * numberUnits);

		// Delete the old array if we have at last 1 on it
		if(numberUnits)
		{
			delete [] data;
			data = 0;
		}

		// Set the new array
		data = tempArray;
	}

	// Set the value
	data[numberUnits] = value;

	// Increment the size
	numberUnits++;
}

template<typename T>
T GroupClass<T>::Get(_u32int pos)
{
	return data[pos];
}

*/