#pragma once

#include <fort/time/Time.hpp>

#include <QString>


template <typename T>
inline std::string ToString(const T & t) {
	std::ostringstream os;
	os << t;
	return os.str();
}

template <>
inline std::string ToString<bool>(const bool & t) {
	std::ostringstream os;
	os << std::boolalpha << t;
	return os.str();
}

template <class T>
std::string ToString(const std::shared_ptr<T> & ptr) {
	return ToString(*ptr);
};


template <typename T>
inline QString ToQString(const T & t) {
	return ToString(t).c_str();
}


inline std::string ToStdString(const QString & s) {
	return s.toUtf8().constData();
}
