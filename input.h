/*************************************************************************
* Title: Numeric input validation
* File: input.h
* Author: James Eli
* Date: 12/29/2017
*
* Integer/float console input validation. Checks string input for valid
* characters, and range. Will repeat input prompting for specified
* number of attempts.
*
* Notes:
*  (1) Requires C++ 11 or greater.
*  (2) Compiled with MS Visual Studio 2017 Community (v141), and/or 
*      Eclipse GCC 5.3.0.
*  (2) Floating point input rejects scientific notation.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   12/29/2017: Initial release. JME
*************************************************************************/
#ifndef NUMERIC_INPUT_VALIDATION_H
#define NUMERIC_INPUT_VALIDATION_H

#include <iostream>  
#include <string>
#include <algorithm>
#include <stdexcept>
#include <cassert>

using namespace std;

#define MAX_INPUT_ATTEMPTS 3  // Maximum input attempts.
#define MAX_INPUT_SIZE     20 // Maximum characters allowed in input string.

// Trim trailing ws from string.
static void trim(string& s) {
	size_t p;

	if ((p = s.find_last_not_of(" \f\n\r\t\v")) != string::npos)
		s.erase(p + 1);
}

template<typename T>
static inline bool validateNumber(T& t, const string s) {
	return false; // Fail for types other than int, long & double (see below).
}

template<>
static inline bool validateNumber<int>(int& i, const string s) {
	string::size_type pos = 0;

	i = stoi(s, &pos);
	if (pos != s.length())
		throw runtime_error("Invalid characters after number");

	return true;
}

template<>
static inline bool validateNumber<long>(long& l, const string s) {
	string::size_type pos = 0;

	l = stol(s, &pos);
	if (pos != s.length())
		throw runtime_error("Invalid characters after number");

	return true;
}

template<>
static inline bool validateNumber<double>(double& d, const string s) {
	string::size_type pos = 0;

	d = stod(s, &pos);
	if (pos != s.length())
		throw runtime_error("Invalid characters after number");

	return true;
}

template<typename T>
static bool isNumber(T& n, string& s) {
	string validChars(" +-1234567890");

	trim(s);

	if (!s.empty()) {
		if (!numeric_limits<T>::is_integer)
			validChars += ".";

		if (s.find_first_not_of(validChars) != string::npos)
			throw runtime_error("Invalid characters");

		if (validateNumber<T>(n, s))
			return true;
	}

	return false;
}

template<typename T>
bool getNumber(string prompt, T& n, T min, T max) {
	string buffer;
	int attempts = MAX_INPUT_ATTEMPTS;

	if (is_same<T, int>::value || is_same<T, long>::value || is_same<T, double>::value) {

		while (attempts--) {
			cout << prompt;
			getline(cin, buffer, '\n');

			// Limit buffer length to reasonable amount.
			if (buffer.size() >= MAX_INPUT_SIZE) {
				cout << "Too many characters input" << endl;
				continue;
			}

			try {
				if (isNumber<T>(n, buffer)) {
					// Check if value between min/max.
					if (n >= min && n <= max)
						return true;
					else
						throw out_of_range("Out of range");
				}
			}
			catch (const out_of_range) {
				cout << "Number outside range (" << min << " to " << max << ")" << endl;
			}
			catch (const exception) {
				cout << "Invalid input: " << buffer << endl;
			}
		}
	}

	return false;
}

#endif