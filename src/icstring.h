
#include <iomanip> 

bool nocase_compare (char c1, char c2)
{
    return std::toupper(c1) == std::toupper(c2);
}

bool operator == (const std::string& a, const std::string& b)
{
	return (a.size() == b.size() && equal (a.begin(),a.end(), b.begin(), nocase_compare));
}

typedef std::string icstring;
