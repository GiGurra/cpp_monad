#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

template<typename T>
using MapContainerType = std::vector<T>;

auto transform = [](const auto& src, auto& trg, auto fcn) {
	std::transform(std::begin(src), std::end(src), std::back_inserter(trg), fcn);
};

auto copyIf = [](const auto& src, auto& trg, auto fcn) {
	std::copy_if(std::begin(src), std::end(src), std::back_inserter(trg), fcn);
};

auto getFirstElem = [](const auto& src) {
	return src[0];
};

auto filter = [](const auto& src, auto fcn) {
	MapContainerType<decltype(getFirstElem(src))> out;
	copyIf(src, out, fcn);
	return out;
};

auto map = [](const auto& src, auto fcn) {
	MapContainerType<decltype(fcn(src[0]))> out;
	transform(src, out, fcn);
	return out;
};

auto flatten = [](const auto& src) {
	MapContainerType<decltype(getFirstElem(getFirstElem(src)))> out;
	for (std::size_t i = 0; i < src.size(); i++) {
		const auto& srcLine = src[i];		
		for (std::size_t e = 0; e < srcLine.size(); e++) {
			out.push_back(srcLine[e]);		
		}	
	}
	return out;
};

auto flatMap = [](const auto& src, auto fcn) {
	auto mapped = map(src, fcn);
	auto flattened = flatten(mapped);
	return flattened;
};

auto printAll = [](const auto& src, const std::string& title) {
	std::cout << "Printing " << title << std::endl;
	for (const auto& x : src) {
		std::cout << "  elem: " << x << std::endl;
	}
};

template<typename CollType>
class Monadic {
public:
	Monadic(CollType col) : col(col) {}

	template <typename T> static Monadic<T> monadic(T c) { return Monadic<T>(c); }
	template <typename MapFcn> auto map(MapFcn mapFcn) { return monadic(::map(col, mapFcn)); }
	template <typename MapFcn> auto filter(MapFcn filterFcn) { return monadic(::filter(col, filterFcn)); }
	template <typename MapFcn> auto flatMap(MapFcn mapFcn) { return monadic(::flatMap(col, mapFcn)); }

	CollType col;
};

template<typename CollType>
Monadic<CollType> monadic(CollType c) {
	return Monadic<CollType>::monadic(c);
}

int main() {

	const std::vector<int> src = { 1, 2, 3 };

	auto squares = map(src, [](auto x) {return x*x;});
	auto largerThan1 = filter(src, [](auto x) {return x > 1;});
	auto strings = map(src, [](auto x) {return std::to_string(x);});

	auto m = monadic(src);

	auto mMapped = m.map([](auto x) {return x*x;});
	auto mFiltered = m.filter([](auto x) {return x > 1;});

	printAll(src, "src");
	printAll(largerThan1, "largerThan1");
	printAll(strings, "strings");
	printAll(squares, "squares");

	printAll(mMapped.col, "mMapped");

	std::vector<std::vector<int>> intLists;
	intLists.push_back(src);

	std::vector<std::vector<int>> mapped = map(src, [](auto x) { return std::vector<int>{1,2,3};} );
	std::vector<int> flatMapped = flatMap(src, [](auto x) { return std::vector<int>{1,2,3};} );
	std::vector<int> flattened = flatten(mapped);

	return 0;
}

