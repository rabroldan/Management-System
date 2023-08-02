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
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

using namespace sdds;
using namespace std;


sdds::LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
{
	Utilities utill;
	
	ifstream openfile(file);
	


	if (!openfile.is_open()) {
		throw string("Unable to open file.");
	}

	
	while (!openfile.eof())
	{
	string data;
	size_t position = 0;
	string activeStation;
	string nextStation;	
	bool more = true;
	Workstation* activeWorkstation = nullptr;
	Workstation* nextWorkstation = nullptr;
		

		getline(openfile, data);
		
		activeStation = utill.extractToken(data, position, more);

		if (more) {
			nextStation = utill.extractToken(data, position, more);
		}

		
		for_each(stations.begin(), stations.end(), [&activeWorkstation, &nextWorkstation, activeStation, nextStation](Workstation* ws) {
			if (ws->getItemName() == activeStation) {
				activeWorkstation = ws;
			}
			else if (ws->getItemName() == nextStation) {
				nextWorkstation = ws;
			}
			});

		if (m_activeLine.size() == 0) {
			m_firstStation = activeWorkstation;
		}

		activeWorkstation->setNextStation(nextWorkstation);
		m_activeLine.push_back(activeWorkstation);
	}

		openfile.close();
}

void sdds::LineManager::reorderStations()
{

	vector<Workstation*> tempStations;
	
	Workstation* lastStation = nullptr;
	unsigned int count = 0;
	unsigned int size = m_activeLine.size();

	while (count < size) {
		for (unsigned int i = 0; i < size; i++) 
		{

			if (m_activeLine[i]->getNextStation() == lastStation) 
			{

				tempStations.push_back(m_activeLine[i]);
				lastStation = m_activeLine[i];
				count++;
				break;

			}
		}
	}


}

bool sdds::LineManager::run(std::ostream &os)
{
	bool empty = true;
    static unsigned int count = 0;
	count++;
	os << "Line Manager Iteration: " << count << endl;

	if (!g_pending.empty()) {
		(*m_firstStation) += move(g_pending.front());
		g_pending.pop_front();
	}

	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		m_activeLine[i]->fill(os);
	}

	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		m_activeLine[i]->attemptToMoveOrder();
	}
	

	for (unsigned int i = 0; i < m_activeLine.size(); i++) {
		if (!m_activeLine[i]->empty()) {
			empty = false;
			break;
		}
	}

	return empty;
}

void sdds::LineManager::display(std::ostream &os) const
{
	unsigned int size = m_activeLine.size();
	
	for (unsigned int i = 0; i < size; i++) {

		m_activeLine[i]->display(os);
	}
}
