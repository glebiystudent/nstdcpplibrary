
# ::nstd
quick examples to demonstrate different modules

### \<utility\>
```cpp
std::string input = "hi";

nstd::switch_string(input, 
"hi", [](){
    std::cout << "why are you here?\n"; // this was ran
},  
"__default", [](){
    std::cout << "this is gonna be ran someday..\n";
});
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
nstd::benchmark  b([](){
	nstd::repeat(1000000, [](){ // <utility>
		int i = 10;
		i++; i *= 20;
		i--; i /= 20;
		i = 0;
	});
}, 100); // 100 = optional argument for finding the mean amongst all 100 benchmark runs

std::cout << b.evaluate() << "\n"; // 5.4944 (milliseconds)
```
### \<log\>
```cpp
auto vec = nstd::vector<int>(30, 90, 100, -1, -6);
auto map = nstd::unordered_map<int, std::string>(10, "something", -60, "other", -1, "wow");
auto stack = nstd::stack<int>(-1, -99, 666, 300, 99500);

nstd::log(vec, "\n", map, "\n", stack, 30, "\nhello world", false, "something??");
// [vector: {30, 90, 100, -1, -6}]
// [unordered_map: {(-1: wow), (-60: other), (10: something)}]
// [stack: {99500, 300, 666, -99, -1}] 30
// hello world 0 something??
```
### \<argsindexing\>
```cpp
nstd::args_even([](auto idx, auto e){ std::cout << idx << ": " << e << "\n"; }, 30, 90, "hi", -1, "whaa..");
// 0: 30
// 2: hi
// 4: whaa..
```