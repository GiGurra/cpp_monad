#ifndef CPP_MONAD_DEFAULT_COMBINATORS_H_
#define CPP_MONAD_DEFAULT_COMBINATORS_H_

#include <cpp_monad/internal/stl_helpers.h>
#include <vector>

namespace cpp_monad {

template <typename T_Coll, typename T_FilterFcn>
auto filter(const T_Coll& src, T_FilterFcn fcn) {
	std::vector<decltype(internal::_firstElem(src))> out;
	internal::_copyIf(src, out, fcn);
	return out;
};

template <typename T_Coll, typename T_MapFcn>
auto map(const T_Coll& src, T_MapFcn fcn) {
	std::vector<decltype(fcn(internal::_firstElem(src)))> out;
	internal::_transform(src, out, fcn);
	return out;
};

template <typename T_Coll>
auto flatten(const T_Coll& src) {
	std::vector<decltype(internal::_firstElem(internal::_firstElem(src)))> out;
	for (const auto& outer : src) {
		for (const auto& inner : outer) {
			out.push_back(inner);
		}	
	}
	return out;
};

template <typename T_Coll, typename T_MapFcn>
auto flatMap(const T_Coll& src, T_MapFcn fcn) {
	return flatten(map(src, fcn));
};

}

#endif /* CPP_MONAD_DEFAULT_COMBINATORS_H_ */
