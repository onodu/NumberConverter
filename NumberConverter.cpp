#include "NumberConverter.h"



std::string NumberConverter::operator() (const std::string &inputNumber, unsigned base1, unsigned base2, unsigned digitsAfterPoint)
{
	m_base1 = base1;
	m_base2 = base2;
	m_digitsAfterPoint = digitsAfterPoint;
	
	if(std::min(m_base1, m_base2) < minBase() || std::max(m_base1, m_base2) > maxBase())
	{
		std::stringstream os;
		os << "Base of a numeral system must be from " << minBase() << " to " << maxBase() << ".";
		throw std::runtime_error(os.str());
	}

	const std::pair<std::string, std::string> pa = parseIntFractPart(inputNumber);
	const std::string intPartStr = pa.first;
	const std::string fractPartStr = pa.second;

	const integer_t intPart = toInteger(intPartStr);
	const rational_t fractPart(toInteger(fractPartStr), pow(integer_t(m_base1), fractPartStr.size()));
	
	std::string s = toString(intPart);
	if(!!fractPart && m_digitsAfterPoint > 0)
	{
		std::string s2 = fractionPartToString(fractPart);
		s += "." + s2;
	}
	
	return s;
}

NumberConverter::integer_t NumberConverter::pow(integer_t a, unsigned n)
{
	if(a == 1) return a;
	integer_t res = 1;
	while(n)
	{
		if(n % 2 == 1) res *= a;
		n /= 2;
		if(n) a *= a;
	}
	return res;

}

void NumberConverter::divide(unsigned &r, integer_t &q, integer_t a, unsigned b)
{
	q = a / b;
	r = static_cast<unsigned>(a - q * b);
}



std::string NumberConverter::toString(integer_t num) const
{
	std::string res;
	if(!num) return "0";
	while(!!num)
	{
		integer_t q;
		unsigned r;
		divide(r, q, num, m_base2);
		res += digits()[r];
		num.swap(q);
	}
	std::reverse(res.begin(), res.end());
	return res;
}

std::string NumberConverter::to_string(const integer_t &a)
{
	std::stringstream s;
	s << a;
	return s.str();
}

std::string NumberConverter::to_string(const rational_t &a)
{
	std::stringstream s;
	s << a;
	return s.str();
}

NumberConverter::integer_t NumberConverter::toInteger(const std::string &inputNumber) const
{
	//std::string temp1, temp2;

	integer_t num = 0, num2 = 1;
	for(auto it = inputNumber.rbegin(); it != inputNumber.rend(); ++it)
	{
		const char c = *it;

		auto it2 = std::find(digits().begin(), digits().end(), c);
		const unsigned num3 = it2 - digits().begin();

		num += num2 * num3;
		num2 *= m_base1;

		//temp1 = to_string(num);
		//temp2 = to_string(num2);
	}
	
	return num;
}


NumberConverter::rational_t NumberConverter::fract(rational_t num)
{
	return num - floor(num);
}

NumberConverter::integer_t NumberConverter::floor(rational_t num)
{
	using namespace boost::multiprecision;
	integer_t num2 = numerator(num) / denominator(num);
	if(rational_t(num2) > num) --num2;
	return num2;
}

std::string NumberConverter::fractionPartToString(rational_t num) const
{
	std::string res;

	//std::string temp1, temp2;
	for(unsigned i = 0; i < m_digitsAfterPoint; i++)
	{
		//temp1 = to_string(num);

		num = fract(num) * rational_t(m_base2);
		//temp2 = to_string(num);

		if(!num) break;
		unsigned num3 = static_cast<unsigned>(floor(num));
		res += digits()[num3];
	}
	return res;
}

const std::vector<char>& NumberConverter::digits()
{
	static std::unique_ptr<std::vector<char> > vec;
	if(!vec)
	{
		vec = std::unique_ptr<std::vector<char> > (new std::vector<char>());
		for(int c = '0'; c <= '9'; c++) vec->push_back(c);
		for(int c = 'a'; c <= 'z'; c++) vec->push_back(c);
	}
	return *vec;
}

unsigned NumberConverter::minBase() const
{
	return 2;
}

unsigned NumberConverter::maxBase() const
{
	return digits().size();
}


std::pair<std::string, std::string> NumberConverter::parseIntFractPart(std::string s)
{
	std::string intPartStr, fractPartStr;
	s = boost::algorithm::to_lower_copy(s);
	auto it = s.begin();
	while(it != s.end() && *it != '.')
	{
		auto it2 = std::find(digits().begin(), digits().end(), *it);
		const unsigned num = it2 - digits().begin();
		if(it2 == digits().end() || num >= m_base1) break;
		intPartStr += *it;
		++it;
	}
	if(it == s.end())
	{
		return std::make_pair(intPartStr, "");
	}
	if(*it != '.')
	{
		throw ParserException(std::string("Invalid character \'") + *it + "\'.", it - s.begin());
	}
	++it;

	while(it != s.end())
	{
		auto it2 = std::find(digits().begin(), digits().end(), *it);
		const unsigned num = it2 - digits().begin();
		if(it2 == digits().end() || num >= m_base1) break;
		fractPartStr += *it;
		++it;
	}
	if(it == s.end())
	{
		return std::make_pair(intPartStr, fractPartStr);
	}
	else
	{
		throw ParserException(std::string("Invalid character \'") + *it + "\'.", it - s.begin());
	}
}
