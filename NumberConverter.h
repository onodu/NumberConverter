#ifndef NUMBERCONVERTER_H
#define NUMBERCONVERTER_H 1


#include <algorithm>
#include <atomic>
#include <cctype>
#include <sstream>
#include <string>
#include <memory>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/algorithm/string.hpp>


class NumberConverter
{
public:
	std::string operator() (const std::string &inputNumber = "0", unsigned base1 = 10, unsigned base2 = 10, unsigned digitsAfterPoint = 0);

	unsigned minBase() const;
	unsigned maxBase() const;

	class ParserException : std::exception
	{
	public:
		ParserException(const std::string &msg, int pos) : m_msg(msg), m_pos(pos)
		{}

		const char * what() const noexcept override
		{
			return m_msg.c_str();
		}

		int pos() const
		{
			return m_pos;
		}

	private:
		std::string m_msg;
		int m_pos;
	};

private:
	typedef boost::multiprecision::cpp_int integer_t;
	typedef boost::multiprecision::cpp_rational rational_t;

	static const std::vector<char>& digits();
	static void divide(unsigned &r, integer_t &q, integer_t a, unsigned b);
	static rational_t fract(rational_t num);
	static integer_t floor(rational_t num);
	static integer_t pow(integer_t a, unsigned n);
	static std::string to_string(const integer_t &a);
	static std::string to_string(const rational_t &a);
	std::pair<std::string, std::string> parseIntFractPart(std::string s);

	std::string toString(integer_t num) const;
	integer_t toInteger(const std::string &inputNumber) const;
	std::string fractionPartToString(rational_t num) const;
	static std::string removeSpaces(std::string s);

	unsigned m_base1, m_base2, m_digitsAfterPoint;

	
};

#endif // NUMBERCONVERTER_H
