////////////////////////////////////////////////////////////////////////////////
// Filename: FThread.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FThread_H_
#define _FThread_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\Callback\WCallback.h"
#include <thread>

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FThread
////////////////////////////////////////////////////////////////////////////////
template<typename CallType>
class FThread
{
	// The thread specializations
	enum class ThreadSpecialization
	{
		InputOutput,
		Process,
		TotalSpecializations
	};

private:
	
	// The number of threads we can have for each specialization (the numbers MUST be different)
	enum ThreadLimits
	{
		InputOutput = 100, // All we need in theory
		Process = 8,
	};

public:
	FThread()
	{
		// Set the initial data
		m_Free = true;
	}
	FThread(const FThread&){}
	~FThread(){}

	// Dispatch this thread (if we got a free thread) or just run inside the main thread
	void Dispatch(WCallback<CallType> _function, CallType* _Data)
	{
		// Set the threaded function
		m_ThreadedFunction = _function;

		// Create a new thread to dispatch
		std::thread dispatchThread(FThread::DispatchHelper, this, _Data);
		dispatchThread.detach();
	}

	// Return if this thread is free
	bool Free()
	{
		return m_Free;
	}

protected:

	// Make this thread busy (callbed by the global function only)
	void SetBusy()
	{
		m_Free = false;
	}

private:

	// Dispatch the threaded function
	void DispatchThreaded(CallType* _Data)
	{
		/*
		THREADED
		*/

		// Call the function
		m_ThreadedFunction.Run(_Data);

		// Set that this thread is free
		m_Free = true;
	}

public:

	////////////
	// GLOBAL //
	////////////

	// <GLOBAL> The global dispatch helper
	static void DispatchHelper(FThread* _resourceLoader, CallType* _Data)
	{
		_resourceLoader->DispatchThreaded(_Data);
	}

private:

	// If this thread is free
	bool m_Free;

	// The function that we will call using this thread
	WCallback<CallType> m_ThreadedFunction;
};

#endif
