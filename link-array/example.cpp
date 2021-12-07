// declaration:
extern const char* my_strings[];

// sizeof(my_strings) is always invalid as usual for extern arrays without size:
size_t sizeof_my_strings = sizeof(my_strings); // error: incomplete type const char*[]


// definition in translation unit 1:
const char* my_strings __partial_array[] = { "Hello" };

// sizeof(my_strings) is still invalid despite the visible partial definition
size_t sizeof_my_strings = sizeof(my_strings); // error incomplete type const char*[]


// multiple definitions in translation unit 2:
const char* my_strings __partial_array[] = { "world!" };
const char* my_strings __partial_array[] = { "foo", "bar" };


// possible actual array after linking:
const char* my_strings[4] = { "world!", "foo", "bar", "Hello" };

// actual size of the array can be queried at runtime:
size_t my_strings_size = __partial_array_size(my_strings);


// usage examples:

// unit_test.hpp
typedef void TestCaseCallback();
extern TestCaseCallback* const test_cases[];

#define TEST_CASE() \
	static void CAT(TEST_CASE_,__LINE__)();
	TestCaseCallback* const test_cases __partial_array[] = { CAT(TEST_CASE_,__LINE__) }; \
	static void CAT(TEST_CASE_,__LINE__)()


// unit_test.cpp
void RunUnitTests()
{
	TestCaseCallback* const* tests = test_cases;
	size_t test_count = __partial_array_size(test_cases);

	for (size_t i = 0; i < test_count; ++i)
	{
		tests[i]();
	}
}


// user_test.cpp
TEST_CASE()
{
	// Some unit test code...
}


// crypto library:

// hash.hpp
struct HashAlgorithm
{
	std::string_view name;
	// some more members...
};

extern const HashAlgorithm hash_algorithms[];

// md5.cpp
const HashAlgorithm hash_algorithms __partial_array[] = {
	HashAlgorithm{ "MD5", some_md5_thing },
};

// sha.cpp
const HashAlgorithm hash_algorithms __partial_array[] = {
	HashAlgorithm{ "SHA1", some_sha1_thing },
	HashAlgorithm{ "SHA256", some_sha256_thing },
};
