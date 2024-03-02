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
        return 2 * elemId + 1;
    }

    int Heap::GetRightChildId(int elemId)
    {
        return 2 * elemId + 2;
    }

    int Heap::GetParentId(int elemId)
    {
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

    void Heap::Heapify(int elemId)
    {
        int largest = elemId;   // Initialize largest as root Since we are using 0 based indexing
        int l = GetLeftChildId(elemId);
        int r = GetRightChildId(elemId); 

        // If left child is larger than root
        if (l < m_heapSize && m_elements[l] > m_elements[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < m_heapSize && m_elements[r] > m_elements[largest])
            largest = r;

        // If largest is not root
        if (largest != elemId)
        {
            std::swap(m_elements[elemId], m_elements[largest]);

            // Recursively heapify the affected sub-tree
            Heapify(largest);
        }
    }

    void Heap::Heapify()
    {
        // find the last paren
        int parent = GetParentId(m_heapSize);
        // heapify for all farents
        while(parent >= 0)
        {
            Heapify(parent);
            parent--;
        }
        
    }

} // namespace Structure
