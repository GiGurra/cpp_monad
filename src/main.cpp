#include <cpp_monad/default_combinators.h>
#include <cpp_monad/monadic.h>

#include <iostream>
#include <string>

using namespace cpp_monad;

template <typename T_Coll>
auto printAll(const T_Coll& src, const std::string& title) {
	std::cout << "Printing " << title << std::endl;
	for (const auto& x : src) {
		std::cout << "  elem: " << x << std::endl;
	}
};

int main() {

	const std::vector<int> src = { 1, 2, 3 };

	auto squares = map(src, [](int x) {return x*x;});
	auto largerThan1 = filter(src, [](int x) {return x > 1;});
	auto strings = map(src, [](int x) {return std::to_string(x);});

	Monadic<std::vector<int>> m(src);

	auto mMapped = m.map([](int x) {return x*x;});
	auto mFiltered = m.filter([](int x) {return x > 1;});

	printAll(src, "src");
	printAll(largerThan1, "largerThan1");
	printAll(strings, "strings");
	printAll(squares, "squares");

	printAll(mMapped.col, "mMapped");

	std::vector<std::vector<int>> intLists;
	intLists.push_back(src);

	std::vector<std::vector<int>> mapped = map(src, [](int x) { return std::vector<int>{1,2,3};} );
	std::vector<int> flatMapped = flatMap(src, [](int x) { return std::vector<int>{1,2,3};} );
	std::vector<int> flattened = flatten(mapped);

	std::vector<int> funList = 
		monadic(src)
			.map([](int x) { return std::vector<int>{1,2,3};} )
			.flatten()
			.filter([](int x) { return x > 1; })
			.col;

	printAll(funList, "funList");

	return 0;
}

