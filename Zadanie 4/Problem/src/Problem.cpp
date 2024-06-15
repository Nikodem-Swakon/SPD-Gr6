#include <algorithm>
#include "Problem.hpp"
#include <climits>
#include <iostream>
#include <chrono>
#include <tuple>
#include <numeric>
#include <algorithm> // std::sort
#include <cmath>
#include <random>

/* additional functions */
void printMatrix(const std::vector<std::vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

/* constructors and destructors */
Problem::Problem(std::vector<Task> tasks) : m_tasksNr(tasks.size())
{
    for (int i = 0; i < tasks.size(); i++)
    {
        Task *newTask = new (Task);
        *newTask = tasks[i];
        m_tasks.push_back(*newTask);
    }
}

Problem::~Problem()
{
    m_tasks.clear();
}

/* methods */
int CalculateCMax(const std::vector<Task> &sequence)
{

    int machineNum = sequence[0].GetValuesSize();
    std::vector<std::vector<int>> CzPi(machineNum + 1, std::vector<int>(sequence.size() + 1, 0));

    for (int i = 0; i < sequence.size() + 1; i++)
        CzPi[0][i] = 0;

    for (int z = 0; z < machineNum + 1; z++)
        CzPi[z][0] = 0;

    for (int z = 1; z < machineNum + 1; z++) // process iteration
    {
        for (int i = 1; i < sequence.size() + 1; i++) // task iteration
        {
            CzPi[z][i] = std::max(CzPi[z - 1][i], CzPi[z][i - 1]) + sequence[i - 1].GetValueAt(z - 1);
        }
    }

    return CzPi[machineNum][sequence.size()];
}

int Problem::calculateMakespan(const std::vector<Task> &sequence) const
{
    if (sequence.empty())
        return 0;

    int numJobs = sequence.size();
    int numMachines = sequence[0].GetValues().size();

    std::vector<std::vector<int>> completionTimes(numJobs, std::vector<int>(numMachines, 0));

    // Initialize the first job's completion times
    completionTimes[0][0] = sequence[0].GetValueAt(0);
    for (int j = 1; j < numMachines; ++j)
    {
        completionTimes[0][j] = completionTimes[0][j - 1] + sequence[0].GetValueAt(j);
    }

    // Calculate completion times for the rest of the jobs
    for (int i = 1; i < numJobs; ++i)
    {
        completionTimes[i][0] = completionTimes[i - 1][0] + sequence[i].GetValueAt(0);
        for (int j = 1; j < numMachines; ++j)
        {
            completionTimes[i][j] = std::max(completionTimes[i - 1][j], completionTimes[i][j - 1]) + sequence[i].GetValueAt(j);
        }
    }

    return completionTimes[numJobs - 1][numMachines - 1];
}

bool CompareTasksTasksDec(const Task &a, const Task &b)
{
    return a.GetValueAt(0) < b.GetValueAt(0);
}

bool CompareTasksTasksAsc(const Task &a, const Task &b)
{
    return a.GetValueAt(0) > b.GetValueAt(0);
}

void Problem::GetNextPerm(std::vector<Task> &vec) const
{
    std::next_permutation(vec.begin(), vec.end());
}

// Implementacja algorytmow

std::vector<std::vector<Task>> Problem::GetNeighborsAPEX(const std::vector<Task> vec)
{
    std::vector<std::vector<Task>> neighbors;
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
        std::vector<Task> neighbor = vec;
        std::swap(neighbor[i], neighbor[i + 1]);
        neighbors.push_back(neighbor);
    }

    return neighbors;
}

/**
 * @brief
 *
 * @param maxIter ile razy szukac nowego sasiedztwa
 * @param tabuListSize jak dlugo "wychodzic" z rozwiazanie optymalnego LOKALNIE
 */
void Problem::TabuSearch(int maxIter, int tabuListSize)
{
    std::vector<Task> xCurrentSolution = m_tasks;
    std::vector<Task> xSolution = m_tasks;

    std::vector<std::vector<Task>> tabuList;
    // Znajdź najlepsze rozwiazanie w sasiedztwie
    for (int i = 0; i < maxIter; i++)
    {
        // Pobierz sasiedztwo najlepszego rozwiazania i zapisz jego kryterium
        std::vector<std::vector<Task>> neighbors = GetNeighborsAPEX(xCurrentSolution);
        std::vector<Task> xbestNeighbor = xCurrentSolution;
        int bestNeighborCMax = CalculateCMax(xCurrentSolution);

        // Znajdz najlepsze rozwiazanie w tym sasiedztwie
        for (const std::vector<Task> &neighbor : neighbors)
        {
            // Jeśli rozwiązanie znajduje się juz w TabuList - pomin
            if (std::find(tabuList.begin(), tabuList.end(), neighbor) == tabuList.end())
            {
                int neighborCMax = CalculateCMax(neighbor);
                // Jesli rozwiaznanie jest lepsza - zapisz
                if (bestNeighborCMax > neighborCMax)
                {
                    xbestNeighbor = neighbor;
                    bestNeighborCMax = neighborCMax;
                }
            }
        }

        // Zapisz najlepsze rozwiazanie w tym sasiedztwie do tabuList, uwzgledniajac jego dopuszczaly rozmiar
        xCurrentSolution = xbestNeighbor;
        tabuList.push_back(xCurrentSolution);
        if (tabuList.size() > tabuListSize)
        {
            tabuList.erase(tabuList.begin());
        }

        // Jesli znalezione rozwiazanie jest lepsze niz dotychczasewe, zapisz je
        if (CalculateCMax(xCurrentSolution) < CalculateCMax(xSolution))
        {
            xSolution = xCurrentSolution;
        }
    }

    std::cout << "Solution" << std::endl;
    DisplayTasks(xSolution);
    std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMax(xSolution) << "\033[0m" << std::endl;
}

/**
 * @brief Oblicza temperaturę dla następnego kroku
 *
 * @param temp Aktualna temperatura
 * @param tempN Temperatura końcowa
 * @param temp0 Temperatura początkowa
 * @param maxIter Liczba iteracji
 * @return int Następna temperatura
 */
int CountNextTemp(int temp, int tempN, int temp0, int maxIter)
{
    double t = temp;
    double lambda = pow(static_cast<double>(tempN) / temp0, 1.0 / maxIter);
    return static_cast<int>(t * lambda);
}

/**
 * @brief algorytm symulowanego wyzarzania
 *
 * @param maxIter ile razy szukac nowego sasiedztwa
 * @param tempN temperatura koncowa, blisak 0
 * @param temp0 poczatkowa wartosc temperatury studzenia
 */
void Problem::SimulatedAnnealing(int maxIter, int temp0, int tempN, funType fun)
{
    int temp = temp0;
    std::vector<Task> currentSolution = m_tasks;
    std::vector<Task> acceptedSolution = m_tasks;
    std::vector<Task> finalSolution = m_tasks;
    int currentCMax = CalculateCMax(currentSolution);
    int acceptedCMax = currentCMax;
    int finalCMax = currentCMax;
    while (temp > tempN)
    {
        for (int i = 1; i <= maxIter; i++)
        {
            std::vector<Task> newSolution = acceptedSolution;
            std::random_device rd;
            std::mt19937 g(rd());

            // Wymieszaj wektor
            std::shuffle(newSolution.begin(), newSolution.end(), g);
            // std::cout << "New Perm" << std::endl;
            // DisplayTasks(newSolution);
            int newCMax = CalculateCMax(newSolution);
            int delta = newCMax - acceptedCMax;

            if (delta < 0) // Jesli rozwiaznanie jest lepsza - zapisz
            {
                // std::cout << "Zaakceptowane" << std::endl;
                acceptedSolution = newSolution;
                acceptedCMax = newCMax;
            }
            else
            {
                double randValue = static_cast<double>(std::rand()) / RAND_MAX; // losowa wartosc od 0 do 1
                if (randValue < exp(-delta / temp))
                {
                    acceptedSolution = newSolution;
                    acceptedCMax = newCMax;
                }
            }

            // Jesli znalezlismy lepsze rozwiazanie, zapisz je
            if (acceptedCMax < finalCMax)
            {
                finalSolution = acceptedSolution;
                finalCMax = acceptedCMax;
            }
        }
        // Zaktualizuj wartosc temperatury stygniecia
        temp = fun(temp, tempN, temp0, maxIter);
        if (temp < tempN)
            break;
    }

    std::cout << "Solution" << std::endl;
    DisplayTasks(finalSolution);
    std::cout << "\033[0;32m Cmax: \033[1;32m" << CalculateCMax(finalSolution) << "\033[0m" << std::endl;
}

void Problem::DisplayTasks(const std::vector<Task> &vec)
{
    for (Task task : vec)
    {
        std::cout << task << std::endl;
    }
}
