// Unit tests for input.h routines.
#include "stdafx.h"
#include "input.h"

#ifdef _DEBUG
int main() {
	double d;
	long l;
	string s;

	// Double
	s = "0";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "00";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "  0";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "0  ";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "0.";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "0.0";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = ".0";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "+0";
	assert(::isNumber<double>(d, s));
	assert(d == 0);
	s = "-0";
	assert(::isNumber<double>(d, s));
	assert(d == 0);

	s = "1";
	assert(::isNumber<double>(d, s));
	assert(d == 1);
	s = "1.";
	assert(::isNumber<double>(d, s));
	assert(d == 1);
	s = ".1";
	assert(::isNumber<double>(d, s));
	assert(d == 0.1);
	s = "0.1";
	assert(::isNumber<double>(d, s));
	assert(d == 0.1);
	s = "1.0";
	assert(::isNumber<double>(d, s));
	assert(d == 1);
	s = "01.0";
	assert(::isNumber<double>(d, s));
	assert(d == 1);
	s = "1.1";
	assert(::isNumber<double>(d, s));
	assert(d == 1.1);
	s = "+1";
	assert(::isNumber<double>(d, s));
	assert(d == 1);
	s = "-1";
	assert(::isNumber<double>(d, s));
	assert(d == -1);

	s = "-+0"; // invalid, ill-formed
	try {
		::isNumber<double>(d, s);
	}
	catch (exception e) {
		assert(e.what() == string("invalid stod argument"));
	}

	s = "abc"; // invalid, non-numeric
	try {
		::isNumber<double>(d, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e"; // scientific notation rejected
	try {
		::isNumber<double>(d, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e+4"; // scientific notation rejected
	try {
		::isNumber<double>(d, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "1 1"; // invalid, trailing character
	try {
		::isNumber<double>(d, s);
	}
	catch (exception e) {
		assert(e.what() == string("Trailing characters"));
	}

	// Long 
	s = "0";
	assert(::isNumber<long>(l, s));
	assert(l == 0);
	s = "00";
	assert(::isNumber<long>(l, s));
	assert(l == 0);
	s = "  0";
	assert(::isNumber<long>(l, s));
	assert(l == 0);
	s = "0  ";
	assert(::isNumber<long>(l, s));
	assert(l == 0);
	s = "+0";
	assert(::isNumber<long>(l, s));
	assert(l == 0);
	s = "-0";
	assert(::isNumber<long>(l, s));
	assert(l == 0);

	s = "1";
	assert(::isNumber<long>(l, s));
	assert(l == 1);
	s = "01";
	assert(::isNumber<long>(l, s));
	assert(l == 1);

	s = "+1";
	assert(::isNumber<long>(l, s));
	assert(l == 1);
	s = "-1";
	assert(::isNumber<long>(l, s));
	assert(l == -1);

	s = "2147483648"; // Exceeds max long value.
	try {
		::isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("stol argument out of range"));
	}

	s = "-2147483649"; // Exceed min long value.
	try {
		::isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("stol argument out of range"));
	}

	s = "-+0"; // Invalid, ill-formed.
	try {
		::isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("invalid stol argument"));
	}

	s = "abc"; // Invalid characters.
	try {
		::isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "1 1"; // Invalid trainling chars.
	try {
		::isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("Trailing characters"));
	}

	// Unsupported type.
	char c;
	s = "1";
	assert(!::isNumber<char>(c, s));

	if (getNumber<double>("Enter a double: ", d, 0., 100.))
	cout << "double value: " << d << endl;
	if (getNumber<long>("Enter a long: ", l, -100, 100))
	cout << "long value: " << l << endl;

}
#endif
