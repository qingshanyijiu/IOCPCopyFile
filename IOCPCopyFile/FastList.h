#ifndef		___FAST_LIST___H
#define		___FAST_LIST___H

#include "CriticalLock.h"

#define  MUTIL_THREAD_ACTION_LIST	

template<typename DataType>
class CFastList
{
public:
	typedef struct tagNoteInfo
	{
		DataType	noteData;
		tagNoteInfo*	pNext;
		
		tagNoteInfo()
		{
			pNext = NULL;
		}
		
	}NoteInfo,*PNoteInfo;

public:
	CFastList()
	{
		m_pHead = new NoteInfo();
		m_pHead->pNext = NULL;

		m_pTail = m_pHead;
	}

	~CFastList()
	{
		Clear();
		delete m_pHead;
	}

	void PushBack(DataType& dataInfo)
	{
		NoteInfo* pNote = new NoteInfo();
		pNote->noteData = dataInfo;
		pNote->pNext = NULL;
		
#ifdef MUTIL_THREAD_ACTION_LIST
		CCriticalLock::CAutoLock lock(m_tailLock);
#endif
		m_pTail->pNext = pNote;
		m_pTail = pNote;

	}

	DataType&	Front()
	{
		return m_pHead->pNext->noteData;
	}

	void	PopFront()
	{
#ifdef MUTIL_THREAD_ACTION_LIST
		CCriticalLock::CAutoLock lock(m_headLock);
#endif
		NoteInfo* pNewHead = m_pHead->pNext;
		if (pNewHead)
		{
			delete m_pHead;
			m_pHead = pNewHead;
		}
	}

	void Clear()
	{
#ifdef MUTIL_THREAD_ACTION_LIST
		CCriticalLock::CAutoLock lock(m_headLock);
#endif
		NoteInfo* pNewHead= m_pHead->pNext;
		
		while (pNewHead)
		{
			delete m_pHead;
			m_pHead = pNewHead;
			pNewHead= m_pHead->pNext;
		}
	}

public:


protected:
	PNoteInfo		m_pHead;
	PNoteInfo		m_pTail;

#ifdef MUTIL_THREAD_ACTION_LIST
	CCriticalLock	m_headLock;
	CCriticalLock	m_tailLock;
#endif
};

#endif