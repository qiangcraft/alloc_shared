/**
 * @class FastMemoryPool
 * @brief A memory pool implementation for fast allocation and deallocation of fixed-size blocks.
 *
 * The FastMemoryPool class provides a memory pool that allows efficient allocation and deallocation
 * of fixed-size blocks. It internally manages a contiguous block of memory and keeps track of the
 * allocated and free blocks.
 * source: https://arxiv.org/pdf/2210.16471
 */
#pragma once
#include <stdlib.h>
#include <cstring>
#include <cstddef>
class FastMemoryPool
{ // Basic type define
	typedef unsigned int uint;
	typedef unsigned char uchar;

	uint m_numOfBlocks;		// Num of blocks
	uint m_sizeOfEachBlock; // Size of each block
	uint m_numFreeBlocks;	// Num of remaining blocks
	uint m_numInitialized;	// Num of initialized blocks
	uchar *m_memStart;		// Beginning of memory pool
	uchar *m_next;			// Num of next free block
public:
	FastMemoryPool()
	{
		m_numOfBlocks = 0;
		m_sizeOfEachBlock = 0;
		m_numFreeBlocks = 0;
		m_numInitialized = 0;
		m_memStart = NULL;
		m_next = 0;
	}
	~FastMemoryPool() { DestroyPool(); }
	void CreatePool(size_t sizeOfEachBlock,
					uint numOfBlocks)
	{
		m_numOfBlocks = numOfBlocks;
		m_sizeOfEachBlock = sizeOfEachBlock;
		m_memStart = new uchar[m_sizeOfEachBlock *
							   m_numOfBlocks];
		m_numFreeBlocks = numOfBlocks;
		m_next = m_memStart;
	}
	void DestroyPool()
	{
		delete[] m_memStart;
		m_memStart = NULL;
	}
	uchar *AddrFromIndex(uint i) const
	{
		return m_memStart + (i * m_sizeOfEachBlock);
	}
	uint IndexFromAddr(const uchar *p) const
	{
		return (((uint)(p - m_memStart)) / m_sizeOfEachBlock);
	}
	void *allocate(size_t)
	{
		if (m_numInitialized < m_numOfBlocks)
		{
			uint *p = (uint *)AddrFromIndex(m_numInitialized);
			*p = m_numInitialized + 1;
			m_numInitialized++;
		}
		void *ret = NULL;
		if (m_numFreeBlocks > 0)
		{
			ret = (void *)m_next;
			--m_numFreeBlocks;
			if (m_numFreeBlocks != 0)
			{
				m_next = AddrFromIndex(*((uint *)m_next));
			}
			else
			{
				m_next = NULL;
			}
		}
		return ret;
	}
	void free(void *p)
	{
		if (m_next != NULL)
		{
			(*(uint *)p) = IndexFromAddr(m_next);
			m_next = (uchar *)p;
		}
		else
		{
			*((uint *)p) = m_numOfBlocks;
			m_next = (uchar *)p;
		}
		++m_numFreeBlocks;
	}
};