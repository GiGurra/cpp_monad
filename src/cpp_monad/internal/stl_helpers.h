#ifndef CPP_MONAD_DEFAULT_STL_HELPERS_H_
#define CPP_MONAD_DEFAULT_STL_HELPERS_H_

#include <algorithm>
#include <iterator>

namespace cpp_monad {
namespace internal {

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

}
}

#endif /* CPP_MONAD_DEFAULT_STL_HELPERS_H_ */