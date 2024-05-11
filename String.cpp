#define _CRT_SECURE_NO_WARNINGS

#include "String.h"

String::String()
	: String(nullptr, 0)
{}

String::String(const char* other, size_t count = std::numeric_limits<size_t>::max())
{
	if (other != nullptr) {
		m_size = std::min(count, strlen(other));
		m_capacity = m_size ? m_size * 2 : 1;
		m_data = new char[m_capacity];
		strncpy(m_data, other, m_size);
		m_data[m_size] = '\0';
	}
	else {
		m_size = 0;
		m_capacity = 1;
		m_data = new char[1];
		*m_data = '\0';
	}
}

String::String(const String& other)
	: String(other.m_data, other.m_size)
{}

String::String(String&& other) noexcept
	: m_size(0)
	, m_capacity(0)
	, m_data(nullptr)
{
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_data, other.m_data);
}

String& String::operator = (const char* other)
{
	if (other != nullptr) {
		m_size = strlen(other);
		if (m_capacity <= m_size) {
			delete[] m_data;
			m_capacity = m_size * 2;
			m_data = new char[m_capacity];
		}
		strncpy(m_data, other, m_size + 1);
	}
	else {
		delete[] m_data;
		m_size = 0;
		m_capacity = 1;
		m_data = new char[1];
		*m_data = '\0';
	}
	return *this;
}

String& String::operator = (const String& other)
{
	if (this != &other) {
		m_size = other.m_size;
		if (m_capacity < other.m_capacity) {
			delete[] m_data;
			m_capacity = other.m_capacity;
			m_data = new char[m_capacity];
		}
		strncpy(m_data, other.m_data, m_size + 1);
	}
	return *this;
}

String& String::operator = (String&& other) noexcept
{
	if (this != &other) {
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_data, other.m_data);
	}
	return *this;
}

String& String::operator += (const char* other)
{
	size_t len = strlen(other);
	if (m_size + len >= m_capacity) {
		m_capacity = (m_capacity + len) * 2;
		char* tmp = new char[m_capacity];
		strncpy(tmp, m_data, m_size);
		delete[] m_data;
		m_data = tmp;
	}
	strncpy(m_data + m_size, other, len);
	m_size += len;
	m_data[m_size] = '\0';
	return *this;
}

String& String::operator += (const String& other)
{
	if (m_size + other.m_size >= m_capacity) {
		m_capacity += other.m_size * 2;
		char* tmp = new char[m_capacity];
		strncpy(tmp, m_data, m_size);
		delete[] m_data;
		m_data = tmp;
	}
	strncpy(m_data + m_size, other.m_data, other.m_size);
	m_size += other.m_size;
	m_data[m_size] = '\0';
	return *this;
}

char& String::operator [] (size_t pos)
{
	return m_data[pos];
}

const char& String::operator [] (size_t pos) const
{
	return m_data[pos];
}

size_t String::size() const
{
	return m_size;
}

String::~String()
{
	delete[] m_data;
}

String operator + (const String& lhs, const char* rhs)
{
	String result(lhs);
	result += rhs;
	return result;
}

String operator + (const String& lhs, const String& rhs)
{
	String result(lhs);
	result += rhs;
	return result;
}

std::ostream& operator << (std::ostream& out, const String& str)
{
	if (str.m_data != nullptr) {
		out.write(str.m_data, str.m_size);
	}
	return out;
}
