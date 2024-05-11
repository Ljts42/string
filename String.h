#pragma once

#include <cstring>
#include <ostream>

class String
{
	size_t m_size;
	size_t m_capacity;
	char* m_data;

public:
	String();
	String(const char*, size_t);
	String(const String&);
	String(String&&) noexcept;

	String& operator = (const char*);
	String& operator = (const String&);
	String& operator = (String&&) noexcept;

	String& operator += (const char*);
	String& operator += (const String&);

	char& operator [] (size_t);
	const char& operator [] (size_t) const;
	size_t size() const;

	~String();

	friend String operator + (const String&, const char*);
	friend String operator + (const String&, const String&);
	friend std::ostream& operator << (std::ostream&, const String&);
};
