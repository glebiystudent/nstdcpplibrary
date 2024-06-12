
# ::nstd
quick examples to demonstrate different modules (library has more than just this)

### \<log\>
```cpp
// nstd::log allows you to log like you're not in C++
auto vec = nstd::vector<int>(30, 90, 100, -1, -6);
auto map = nstd::unordered_map<int, std::string>(10, "something", -60, "other", -1, "wow");
auto stack = nstd::stack<int>(-1, -99, 666, 300, 99500);

nstd::log(vec, "\n", map, "\n", stack, 30, "\nhello world", false, "something??");
// [vector: {30, 90, 100, -1, -6}]
// [unordered_map: {(-1: wow), (-60: other), (10: something)}]
// [stack: {99500, 300, 666, -99, -1}] 30
// hello world 0 something??
```
### \<utility\>
```cpp
// as you might know switch can't work with strings at all
std::string input = "hi";

nstd::switch_string(input, 
"hi", []{
	std::cout << "why are you here?\n"; // this was ran
},  
"__default", []{
	std::cout << "this is gonna be ran someday..\n";
});
```
```cpp
// 4 lines of code compressed into 1
auto [a, b, c, d] = nstd::var("hi", nstd::vector(10, 90, 30), 10, []{ std::cout << "wow\n"; });
nstd::log(a, b, c); // hi [vector: {10, 90, 30}] 10
d(); // wow
```
```cpp
// destructuring assignment like in javascript!
auto vec = nstd::vector(3, 9, -1);

auto [var1, var2, var3] = nstd::var("hello", false, nstd::vector(-1, -3, -100));
auto [e1, e2] = nstd::var<2>(vec);

nstd::log(var1, var2, var3, "\n", e1, e2);
// hello 0 [vector: {-1, -3, -100}]
// 3 9
```
### \<vector\>
```cpp
auto vec1 = nstd::vector(30, 90, -1, 900, 100);
auto vec2 = nstd::vector(-100, 9, -6, -4900, 0);
auto vec3 = nstd::vector(73, 89, 13, 987, 123);

auto merged = nstd::merge<int>(vec1, vec2, vec3);
if(nstd::every<int>(merged, [](auto e){ return e > -10000; })) {
	auto filtered = nstd::filter<int>(merged, [](auto e){ return e <= 0; });
	std::cout << nstd::concat(filtered, " "); // "-1 -100 -6 -4900 0"
}
```
### \<string\>
```cpp
std::string str = "c//orru/*---pted!(*#) //-str@@@ing...";
std::string healed = nstd::erase_characters(str, "!()@*#/-.");
auto parts = nstd::split(healed); // ["corrupted", "string"]
```
### \<benchmark\>
```cpp
nstd::benchmark  b([]{
	nstd::repeat(1000000, []{ // <utility>
		int i = 10;
		i++; i *= 20;
		i--; i /= 20;
		i = 0;
	});
}, 100); // 100 = optional argument for finding the mean amongst all 100 benchmark runs

std::cout << b.evaluate() << "\n"; // 5.4944 (milliseconds)
```
### \<argsindexing\>
```cpp
// ability to fluently work with infinite amount of arguments
nstd::args_even([](auto idx, auto e){ std::cout << idx << ": " << e << "\n"; }, 30, 90, "hi", -1, "whaa..");
// 0: 30
// 2: hi
// 4: whaa..
```

### using ::nstd  &  __compressed
```cpp
// __compressed is a feature allowing you to compress the library by ignoring extra/ modules
// although you won't have features such as nstd::log() & nstd::format()
// you can do it like this:
#define __compressed
#include "nstd/init.hpp" // use only this line if you want a full version of ::nstd
```
