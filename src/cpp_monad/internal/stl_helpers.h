#ifndef CPP_MONAD_DEFAULT_STL_HELPERS_H_
#define CPP_MONAD_DEFAULT_STL_HELPERS_H_

namespace cpp_monad {
namespace internal {

template <typename T_Coll>
auto _firstElem(const T_Coll& src) {
	return *src.begin();
};

}
}

#endif /* CPP_MONAD_DEFAULT_STL_HELPERS_H_ */