#include "ValueUtils.hpp"

#include <type_traits>

namespace fort {
namespace myrmidon {

template<class> inline constexpr bool always_false_v = false;

ValueType ValueUtils::Type(const Value & value) {
	return std::visit([](auto&& arg) -> ValueType {
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, bool>) {
			return ValueType::BOOL;
		} else if constexpr (std::is_same_v<T, int>) {
			return ValueType::INT;
		} else if constexpr (std::is_same_v<T, double>) {
			return ValueType::DOUBLE;
		} else if constexpr (std::is_same_v<T, std::string>) {
			return ValueType::STRING;
		} else if constexpr (std::is_same_v<T, fort::Time>) {
			return ValueType::TIME;
		} else {
			static_assert(always_false_v<T>, "non-exhaustive visitor!");
		}
	}, value);
}

const std::string & ValueUtils::TypeName(ValueType type) {
	static std::vector<std::string> names =
		{ "Bool","Int","Double","String","Time"};
	size_t idx = size_t(type);
	if ( idx >= names.size() ) {
		throw std::invalid_argument("Unknown ValueType value "
		                            + std::to_string(idx));
	}
	return names.at(idx);
}

std::string ValueUtils::TypeName(const Value & value) {
	return TypeName(Type(value));
}


Value ValueUtils::Default(ValueType type) {
	static std::vector<Value> defaults =
		{
		 false,
		 0,
		 0.0,
		 std::string(""),
		 Time(),
		};

	size_t idx = size_t(type);
	if ( idx >= defaults.size() ) {
		throw std::invalid_argument("Unknown ValueType value "
		                            + std::to_string(idx));
	}

	return defaults[idx];
}

Value ValueUtils::Parse(ValueType type, const std::string & str) {
	auto value = Default(type);
	std::visit([&str](auto &&arg) {
		using T = std::decay_t<decltype(arg)>;
		if constexpr ( std::is_same_v<T, bool> ) {
			std::istringstream iss(str);
			bool res;
			iss >> std::boolalpha >> res;
			if ( iss.good() == false ) {
				throw std::invalid_argument("Invalid string '"
				                            + str
				                            + "' for AntMetadata::Value");
			 }
			 arg = res;
		} else if constexpr ( std::is_same_v<T,int32_t> ) {
			arg = std::stoi(str);
		} else if constexpr ( std::is_same_v<T,double> ) {
			arg = std::stod(str);
		} else if constexpr ( std::is_same_v<T,std::string> ) {
			arg = str;
		} else if constexpr ( std::is_same_v<T,Time> ) {
			arg = Time::Parse(str);
		} else {
			static_assert(always_false_v<T>, "non-exhaustive visitor!");
		}
	},value);
	return value;
}

ValueUtils::ValuedTimeRangeList
ValueUtils::BuildRanges(const std::map<Time,Value> & values) {
	return {};
	/*
	for ( auto iter = values.begin();
	      iter != values.end();
	      ++iter) {
		if ( !(iter->second == value) ) {
			continue;
		}
		auto next = iter;
		while ( next != values.end() && next->second == value ) {
			++next;
		}
		if ( next == values.end() ) {
			res.push_back({antID,iter->first,Time::Forever()});
		} else {
			res.push_back({antID,iter->first,next->first});
		}
		iter = --next;
	}
	*/
}





} // namespace myrmidon
} // namespace fort