/*
    Binary Heap
*/
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define TAB "   " // fills up empty space between the left edge and the leafs

namespace Structure
{
    template <typename T>
    void HeapSort(std::vector<T> &elems);

    template <typename T>
    class Heap
    {
    protected:
        /* Protected members */
        std::vector<T> m_elements;
        int m_heapSize;

        /* Protected methods */

    public:
        /* Public methods */
        Heap() { m_heapSize = 0; };
        ~Heap(){};
        void Insert(T elem);
        T GetMaximum() { return m_elements[0]; };
        T EraseMaximum();
        T Erase(const T elem);
        void BuildHeap(std::vector<T> elems);
        void PrintHeap(int elemId, std::string sp = "", std::string sn = "");

        int GetLeftChildId(int elemId) { return 2 * elemId + 1; };
        int GetRightChildId(int elemId) { return 2 * elemId + 2; };
        int GetParentId(int elemId) { return (elemId - 1) / 2; };
        void HeapifyDown(int elemId);
        void Heapify(int elemId);
        std::vector<T> HeapSort();
        bool Empty() { return m_heapSize == 0; };
        void InserVector(std::vector<T> &elems);
    };

    /////////////////////////// METHODS
    template <typename T>
    void Heap<T>::BuildHeap(std::vector<T> elems)
    {
        for (int i = 0; i < elems.size(); i++)
        {
            Insert(elems[i]);
        }

        m_heapSize = m_elements.size();
        Heapify(GetParentId(m_heapSize - 1));
    }

    /*
        Prints heap elements, beginning from the directed elem.
    */
    template <typename T>
    void Heap<T>::PrintHeap(int elemId, std::string sp, std::string sn)
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

    template <typename T>
    void Heap<T>::Insert(T elem)
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

    template <typename T>
    void Heap<T>::HeapifyDown(int elemId)
    {
        int largest = elemId; // Initialize largest as root Since we are using 0 based indexing
        int l = GetLeftChildId(elemId);
        int r = GetRightChildId(elemId);

        // If left child is larger than root
        if (l < m_heapSize && (m_elements[l] > m_elements[largest]))
            largest = l;

        // If right child is larger than largest so far
        if (r < m_heapSize && (m_elements[r] > m_elements[largest]))
            largest = r;

        // If largest is not root
        if (largest != elemId)
        {
            std::swap(m_elements[elemId], m_elements[largest]);
            // Recursively heapify the affected sub-tree
            HeapifyDown(largest);
        }
    }

    // elemId is last parent in the heap
    template <typename T>
    void Heap<T>::Heapify(int elemId)
    {
        // heapify for all farents

        while (elemId >= 0)
        {
            HeapifyDown(elemId);
            elemId--;
        }
    }

    template <typename T>
    std::vector<T> Heap<T>::HeapSort()
    {
        // find last elem n heap
        int last = m_heapSize - 1;

        while (last > 0)
        {

            if (last > 1)
            {
                std::swap(m_elements[0], m_elements[last]);
            }
            m_heapSize = last;

            // find the last paren
            int parent = GetParentId(last);
            Heapify(parent - 1);
            last = m_heapSize - 1;
        }

        PrintHeap(0);

        return m_elements;
    }

    // erase element with max value
    template <typename T>
    T Heap<T>::EraseMaximum()
    {
        std::swap(m_elements[0], m_elements[m_heapSize - 1]);
        T maxElem = m_elements[m_heapSize - 1];
        m_elements.pop_back();
        m_heapSize--;
        Heapify(GetParentId(m_heapSize - 1));
        return maxElem;
    }

    // erase directed element
    template <typename T>
    T Heap<T>::Erase(const T elem)
    {
        auto toRemove = std::find(m_elements.begin(), m_elements.end(), elem);
        int toRemoveId = toRemove - m_elements.begin();
        std::swap(m_elements[toRemoveId], m_elements[m_heapSize - 1]);
        T maxElem = m_elements[m_heapSize - 1];
        m_elements.pop_back();
        m_heapSize--;
        Heapify(GetParentId(m_heapSize - 1));
        
        return maxElem;
    }

    /////////////////////////// PUBLIC FUNCTION
    // sort algorithm
    template <typename T>
    void HeapSort(std::vector<T> &elems)
    {
        Heap<T> heap;
        heap.BuildHeap(elems);
        std::vector<T> sortedVec = heap.HeapSort();

        // rewrite vector elements
        for (int i = 0; i < elems.size(); i++)
        {
            elems[elems.size() - i - 1] = sortedVec[i];
        }
    }

} // namespace Structure
