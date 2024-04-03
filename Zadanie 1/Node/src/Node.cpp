#include "Node.hpp"
#include "algorithm"

Node::Node(std::vector<Task> tasks, int lb) : m_problem(tasks),
                                              m_lb(lb)
{
    std::cout << "konstruktor 2" << std::endl;
    m_ub = std::numeric_limits<int>::max();
    NodeInit();
}

Node::Node(std::vector<Task> tasks, int lb, int ub) : m_problem(tasks),
                                                      m_lb(lb),
                                                      m_ub(ub)
{
    std::cout << "konstruktor 1" << std::endl;
    NodeInit();
}

// init node, find its permutation, cMax, critical path, critical set, interference task if it exists
// update low and up barrier
void Node::NodeInit()
{
    std::cout << "init " << std::endl;
    m_permutation = m_problem.AlgorithmSchrage();
    std::cout << "po schrage " << std::endl;
    m_cMax = m_permutation.GetCriterion();
    std::cout << "obliczone kryterium " << std::endl;
    std::vector<Task> tmpPath = DesignateCriticalPath();
    std::cout << "wyznaczono path " << std::endl;
    std::copy(tmpPath.begin(), tmpPath.end(), back_inserter(m_criticPath));
    std::cout << "kopioewanie " << std::endl;

    m_cId = DesignateInterferenceTaskId();
    std::cout << "wyznaczono id " << std::endl;
    if (m_cId == -1)
    {
        m_isOptimal = true;
        std::cout << "OPTYMALNY " << std::endl;
    }
    else
    {
        std::cout << "NIEOPTYMALNY " << std::endl;
        m_isOptimal = false;
        m_interferenceTask = m_permutation.GetElem(m_cId);
        std::vector<Task> tmpSet = DesignateCriticalSet();
        std::cout << "tmpSet wektor " << std::endl;
        std::copy(tmpSet.begin(), tmpSet.end(), back_inserter(m_criticSet));
        std::cout << "kopiowanie " << std::endl;
    }
    UpdateUpBarier();
    UpdateLowBarier();
}

Node::~Node()
{
}

std::vector<Task> Node::DesignateCriticalPath()
{
    std::cout << "DesignateCriticalPath " << std::endl;
    Permutation tmp = m_problem.AlgorithmSortQj();
    std::cout << "tmp " << std::endl;
    Task maxQjTask = tmp.GetRankedTasks()[0];
    std::cout << "0 element " << std::endl;
    auto lastInPath = std::find(m_permutation.GetRankedTasks().begin(), m_permutation.GetRankedTasks().end(), maxQjTask);
    std::cout << "znaleziono " << std::endl;
    auto first = m_permutation.GetRankedTasks().begin() + m_cId;
    std::cout << "pierwszy " << std::endl;
    auto last = lastInPath + 1;
    std::cout << "ostatni " << std::endl;
    std::vector<Task> criticalPath;
    for(int i = m_cId; i < lastInPath -m_permutation.GetRankedTasks().begin(); i++ )
    {
        criticalPath.push_back(m_permutation.GetRankedTasks()[i]);
    }
    
    std::cout << "pod wektor " << std::endl;

    return criticalPath;
}

std::vector<Task> Node::DesignateCriticalSet()
{
    auto first = m_permutation.GetRankedTasks().begin() + m_cId + 1;
    auto last = m_permutation.GetRankedTasks().begin() + m_cId + m_criticPath.size();
     std::vector<Task> criticalSet;
    for(int i = m_cId + 1; i < m_criticPath.size(); i++ )
    {
        criticalSet.push_back(m_permutation.GetRankedTasks()[i]);
    }

    return criticalSet;
}

// it finds interference tasks - task C
int Node::DesignateInterferenceTaskId()
{
    int i = 0;
    int sum = m_permutation.GetRankedTasks()[0].GetRj();
    for(i = 0; i < m_permutation.GetRankedTasks().size(); i++)
    {
        if (m_permutation.GetRankedTasks()[i].GetRj() > sum)
        {
            int interferenceTaskId = i;
            break;
        }
        sum += m_permutation.GetRankedTasks()[i].GetPj();
    }

    if (i < m_permutation.GetRankedTasks().size()) // there is no interference task
    {
        return -1;
    }

    return i;
}

// true if interference doesnt exist, false if it exists
bool Node::IsOptimal() const
{
    return m_isOptimal;
}
Task Node::GetInterferenceTask() const
{
    return m_interferenceTask;
}

Permutation Node::GetPermutation() const
{
    return m_permutation;
}

std::vector<Task> Node::GetCriticalPath() const
{
    return m_criticPath;
}

void Node::UpdateUpBarier()
{
    std::cout << "m_ub " << m_ub << " cmax " << m_cMax << std::endl;
    m_ub = std::min(m_ub, m_cMax);
}

void Node::UpdateLowBarier()
{
    Pair schrageSepSolution = m_problem.AlgorithmSchrageSep();
    int tmp = schrageSepSolution.GetCriterion();
    int m_lb = std::max(m_lb, tmp);
}

int Node::GetUpBarier() const
{
    return m_ub;
}

int Node::GetLowBarier() const
{
    return m_lb;
}
