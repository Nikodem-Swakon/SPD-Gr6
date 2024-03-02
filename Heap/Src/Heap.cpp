#include "../Inc/Heap.hpp"
#include <assert.h>
#include <string>
#include <algorithm>

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
        assert(2 * elemId + 1 < m_heapSize);
        return 2 * elemId + 1;
    }

    int Heap::GetRightChildId(int elemId)
    {
        assert(2 * elemId + 2 < m_heapSize);
        return 2 * elemId + 2;
    }

    int Heap::GetParentId(int elemId)
    {
        assert(elemId > 0);
        return (elemId - 1) / 2;
    }

    void Heap::BuildHeap(std::vector<int> elems)
    {
        for (int i = 0; i < elems.size(); i++)
        {
            Insert(elems[i]);
        }

        m_heapSize = m_elements.size();
    }

    /*
        Prints heap elements, beginning from the directed elem.
    */
    void Heap::PrintHeap(int elemId, std::string sp, std::string sn)
    {
        std::string s;

        if (elemId < m_heapSize)
        {
            s = sp;
            if (sn == TAB)
                s[s.length() - 2] = ' ';
            PrintHeap(2 * elemId + 2, s + TAB, TAB);

            s = s.substr(0, sp.length() - 2);

            std::cout << s << sn << m_elements[elemId] << std::endl;

            s = sp;
            if (sn == TAB)
                s[s.length() - 2] = ' ';
            PrintHeap(2 * elemId + 1, s + TAB, TAB);
        }
    }

    void Heap::Insert(int elem)
    {
        int i, j;

        m_elements.push_back(elem);
        i = m_heapSize++;
        j = (i - 1) / 2;

        // while the elem is greater ten parent
        while (i > 0 && m_elements[j] < elem)
        {
            m_elements[i] = m_elements[j];
            i = j;
            j = (i - 1) / 2;
        }
        m_elements[i] = elem;
    }

    int Heap::GetMaximum()
    {
        return m_elements[0];
    }

} // namespace Structure
