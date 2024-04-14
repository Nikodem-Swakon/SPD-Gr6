#include "Node.hpp"
#include "algorithm"

Node::Node(std::vector<Task> tasks, int lb) : m_problem(tasks),
                                              m_lb(lb),
                                              m_criticPath({})
{
    std::cout << "konstruktor 2" << std::endl;
    for (int i = 0; i < tasks.size(); i++)
    {
        std::cout << tasks[i] << " ";
    }
    m_ub = std::numeric_limits<int>::max();
    NodeInit();
}

Node::Node(std::vector<Task> tasks, int lb, int ub) : m_problem(tasks),
                                                      m_lb(lb),
                                                      m_ub(ub),
                                                      m_criticPath({})
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
    // m_permutation.DisplaySolution();
    std::vector<Task> tmp;
    m_permutation.GetRankedTasks(tmp);
    for (int i = 0; i < tmp.size(); i++)
    {
        std::cout << tmp[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "po schrage " << std::endl;
    m_cMax = m_permutation.GetCriterion();
    std::cout << std::endl;
    std::cout << "obliczone kryterium " << m_cMax << std::endl;
    m_cId = DesignateInterferenceTaskId();
    std::cout << "wyznaczono numer w uszeregowaniu " << m_cId << std::endl;
    if (m_cId == -1)
    {
        m_isOptimal = true;
        std::cout << "OPTYMALNY " << std::endl;
    }
    else
    {
        DesignateCriticalPath(m_criticPath);
        std::cout << "wyznaczono m_criticPath " << std::endl;
        for (int i = 0; i < m_criticPath.size(); i++)
        {
            std::cout << "   " << m_criticPath[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "NIEOPTYMALNY " << std::endl;
        m_isOptimal = false;
        m_interferenceTask = m_permutation.GetElem(m_cId);
        DesignateCriticalSet(m_criticSet);
        std::cout << "tmpSet wektor " << std::endl;
        for (int i = 0; i < m_criticSet.size(); i++)
        {
            std::cout << "   " << m_criticSet[i] << " ";
        }

        std::cout << "kopiowanie " << std::endl;
        UpdateUpBarier();
        UpdateLowBarier();
    }
}

Node::~Node()
{
}

void Node::DesignateCriticalPath(std::vector<Task> &path)
{
    std::cout << "DesignateCriticalPath " << std::endl;
    std::vector<Task> currentPermutation = m_permutation.GetRankedTasks();
    std::cout << "size " << currentPermutation.size() << std::endl;
    int carrentTime = 0;
    int coolingTime = 0;
    // find criticalTask
    m_criticalTask = currentPermutation.back();
    for (int i = 0; i < currentPermutation.size(); i++)
    {
        int last = carrentTime;
        carrentTime = currentPermutation[i].GetPj() + std::max(carrentTime, currentPermutation[i].GetRj());
        coolingTime = coolingTime - (carrentTime - last);
        if ((coolingTime < currentPermutation[i].GetQj()) && (i >= m_cId))
        {
            m_criticalTask = currentPermutation[i];
            coolingTime = currentPermutation[i].GetQj();
        }
        last = carrentTime;
    }
    std::cout << std::endl;

    std::cout << "0 element " << m_criticalTask << std::endl;
    // find criticalPath
    auto lastIter = std::find(currentPermutation.begin(), currentPermutation.end(), m_criticalTask);
    int lastInPath = lastIter - currentPermutation.begin();
    for (int i = m_cId; i <= lastInPath; i++)
    {
        path.push_back(currentPermutation[i]);
    }
    std::cout << std::endl;
    std::cout << "pod wektor " << std::endl;
}

void Node::DesignateCriticalSet(std::vector<Task> &path)
{
    for (int i = m_cId + 1; i < (m_criticPath.size() + m_cId); i++)
    {
        path.push_back(m_permutation.GetRankedTasks()[i]);
    }
}

// it finds interference tasks - task C
int Node::DesignateInterferenceTaskId()
{
    int i = 0;
    int sum = m_permutation.GetRankedTasks()[0].GetRj();
    for (i = 0; i < m_permutation.GetRankedTasks().size(); i++)
    {
        if (m_permutation.GetRankedTasks()[i].GetRj() > sum)
        {
            int interferenceTaskId = i;
            break;
        }
        sum += m_permutation.GetRankedTasks()[i].GetPj();
    }

    if (i >= m_permutation.GetRankedTasks().size()) // there is no interference task
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
    std::cout << "m_ub " << m_ub << std::endl;
}

void Node::UpdateLowBarier()
{
    Pair schrageSepSolution = m_problem.AlgorithmSchrageSep();
    int tmp = schrageSepSolution.GetCriterion();
    m_lb = std::min(m_lb, tmp);
    std::cout << "m_lb " << m_lb << std::endl;
}

int Node::GetUpBarier() const
{
    return m_ub;
}

int Node::GetLowBarier() const
{
    return m_lb;
}

int Node::GetPk() const
{
    int result = 0;
    for (int i = 0; i < m_criticSet.size(); i++)
    {
        result += m_criticSet[i].GetPj();
    }
    return result;
}

int Node::GetQc() const
{
    int result = m_criticSet[0].GetQj();
    for (int i = 0; i < m_criticSet.size(); i++)
    {
        if(m_criticSet[i].GetQj() < result)
            result = m_criticSet[i].GetQj();
    }
    return result;
}

int Node::GetRc() const
{
    int result = m_criticSet[0].GetRj();
    for (int i = 0; i < m_criticSet.size(); i++)
    {
        if(m_criticSet[i].GetRj() < result)
            result = m_criticSet[i].GetRj();
    }
    return result;
}
