#include <iostream>

#include "estring.hpp"

using namespace std;

// take a line and split it into a vector
svector str::split(str split, uint limit) {
	svector list;
	size_t end,pos = 0;
	
	while(true) {
		end = find(split,pos);
		list.push_back(substr(pos,end-pos));
		pos = end + split.size();
		if(end == string::npos) break;
		if(limit != 0) {
			if(list.size() >= limit) {
				list.push_back(substr(pos));
				break;
			}
		}	
	}
	
	return list;
}

// combine a svector and replace string
void str::join(str sept, svector &list) {
	assign(list[0]);
	for(uint i = 1; i < list.size(); i++) {
		append(sept);
		append(list[i]);
	}
}

// append a svector to the string
void str::ajoin(str sept, svector &list) {
	for(uint i = 0; i < list.size(); i++) {
		append(sept);
		append(list[i]);
	}
}

// counts how many times it appears
uint str::count(const str s) const {
	uint total = 0;
	size_t end,pos = 0;
	
	while(true) {
		end = find(s,pos);
		if(end == string::npos)
			break;
		pos = end + s.size();
		total++;
	}
	return total;
}

bool str::islower() const {
	bool Bool = true;
	if (length() == 0)
		Bool = false;
	else {
		for(const_iterator i = begin(); i != end(); i++) {
			if(*i >= 'A' && *i <= 'Z') {
				Bool = false;
				break;
			}
		}
	}
	return Bool;
}

bool str::isupper() const {
	bool Bool = true;
	if (length() == 0)
		Bool = false;
	else {
		for(const_iterator i = begin(); i != end(); i++) {
			if(*i >= 'a' && *i <= 'z') {
				Bool = false;
				break;
			}
		}
	}
	return Bool;
}

bool str::isint() const {
	bool Bool = true;
	if (length() == 0)
		Bool = false;
	else {
		for(const_iterator i = begin(); i != end(); i++) {
			if(*i < '0' || *i > '9') {
				Bool = false;
				break;
			}
		}
	}
	return Bool;
}

bool str::isfloat() const {
	bool Bool = true;
	if (length() == 0)
		Bool = false;
	else if( count(".") != 1 )
		Bool = false;
	else {
		for(const_iterator i = begin(); i != end(); i++) {
			if((*i < '0' || *i > '9') && *i != '.') {
				Bool = false;
				break;
			}
		}
	}
	return Bool;
}

bool str::isalpha() const {
	bool Bool = true;
	if (length() == 0)
		Bool = false;
	else {
		for(const_iterator i = begin(); i != end(); i++) {
			if((*i < 'a' || *i > 'z') && (*i < 'A' || *i > 'Z') && *i != ' ') {
				Bool = false;
				break;
			}
		}
	}
	return Bool;
}

str str::lower() {
	for(iterator i = begin(); i != end(); i++) {
		if(*i >= 'A' && *i <= 'Z') 
			*i += ('a' - 'A');
	}
	return *this;
}

str str::upper() {
	for(iterator i = begin(); i != end(); i++) {
		if(*i >= 'a' && *i <= 'z') 
			*i -= ('a' - 'A');
	}
	return *this;
}