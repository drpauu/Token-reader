#include "variables.hpp"

variables::variables()throw(error)
{
    head = NULL;
}

variables::variables(const variables &v)throw(error)
{
    node *temp = v.head;
    head = NULL;
    node *current = head;
    while (temp)
    {
        node *n = new node;
        n->_v = temp->_v;
        n->_e = temp->_e;
        n->_seg = NULL;
        if (!head)
        {
            head = n;
            current = head;
        }
        else
        {
            current->_seg = n;
            current = n;
        }
        temp = temp->_seg;
    }
}

variables &variables::operator=(const variables &v)throw(error)
{
    if (this == &v)
        return *this;
    node *temp = head;
    while (temp)
    {
        node *aux = temp->_seg;
        delete temp;
        temp = aux;
    }
    node *temp2 = v.head;
    head = NULL;
    node *current = head;
    while (temp2)
    {
        node *n = new node;
        n->_v = temp2->_v;
        n->_e = temp2->_e;
        n->_seg = NULL;
        if (!head)
        {
            head = n;
            current = head;
        }
        else
        {
            current->_seg = n;
            current = n;
        }
        temp2 = temp2->_seg;
    }
    return *this;
}

variables::~variables()throw(error)
{
    node *temp = head;
    while (temp)
    {
        node *aux = temp->_seg;
        delete temp;
        temp = aux;
    }
    head = NULL;
}

void variables::assign(const std::string &v, const expressio &e) throw(error)
{
    node *temp = head;
    while (temp != nullptr)
    {
        if (temp->_v == v)
        {
            temp->_e = e;
            return;
        }
        temp = temp->_seg;
    }

    temp = new node;
    temp->_v = v;
    temp->_e = e;
    temp->_seg = head;
    head = temp;
}

void variables::unassign(const std::string &v) throw()
{
    node *p = head, *ant = NULL;
    while (p != NULL && p->_v != v)
    {
        ant = p;
        p = p->_seg;
    }
    if (p != NULL)
    {
        if (ant == NULL)
        {
            head = p->_seg;
        }
        else
        {
            ant->_seg = p->_seg;
        }
        delete p;
    }
}

expressio variables::valor(const std::string &lv) const throw(error)
{
    node *p = head;
    while (p != NULL && p->_v != lv)
    {
        p = p->_seg;
    }
    if (p != NULL)
    {
        return p->_e;
    }
    return expressio();
}

void variables::dump(std::list<std::string> &l) const throw(error)
{
    node *p = head;
    while (p != NULL)
    {
        l.push_back(p->_v);
        p = p->_seg;
    }
}