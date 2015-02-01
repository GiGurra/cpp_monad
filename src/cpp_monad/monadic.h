#ifndef CPP_MONAD_MONADIC
#define CPP_MONAD_MONADIC

namespace cpp_monad {
    
template<typename CollType>
class Monadic {
public:
	Monadic(CollType col) : col(col) {}

	template <typename T> 
	static Monadic<T> monadic(T c) { return Monadic<T>(c); }

	template <typename MapFcn> 
	auto map(MapFcn mapFcn) { return monadic(::map(col, mapFcn)); }

	template <typename MapFcn> 
	auto filter(MapFcn filterFcn) { return monadic(::filter(col, filterFcn)); }

	template <typename MapFcn> 
	auto flatMap(MapFcn mapFcn) { return monadic(::flatMap(col, mapFcn)); }

	auto flatten() { return monadic(::flatten(col)); }

	CollType col;
};

template<typename CollType>
Monadic<CollType> monadic(CollType c) {
	return Monadic<CollType>::monadic(c);
}

}

#endif /* CPP_MONAD_MONADIC */
