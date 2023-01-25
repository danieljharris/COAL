#include <vector>
#include <string>
#include <sstream>

class str;
typedef std::vector<str> svector;
typedef unsigned int uint;

class str : public std::string {
	
public:
	// string constructor
	str() : std::string() { }
	str( const std::string& s ) : std::string( s ) { }
	str( const std::string& s, std::size_t n ) : std::string( s,n ) { }
	str( const char *s, std::size_t n ) : std::string( s,n ) { }
	str( const char *s ) : std::string( s ) { }
	str( std::size_t n, char c ) : std::string ( n,c ) { }
	template <class InputIterator>
	str( InputIterator first, InputIterator last ) : std::string( first,last ) { }

	// extended methods
	svector split(str split=" ", uint limit=0);
	void join(str sept, svector &list); // make new string 
	void ajoin(str sept, svector &list);
	uint count(const str s) const;
	
	str lower();
	str upper();
	
	bool islower() const;
	bool isupper() const;
	bool isint() const;
	bool isfloat() const;
	bool isalpha() const;
	
	// convert str into a number
	template <typename T>
	T convert() { 
		T result = 0;
		if(isint() or isfloat()) {
			std::stringstream stream;
			stream << *this;
			stream >> result;
		}
		return result;
	}
};