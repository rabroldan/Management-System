/*
*****************************************************************************

Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds
{
	class Station
	{
	private:
		int m_id{0};
		std::string m_name {};
		std::string m_desc  {};
		size_t m_serialNumber{};
		size_t m_current {};



	public:
	
		Station(const std::string& record);
		const std::string& getItemName() const; // returns the name of the current Station object
		size_t getNextSerialNumber(); // returns the next serial number to be used on the assembly line and increments m_serialNumber
		size_t getQuantity() const; //returns the remaining quantity of items in the Station object
		void updateQuantity(); // subtracts 1 from the available quantity; should not drop below 0.
		void display(std::ostream& os, bool full) const; //inserts information about the current object into stream os.
	};
}
#endif