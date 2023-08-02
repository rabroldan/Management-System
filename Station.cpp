/*
*****************************************************************************

Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#include <string>
#include <iostream>
#include <algorithm>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{

	static size_t m_widthField = 0;

	static int id_generator = 0;

	Station::Station(const std::string& record) {
		Utilities util;
		m_id = ++id_generator;
		size_t next_pos = 0;
		bool more;

		m_name = util.extractToken(record, next_pos, more);
		m_serialNumber = stoi(util.extractToken(record, next_pos, more));
		m_current = stoi(util.extractToken(record, next_pos, more));
		m_widthField = std::max(util.getFieldWidth(), m_widthField);
		m_desc = util.extractToken(record, next_pos, more);



	}
	const std::string& Station::getItemName() const 
	{

		return m_name;

	}
	size_t Station::getNextSerialNumber() 
	{

		return m_serialNumber++;

	}
	size_t Station::getQuantity() const 
	{

		return m_current;

	}
	void Station::updateQuantity() 
	{

		if (m_current > 0)
			m_current--;

	}
	void Station::display(std::ostream& os, bool full) const
	{

		if (!full) 
		{
		
			os.setf(ios::right);
			os.width(3);
			os.fill('0');
			os.setf(ios::right);
			os << m_id;
			os.unsetf(ios::right);
			os.fill(' ');
			os << " | ";
			os.width(m_widthField);
			os.setf(ios::left);
			os << m_name;
			os.unsetf(ios::left);
			os << "  | ";
			os.setf(ios::right);
			os.width(6);
			os.fill('0');
			os << m_serialNumber;
			os.unsetf(ios::right);
			os.fill(' ');
			os << " | ";

		}
		else
		{
			
			os.setf(ios::right);
			os.width(3);
			os.fill('0');
			os.setf(ios::right);
			os << m_id;
			os.unsetf(ios::right);
			os.fill(' ');
			os << " | ";
			os.width(m_widthField);
			os.setf(ios::left);
			os << m_name;
			os << "  | ";
			os.setf(ios::right);
			os.width(6);
			os.fill('0');
			os << m_serialNumber;
			os.fill(' ');
			os << " | ";
			os.width(4);
			os << m_current;
			os.unsetf(ios::right);
			os << " | ";
			os << m_desc;
			
		}

		os << endl;
	}
}