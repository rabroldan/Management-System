/*
*****************************************************************************

Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#include "Workstation.h"

using namespace std;
using namespace sdds;

deque<CustomerOrder> g_pending{};
deque<CustomerOrder> g_completed{};
deque<CustomerOrder> g_incomplete{};


void Workstation::fill(std::ostream &os)
{

if(!m_orders.empty())
{

    m_orders.front().fillItem(*this, os);
}


}

bool Workstation::attemptToMoveOrder()
{

        if (m_orders.empty()) 
        {
            return false;
        }

        if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) 
        {
            if (m_pNextStation == nullptr) {
                if (m_orders.front().isOrderFilled()) {
                    g_completed.push_back(std::move(m_orders.front()));
                } else {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
            } else {
                (*m_pNextStation) += std::move(m_orders.front());
            }
            m_orders.pop_front();
            return true;
        }

        return false;

    }

void Workstation::setNextStation(Workstation* station)
{

    m_pNextStation = station;

}

Workstation* Workstation::getNextStation() const
{

    return m_pNextStation;

}

void Workstation::display(ostream& os) const
{

    os << getItemName();
    os << " --> ";

    if (m_pNextStation == nullptr) {
        os << "End of Line";
    }
    else {
        os << m_pNextStation->getItemName();
    }

    os << endl;

}

Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
{

    m_orders.emplace_back(move(newOrder));
    return *this;

}

bool Workstation::empty() const 
{

    return m_orders.empty();

}