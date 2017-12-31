// Unit tests for input.h routines.
#include "input.h"

#ifdef __GNUC__
#define INVALID_STOD_EXCEPTION "stod"
#define RANGE_STOL_EXCEPTION "stol"
#define INVALID_STOL_EXCEPTION "stol"
#elif _MSC_VER
#define INVALID_STOD_EXCEPTION "invalid stod argument"
#define RANGE_STOL_EXCEPTION "stol argument out of range"
#define INVALID_STOL_EXCEPTION "invalid stol argument"
#endif

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
	s = "1";
	assert(::isNumber(d, s));
	assert(d == 1);

	s = "-+0"; // invalid, ill-formed
	try {
		::isNumber<double>(d, s);
	}
	catch (exception const& e) {
		assert(e.what() == string(INVALID_STOD_EXCEPTION));
	}

	s = "abc"; // invalid, non-numeric
	try {
		::isNumber<double>(d, s);
	}
	catch (exception const& e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e"; // scientific notation rejected
	try {
		::isNumber<double>(d, s);
	}
	catch (exception const& e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e+4"; // scientific notation rejected
	try {
		::isNumber<double>(d, s);
	}
	catch (exception const& e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "1 1"; // invalid, trailing character
	try {
		::isNumber<double>(d, s);
	}
	catch (exception const& e) {
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
	s = "1";
	assert(::isNumber(l, s));
	assert(l == 1);

	s = "2147483648";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception const& e) {
		assert(e.what() == string(RANGE_STOL_EXCEPTION));
	}

	s = "-2147483649";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception const& e) {
		assert(e.what() == string(RANGE_STOL_EXCEPTION));
	}

	s = "-+0";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception const& e) {
		assert(e.what() == string(INVALID_STOL_EXCEPTION));
	}

	s = "abc";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception const& e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception const& e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "1 1";
	try {
		::isNumber<long>(l, s);
	}
	catch (exception const& e) {
		assert(e.what() == string("Trailing characters"));
	}

	char c;
	s = "1";
	assert(!::isNumber<char>(c, s));

	if (getNumber<double>("Enter a double: ", d, 0., 100.))
		cout << "double value: " << d << endl;
	if (getNumber<long>("Enter a long: ", l, -100, 100))
		cout << "long value: " << l << endl;

	return 0;
}
