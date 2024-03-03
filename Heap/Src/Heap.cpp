#include "../Inc/Heap.hpp"
#include <assert.h>
#include <string>
#include <algorithm>

namespace Structure
{
    /////////////////////////// METHODS
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

    void Heap::BuildHeap(std::vector<int> &elems)
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

    void Heap::HeapifyDown(int elemId)
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
            HeapifyDown(largest);
        }
    }

    void Heap::Heapify(int elemId)
    {
        // heapify for all farents
       
        while(elemId >= 0)
        {
            HeapifyDown(elemId);
            elemId--;
        }
        
    }


    std::vector<int> Heap::HeapSort()
    {
        // find last elem n heap
        int last = m_heapSize - 1;
        if(last > 0)
            std::swap(m_elements[0], m_elements[last]);
        int max = m_elements[last];
        m_heapSize = last;

            std::cout << "After swap, max elem is on " << last << " position." << std::endl;
            std::cout << "Its parent is node number " << GetParentId(last) << std::endl;
            PrintHeap(0);


        // find the last paren
        int parent = GetParentId(last);
        Heapify(parent - 1);    // to not heapify the elem which is replaced


            std::cout << "After heapSort "<< std::endl;
        PrintHeap(0);
        return m_elements;
    }


    /////////////////////////// PUBLIC FUNCTION
    // sort algorithm
    void HeapSort(std::vector<int> &elems)
    {
        Heap heap;
        heap.BuildHeap(elems);

            std::cout << "Heap" <<std::endl;
            heap.PrintHeap(0);

        std::vector<int> sortedVec = heap.HeapSort();
        for(int i = 0; i < elems.size(); i++)
        {
            elems[i] = sortedVec[i];
        }
        
    }


} // namespace Structure
