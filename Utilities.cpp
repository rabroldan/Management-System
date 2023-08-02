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
#include <algorithm>
#include "Utilities.h"
using namespace std;
namespace sdds
{
		char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string removeSpaces(const std::string &str)
	{
		std::string result;
		bool leadingSpaces = true;

		for (char c : str)
		{
			if (leadingSpaces && c == ' ')
			{
				continue;
			}

			leadingSpaces = false;
			result += c;
		}

		size_t end = result.length();
		while (end > 0 && result[end - 1] == ' ')
		{
			--end;
		}

		result.erase(end);

		return result;
	}

	std::string Utilities::extractToken(const std::string &source, size_t &next_pos, bool &more)
	{
		std::string result = source.substr(next_pos);
		int temp = result.find(m_delimiter);

		if (source[next_pos] == m_delimiter)
		{
			more = false;
			throw std::string("Delimiter is found at next_pos.");
		}

		if (temp == -1)
		{
			result = removeSpaces(result);
			more = false;
		}
		else
		{
			result = removeSpaces(result.substr(0, temp));
			more = true;
			next_pos += temp + 1;
		}

		if (m_widthField < result.length())
			m_widthField = result.length();

		return result;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}
