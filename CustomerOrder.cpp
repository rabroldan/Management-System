/*
*****************************************************************************

Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0u;

    CustomerOrder::CustomerOrder()
    {
        ; // blank
    }
    CustomerOrder::CustomerOrder(const std::string str)
    {
        Utilities u{};
        size_t pos = 0;
        bool more = true;
        m_name = u.extractToken(str, pos, more);
        m_product = u.extractToken(str, pos, more);
        m_cntItem = std::count(str.begin(), str.end(), u.getDelimiter()) - 1;

        m_lstItem = new Item *[m_cntItem];

        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(u.extractToken(str, pos, more));
        }

        if (m_widthField < u.getFieldWidth())
        {
            m_widthField = u.getFieldWidth();
        }
    }
    CustomerOrder::CustomerOrder(const CustomerOrder &customerOrder)
    {
        throw std::string("Copy constructor cannot be called");
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&customerOrder) noexcept
    {
        *this = std::move(customerOrder);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&customerOrder) noexcept
    {
        if (this == &customerOrder)
        {
            return *this;
        }
        else
        {
            m_name = customerOrder.m_name;
            m_product = customerOrder.m_product;
            m_cntItem = customerOrder.m_cntItem;
            m_lstItem = customerOrder.m_lstItem;

            customerOrder.m_cntItem = 0;
            customerOrder.m_lstItem = nullptr;

            return *this;
        }
    };

CustomerOrder::~CustomerOrder() {
    if (m_lstItem) {
      for (auto i = 0u; i < m_cntItem; ++i)
        delete m_lstItem[i];

      delete[] m_lstItem;
      m_lstItem = nullptr;
    }
  }

    bool CustomerOrder::isOrderFilled() const
    {
        size_t count = 0;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_isFilled)
            {
                count++;
            }
        }

        return count == m_cntItem;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        size_t itemCount = 0;
        size_t filledCount = 0;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == itemName)
            {
                itemCount++;

                if (m_lstItem[i]->m_isFilled == true)
                {
                    filledCount++;
                }
            }
        }
        if (itemCount == filledCount)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled)
            {
                if (station.getQuantity() > 0)
                {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << std::endl;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << std::right;
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setfill(' ') << std::left;
            os << std::setw(m_widthField + 2) << m_lstItem[i]->m_itemName << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
            os << std::endl;
        }
    };
}