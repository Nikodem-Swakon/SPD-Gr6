#include "Node.hpp"
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

void Node::NodeInit()
{
    m_permutation = m_problem.AlgorithmSchrage();
    m_cMax = m_permutation.GetCriterion();
    m_criticPath = DesignateCriticalPath();

    m_cId = DesignateInterferenceTaskId();
    if (m_cId == -1)
    {
        m_isOptimal = true;
    }
    else
    {
        m_isOptimal = false;
        m_criticSet = DesignateCriticalSet();
    }
}

Node::~Node()
{
}

Permutation Node::DesignateCriticalPath()
{
    Permutation criticalPath;

    return criticalPath;
}

Permutation Node::DesignateCriticalSet()
{
    Permutation criticalSet;

    return criticalSet;
}

int Node::DesignateInterferenceTaskId()
{
    int interferenceTaskId;
    return interferenceTaskId;
}

bool Node::IsOptimal()
{
    return m_isOptimal;
}
