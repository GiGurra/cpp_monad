#ifndef CPP_MONAD_DEFAULT_COMBINATORS_H_
#define CPP_MONAD_DEFAULT_COMBINATORS_H_

#include <vector>
#include <algorithm>
#include <iterator>

namespace cpp_monad {

template <typename T_SrcColl, typename T_TrgColl, typename T_MapFcn>
void _transform(const T_SrcColl& src, T_TrgColl& trg, T_MapFcn fcn) {
	std::transform(std::begin(src), std::end(src), std::back_inserter(trg), fcn);
};

template <typename T_Coll, typename T_FilterFcn>
void _copyIf(const T_Coll& src, T_Coll& trg, T_FilterFcn fcn) {
	std::copy_if(std::begin(src), std::end(src), std::back_inserter(trg), fcn);
};

template <typename T_Coll>
auto _firstElem(const T_Coll& src) {
	return *src.begin();
};

template <typename T_Coll, typename T_FilterFcn>
auto filter(const T_Coll& src, T_FilterFcn fcn) {
	std::vector<decltype(_firstElem(src))> out;
	_copyIf(src, out, fcn);
	return out;
};

template <typename T_Coll, typename T_MapFcn>
auto map(const T_Coll& src, T_MapFcn fcn) {
	std::vector<decltype(fcn(_firstElem(src)))> out;
	_transform(src, out, fcn);
	return out;
};

template <typename T_Coll>
auto flatten(const T_Coll& src) {
	std::vector<decltype(_firstElem(_firstElem(src)))> out;
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
