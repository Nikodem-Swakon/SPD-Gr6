#include "../Inc/Heap.hpp"
#include <assert.h>

namespace Structure
{
        Heap::Heap()
    {
        m_heapSize = 0;
    }

    Heap::~Heap()
    {
    }

    int Heap::GetLeftChildId(int elemId)
    {
        assert(2* elemId + 1 < m_heapSize);
        return 2* elemId + 1;
    }

    int Heap::GetRightChildId(int elemId)
    {
        assert(2* elemId + 2 < m_heapSize);
        return 2* elemId + 2;
    }

    int Heap::GetParentId(int elemId)
    {
        assert(elemId > 0);
        return (elemId - 1)/2;
    }    

    void Heap::BuildHeap(std::vector<int> elems)
    {
        for(int i = 0; i < elems.size(); i++)
            m_elements.push_back(elems[i]);

        m_heapSize = m_elements.size();
    }
} // namespace Structure
