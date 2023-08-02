/*
*****************************************************************************

Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include "Station.h"

namespace sdds{

struct Item
{
	std::string m_itemName;
	size_t m_serialNumber{0};
	bool m_isFilled{false};

	Item(const std::string& src) : m_itemName(src) {};
};
    

class CustomerOrder{

std::string m_name {};
std::string m_product {};
size_t m_cntItem {};
Item** m_lstItem {nullptr};


static size_t m_widthField;


public:
CustomerOrder();
CustomerOrder(const std::string str);
CustomerOrder(const CustomerOrder& customerOrder); // will throw an exception
CustomerOrder& operator=(const CustomerOrder& src) = delete; // cannot copy and delete
CustomerOrder(CustomerOrder&& customerOrder) noexcept; //This constructor should "promise" that it doesn't throw exceptions
CustomerOrder& operator=(CustomerOrder&& customerOrder) noexcept; //This constructor should "promise" that it doesn't throw exceptions

~CustomerOrder();

bool isOrderFilled() const; // if all the items in the order have been filled
bool isItemFilled(const std::string& itemName) const;  //if all items specified by `itemName` have been filled.
void fillItem(Station& station, std::ostream& os); //fills **one** item in the current order that the `Station` specified in the first parameter handles.

void display(std::ostream& os) const;

};

}

#endif