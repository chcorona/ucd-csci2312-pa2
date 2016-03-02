//
// Created by Christopher Corona on 2/24/2016.
//


#include "Cluster.h"


namespace Clustering
{

    LNode::LNode(const Point &p, LNodePtr n) : point(p) {next = n;}

    void Cluster:: __del()
    {
        LNodePtr current = __points;
        LNodePtr next;
        for(int i=0; i< __size;++i)
        {
            if(__points != nullptr)
            {
                next=current->next;
                delete current;
                current=next;
            }
        }
        __points = nullptr;
    }

    void Cluster::__cpy(LNodePtr points)
    {
        if(points != nullptr)
        {
            LNodePtr null= nullptr;
            LNode  *head = new LNode(points->point,null);
            LNodePtr ptscurrent= points->next;
            __points = head;
            LNodePtr current = __points;
            while(ptscurrent != nullptr)
            {
                current->next = new LNode(ptscurrent->point,null);
                current=current->next;
                ptscurrent = ptscurrent->next;
            }
        }
    }
    bool Cluster::__in(const Point &p) const
    {

    }
    Cluster::Cluster()
    {
        __size = 0;
        __points = nullptr;
    }

    // The big three: cpy ctor, overloaded operator=, dtor
    Cluster::Cluster(const Cluster &cluster1)
    {
        __size = cluster1.getSize();
        __cpy(cluster1.__points);

    }
    Cluster &Cluster::operator=(const Cluster & another)
    {
        if(this !=&another)
        {
            __size = another.__size;
            __del();
            __cpy(another.__points);
        }
        return *this;
    }
    Cluster::~Cluster()
    {
        __del();
    }

    // Getters/setters
    int Cluster::getSize() const
    {
        return __size;
    }
    // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point & newPoint)
    {
        if(__points == nullptr)
        {
            LNode *N = new LNode(newPoint, nullptr);
            __points = N;
            ++__size;
            return;
        }
        if(__points->next == nullptr)
        {
            LNode *N = new LNode(newPoint, nullptr);
            if(N->point < __points->point)
            {
                N->next = __points;
                __points = N;
                ++__size;
                return;
            }
            else
            {
                __points->next=N;
                ++__size;
                return;
            }
        }
        LNode *N = new LNode(newPoint, nullptr);
        LNodePtr temp = __points->next;
        LNodePtr prev = __points;
        if(N-> point <__points->point)
        {
            __points = N;
            N->next=prev;
            ++__size;
            return;
        }
        if(N-> point < temp->point)
        {
            prev->next = N;
            N->next=temp;
            ++__size;
            return;
        }
        while(temp->next != nullptr)
        {
            if(N->point <temp->point)
            {
                prev = N;
                N->next=prev;
                ++__size;
                return;
            }
            temp = temp->next;
            prev = prev->next;
        }
        temp->next=N;
        ++__size;
    }
    const Point &Cluster::remove(const Point &removePoint)
    {
        LNodePtr temp = __points;
        if(temp->point == removePoint)
        {
            temp = __points;
            if(__size> 0)
            {
                __points = __points->next;
                --__size;
            }
            delete temp;
        }
        else
        {
            int i=0;
            LNodePtr prev = temp;
            temp = temp->next;
            for(;i<__size;++i)
            {
                if(temp->point==removePoint)
                {
                    if(temp->next == nullptr)
                    {
                        prev->next= nullptr;
                        delete temp;
                        __size--;
                    }
                    else
                    {
                        prev->next = temp->next;
                    }
                }
                temp=temp->next;
                prev=prev->next;
            }
        }
        return removePoint;
    }
    bool Cluster::contains(const Point & point)
    {
        LNodePtr  temp;
        if(point == __points->point)
        {
            return true;
        }
        if(__points->next == nullptr)
        {
            return false;
        }
        temp = __points->next;
        for(int i=0;i<__size;++i)
        {
            if(temp->point==point)
            {
                return true;
            }
            temp=temp->next;
        }
        return false;
    }

    // Overloaded operators

    // Members: Subscript
    const Point &Cluster::operator[](unsigned int index) const // notice: const
    {
        LNodePtr  temp;
        temp=__points;
        if(index==0)
        {
            return __points->point;
        }
        for(int i=0;i<index;++i)
        {
            temp=temp->next;
        }
        return temp->point;
    }
    // Members: Compound assignment (Point argument)
    Cluster &Cluster::operator+=(const Point &a)
    {
        this->add(a);
        return *this;
    }
    Cluster &Cluster::operator-=(const Point &s)
    {
        this ->remove(s);
        return  *this;
    }

    // Members: Compound assignment (Cluster argument)
    Cluster &Cluster::operator+=(const Cluster &a) // union
    {
        for(int i=0;i<a.getSize();++i)
        {
            if(!(this->contains(a[i])))
            {
                this->add(a[i]);
            }
        }
        return *this;
    }
    Cluster &Cluster::operator-=(const Cluster &s) // (asymmetric) difference
    {
        for(int i=0;i<s.getSize();++i)
        {
            if(!(this->contains(s[i])))
            {
                this->remove(s[i]);
            }
        }
        return *this;
    }

    // Friends: IO
    std::ostream &operator<<(std::ostream &out, const Cluster &cluster1)
    {
        LNodePtr temp = cluster1.__points;
        for (int i = 0; i < cluster1.__size; ++i)
        {
            out<<temp->point << std::endl;
            temp = temp -> next;
        }
        return out;
    }
    std::istream &operator>>(std::istream &in, Cluster &cluster1)
    {

    }

    // Friends: Comparison
    bool operator==(const Cluster &cluster1, const Cluster &cluster2)
    {
        if(cluster1.__size != cluster2.__size)
        {
            return false;
        }
        for(int i=0; i<cluster1.__size;++i)
        {
            if(cluster1[i] != cluster2[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Cluster &cluster1, const Cluster &cluster2)
    {
        return !(cluster1 == cluster2);
    }

    // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &cluster1, const Point &point1)
    {
        Cluster *cluster2= new Cluster(cluster1);
        if(!(cluster2->contains(point1)))
        {
            cluster2->add(point1);
        }
        else
        {
            return cluster1;
        }
        return *cluster2;
    }
    const Cluster operator-(const Cluster &cluster1, const Point &point1)
    {
        Cluster *cluster2= new Cluster(cluster1);
        if(!(cluster2->contains(point1)))
        {
            cluster2->remove(point1);
        }
        else
        {
            return cluster1;
        }
        return *cluster2;

    }

    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &cluster1, const Cluster &cluster2) // union
    {
        Cluster *cluster3 = new Cluster(cluster1);
        Cluster *cluster4 = new Cluster(cluster2);

        for(int i=0; i< cluster4->getSize();++i)
        {
            if(!(cluster3->contains(cluster2[i])))
            {
                cluster3->add(cluster2[i]);
            }
        }
        delete cluster4;
        return *cluster3;
    }
    const Cluster operator-(const Cluster &cluster1, const Cluster &cluster2) // (asymmetric) difference
    {
        Cluster *cluster3 = new Cluster(cluster1);
        Cluster *cluster4 = new Cluster(cluster2);

        for(int i=0; i< cluster3->getSize();++i)
        {
            if(!(cluster3->contains(cluster2[i])))
            {
                cluster3->remove(cluster2[i]);
            }
        }
        delete cluster4;
        return *cluster3;
    }

};