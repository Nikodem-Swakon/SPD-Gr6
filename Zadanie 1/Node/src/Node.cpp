#include "Node.hpp"
#include "algorithm"

Node::Node(std::vector<Task> tasks, int lb) : m_problem(tasks),
                                              m_lb(lb)
{
    m_ub = std::numeric_limits<int>::infinity();
    NodeInit();
}

Node::Node(std::vector<Task> tasks, int lb, int ub) : m_problem(tasks),
                                                      m_lb(lb),
                                                      m_ub(ub)
{
    NodeInit();
}

// init node, find its permutation, cMax, critical path, critical set, interference task if it exists
// update low and up barrier
void Node::NodeInit()
{
    m_permutation = m_problem.AlgorithmSchrage();
    m_cMax = m_permutation.GetCriterion();
    std::vector<Task> tmpPath = DesignateCriticalPath();
    std::copy(tmpPath.begin(), tmpPath.end(), back_inserter(m_criticPath));

    m_cId = DesignateInterferenceTaskId();
    if (m_cId == -1)
    {
        m_isOptimal = true;
    }
    else
    {
        m_isOptimal = false;
        m_interferenceTask = m_permutation.GetElem(m_cId);
        std::vector<Task> tmpSet = DesignateCriticalSet();
        std::copy(tmpSet.begin(), tmpSet.end(), back_inserter(m_criticSet));
    }
    UpdateUpBarier();
    UpdateLowBarier();
}

Node::~Node()
{
}

std::vector<Task> Node::DesignateCriticalPath()
{
    Permutation tmp = m_problem.AlgorithmSortQj();
    Task maxQjTask = tmp.GetRankedTasks()[0];
    auto lastInPath = std::find(m_permutation.GetRankedTasks().begin(), m_permutation.GetRankedTasks().end(), maxQjTask);
    auto first = m_permutation.GetRankedTasks().begin() + m_cId;
    auto last = lastInPath + 1;
    std::vector<Task> criticalPath(first, last);

    return criticalPath;
}

std::vector<Task> Node::DesignateCriticalSet()
{
    auto first = m_permutation.GetRankedTasks().begin() + m_cId + 1;
    auto last = m_permutation.GetRankedTasks().begin() + m_cId + m_criticPath.size();
    std::vector<Task> criticalSet(first, last);

    return criticalSet;
}

int Node::DesignateInterferenceTaskId()
{
    int interferenceTaskId;
    // return interferenceTaskId;

    return -1;
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
