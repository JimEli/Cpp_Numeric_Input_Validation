#include "stdafx.h"
#include "input.h"

#ifdef _DEBUG
int main() {
	double d;
	long l;
	string s;

	// Double
	s = "0";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "00";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "  0";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "0  ";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "0.";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "0.0";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = ".0";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "+0";
	assert(isNumber<double>(d, s));
	assert(d == 0);
	s = "-0";
	assert(isNumber<double>(d, s));
	assert(d == 0);

	s = "1";
	assert(isNumber<double>(d, s));
	assert(d == 1);
	s = "1.";
	assert(isNumber<double>(d, s));
	assert(d == 1);
	s = "1.0";
	assert(isNumber<double>(d, s));
	assert(d == 1);
	s = "01.0";
	assert(isNumber<double>(d, s));
	assert(d == 1);
	s = "1.1";
	assert(isNumber<double>(d, s));
	assert(d == 1.1);
	s = "+1";
	assert(isNumber<double>(d, s));
	assert(d == 1);
	s = "-1";
	assert(isNumber<double>(d, s));
	assert(d == -1);

	s = "-+0";
	try {
		isNumber<double>(d, s);
	}
	catch (exception e) {
		assert(e.what() == string("invalid stod argument"));
	}

	s = "abc";
	try {
		isNumber<double>(d, s);
	} catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e";
	try {
		isNumber<double>(d, s);
	} catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "1 1";
	try {
		isNumber<double>(d, s);
	} catch (exception e) {
		assert(e.what() == string("Invalid characters after number"));
	}

	// Long 
	s = "0";
	assert(isNumber<long>(l, s));
	assert(l == 0);
	s = "00";
	assert(isNumber<long>(l, s));
	assert(l == 0);
	s = "  0";
	assert(isNumber<long>(l, s));
	assert(l == 0);
	s = "0  ";
	assert(isNumber<long>(l, s));
	assert(l == 0);
	s = "+0";
	assert(isNumber<long>(l, s));
	assert(l == 0);
	s = "-0";
	assert(isNumber<long>(l, s));
	assert(l == 0);

	s = "1";
	assert(isNumber<long>(l, s));
	assert(l == 1);
	s = "01";
	assert(isNumber<long>(l, s));
	assert(l == 1);

	s = "+1";
	assert(isNumber<long>(l, s));
	assert(l == 1);
	s = "-1";
	assert(isNumber<long>(l, s));
	assert(l == -1);

	s = "2147483648";
	try {
		isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("stol argument out of range"));
	}

	s = "-2147483649";
	try {
		isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("stol argument out of range"));
	}

	s = "-+0";
	try {
		isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("invalid stol argument"));
	}

	s = "abc";
	try {
		isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "123e";
	try {
		isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters"));
	}

	s = "1 1";
	try {
		isNumber<long>(l, s);
	}
	catch (exception e) {
		assert(e.what() == string("Invalid characters after number"));
	}

	char c;
	s = "1";
	assert(!isNumber<char>(c, s));
/*
	if (getNumber<double>("Enter a double: ", d, 0., 100.))
		cout << "double value: " << d << endl;
	if (getNumber<long>("Enter a long: ", l, -100, 100))
		cout << "long value: " << l << endl;
*/
}
#endif

/*
template <typename T> struct input_t {
	T& n;
	explicit input_t(T& n) : n(n) { }
	input_t(const input_t <T> & i) : n(i.n) { }
};

template <typename T> inline input_t <T> input(T& n) {
	input_t <T> result(n);
	return result;
}

template <typename T> istream& operator >> (istream& ins, const input_t <T> & i) {
	// Read a line (terminated by ENTER|NEWLINE) from the user
	string s;
	getline(ins, s);

	// Get rid of any trailing whitespace
	s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

	// Read it into the target type
	istringstream ss(s);
	ss >> i.n;

	// Check to see that there is nothing left over
	if (!ss.eof())
		ins.setstate(ios::failbit);

	return ins;
}

int main() {
	int n;

	cout << "Please enter an integer> " << flush;
	cin >> input(n);

	while (!cin) {
		cin.clear();
		cout << "Please, enter only an INTEGER: " << flush;
		cin >> input(n);
	}

	cout << "Good job!\n" "You entered the number " << n << endl;

	return 0;
}

//
//
// integer validation
template <typename Result> Result get_input(
	Result             default_value,
	Result             minimum_value,
	Result             maximum_value,
	const std::string& start_message,
	const std::string& try_again_message,
	const std::string& bad_range_message
) {
	Result result(default_value);

	std::cout << start_message;

	while (true) {
		std::string s;
		std::getline(std::cin, s);

		s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);
		if (s.empty()) 
			break;

		std::istringstream ss(s);
		ss >> result;

		if (!ss.eof())
			std::cout << try_again_message;

		else if ((minimum_value > result) or (result > maximum_value))
			std::cout << bad_range_message;

		else break;
	}

	return result;
}

int main() {
	int x = get_input(
		50,
		1,
		100,
		"I am thinking of a number between 1 and 100, inclusive.\nWhat is it? ",
		"That was not a number. Try again: ",
		"The number must be between 1 and 100, inclusive: "
	);

	cout << "Good job! You guessed the number " << x << ".\n";

	return 0;
}

//
//
//
bool isFloat(string s) {
	istringstream iss(s);
	float f;

	iss >> std::noskipws >> f;
	return iss && iss.eof(); // Result converted to bool
}

bool string_to_float(string s, float *f) {
	std::istringstream iss(s);
	iss >> std::noskipws >> *f;
	return iss.eof() && !iss.fail();
}

bool isFloat(string myString) {
	std::istringstream iss(myString);
	float f;
	iss >> noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

#include <cctype>
static bool isFloatNumber(const std::string& string) {
	std::string::const_iterator it = string.begin();
	bool decimalPoint = false;
	int minSize = 0;
	if (string.size()>0 && (string[0] == '-' || string[0] == '+')) {
		it++;
		minSize++;
	}
	while (it != string.end()) {
		if (*it == '.') {
			if (!decimalPoint) decimalPoint = true;
			else break;
		}
		else if (!std::isdigit(*it) && ((*it != 'f') || it + 1 != string.end() || !decimalPoint)) {
			break;
		}
		++it;
	}
	return string.size() > minSize && it == string.end();
}

int main(void) {
	Add();
	return 0;
}

//
//
//
void remove_chars(char *dest, const char *src, const char *excludes) {
	do {
		if (!strchr(excludes, *src))
			*dest++ = *src;
	} while (*src++);

	*dest = '\000';
}

void removeWhitespace(std::string &s) {
	for (size_t i = 0; i < s.length(); i++) {
		if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') {
			s.erase(i, 1);
			i--;
		}
	}
}

//double string_to_double(const std::string &s) {
double string_to_double(string s) {
//	s.erase(std::remove_if(s.begin(), s.end(), [](char c) { return (c == '\r' || c == '\t' || c == ' ' || c == '\n'); }), s.end());
	//s.erase( std::remove_if( s.begin(), s.end(), ::isspace ), s.end() );
	//std::bind( std::isspace<char>, _1, std::locale::classic() );

//	s.erase(
//		std::remove_if(
//			s.begin(), s.end(),
//			[](unsigned char ch) { return isspace(ch) || ispunct(ch); }),
//		s.end());

	[](char ch) { return std::isspace<char>(ch, std::locale::classic()); };
	std::istringstream iss(s);
	double d;

	if (!(iss >> d))
		return 0;

	return d;
}

static inline string &ltrim(string &s) {
	s.erase(s.begin(), find_if_not(s.begin(), s.end(), [](int c) { return isspace(c); }));
	return s;
}

static inline string &rtrim(string &s) {
	s.erase(find_if_not(s.rbegin(), s.rend(), [](int c) { return isspace(c); }).base(), s.end());
	return s;
}

static inline string trim(const string &s) {
	string t = s;
	return ltrim(rtrim(t));
}

bool inputFloat() {
	cout << "Enter a number: ";

	string num;
	//cin.getline(num1, STRLEN);
	//if (cin.fail()) {
	//	cin.clear();
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//}
	cin.clear(); // Clear stream status.
	cin >> skipws >> setw(3) >> num;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// Ignore to the end of line
	if (cin.bad()) {
		cerr << "Input stream corrupted.\n"; // Stream corrupted.
		exit(EXIT_FAILURE);
	}
	if (num.find_first_not_of("1234567890.-+") != string::npos) {
		cout << "Invalid entry: " << num << endl;
		return false;
	}
	return true;
}
*/
/*
inline double str_to_double(const std::string& s) {
	char *end = NULL;
	double val = strtod(s.c_str(), &end);

	if (end == s.c_str() || end - s.c_str() != s.length())
		serror::raise("string '%s' does not represent a valid floating point value", s.c_str());
	if (val == +HUGE_VAL)
		serror::raise("string '%s' represents floating point value which is too big", s.c_str());
	if (val == -HUGE_VAL)
		serror::raise("string '%s' represents floating point value which is too small", s.c_str());
	return val;
}

void getNum(void) {
	string line;
	int num;
	
	while ((std::cout << "Please enter a number: ") //make sure the user knows what you expect
		&& std::getline(std::cin, line)
		&& !(std::istringstream{ line } >> num)
		&& (num < min || num > max)
		) {
		std::istringstream is{ line };
		if ((is >> num) && !(is >> line) && (num > min && num < max)) {
			break; //done, we got what we wanted
		}
		std::cerr << "Invalid input, try again." << std::endl;
	}
}

// some tests
#include <cassert>
int main(void) {
	float f;

	// simple case:
	assert(0.5 == string_to_double("0.5"));
	assert(string_to_float("0.5", &f));
	assert(f == 0.5);

	// blank space:
	assert(0.6 == string_to_double("0.6 "));
	assert(!string_to_float("0.6 ", &f));
	assert(0.7 == string_to_double(" 0.7"));
	assert(!string_to_float(" 0.7", &f));

	// trailing non digit characters:
	assert(0.8 == string_to_double("0.8a"));
	assert(!string_to_float("0.8a", &f));

	// note that with your requirements you can't distinguish
	// all the the allowed string representation of zero from
	// the non numerical strings:
	assert(0 == string_to_double("0"));
	assert(string_to_float("0", &f));
	assert(f == 0);
	assert(0 == string_to_double("0."));
	assert(string_to_float("0.", &f));
	assert(f == 0);
	assert(0 == string_to_double("0.0"));
	assert(string_to_float("0.0", &f));
	assert(f == 0);
	assert(0 == string_to_double("0.00"));
	assert(string_to_float("0.00", &f));
	assert(f == 0);
	assert(0 == string_to_double("0.0e0"));
	assert(string_to_float("0.0e0", &f));
	assert(f == 0);

	assert(0 == string_to_double("0.0e-0"));
	assert(0 == string_to_double("0.0e+0"));
	assert(0 == string_to_double("+0"));
	assert(0 == string_to_double("+0."));
	assert(0 == string_to_double("+0.0"));
	assert(0 == string_to_double("+0.00"));
	assert(0 == string_to_double("+0.0e0"));
	assert(0 == string_to_double("+0.0e-0"));
	assert(0 == string_to_double("+0.0e+0"));
	assert(0 == string_to_double("-0"));
	assert(0 == string_to_double("-0."));
	assert(0 == string_to_double("-0.0"));
	assert(0 == string_to_double("-0.00"));
	assert(0 == string_to_double("-0.0e0"));
	assert(0 == string_to_double("-0.0e-0"));
	assert(0 == string_to_double("-0.0e+0"));

	assert(0 == string_to_double("foobar"));
	assert(!string_to_float("foobar", &f));

	cout << "Please enter two numbers you wish "
		<< "to add, separated by a white space:"
		<< endl;

	string num1, num2;
	//cin.getline(num1, STRLEN);
	//if (cin.fail()) {
	//	cin.clear();
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//}
	cin.clear(); // Clear stream status.
	cin >> skipws >> setw(3) >> num1;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// Ignore to the end of line
	if (cin.bad()) {
		cerr << "Input stream corrupted.\n"; // Stream corrupted.
		exit(EXIT_FAILURE);
	}
	if (num1.find_first_not_of("1234567890.-+") != string::npos) {
		cout << "Invalid entry: " << num1 << endl;
		return 0;
	}

	cin >> skipws >> num2;
	if (num2.find_first_not_of("1234567890.-+") != string::npos) {
		cout << "invalid number: " << num2 << endl;
		return 0;
	}

	float x = 0, y = 0, z = 0;
	x = atof(num1.c_str());
	y = atof(num2.c_str());
	z = x + y;

	cout << x << " + " << y << " = " << z << endl;

	std::string input = "\t\tHELLO WORLD\r\nHELLO\t\nWORLD     \t";
	auto rs = std::regex_replace(input, std::regex("\\s+"), "");
	std::cout << rs << std::endl;
	
	return 0;
}
*/
