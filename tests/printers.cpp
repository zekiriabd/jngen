#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "../jngen.h"

#include <vector>
#include <utility>

template<typename T>
void checkOutput(const T& t, const std::string& s) {
    std::ostringstream ss;
    ss << t;
    BOOST_CHECK_EQUAL(ss.str(), s);
}

BOOST_AUTO_TEST_CASE(vector_depth) {
    using jngen::detail::VectorDepth;
    BOOST_CHECK(VectorDepth<int>::value == 0);
    BOOST_CHECK(VectorDepth<std::vector<int>>::value == 1);
    BOOST_CHECK(VectorDepth<
        std::vector<std::vector<double>>>::value == 2);
    typedef std::pair<int, int> Pair;
    BOOST_CHECK(VectorDepth<
        std::vector<std::vector<std::vector<Pair>>>>::value == 3);
}

#undef COMMAdjdji

BOOST_AUTO_TEST_CASE(trivial) {
    setMod().reset();

    checkOutput(repr(1), "1");
    checkOutput(repr(1.1), "1.1");
    checkOutput(repr("hello"), "hello");
    checkOutput(repr(std::string{"world"}), "world");
    checkOutput(repr(1).add1(), "2");
    checkOutput(repr(std::pair<int, int>{2, 3}), "2 3");
}

BOOST_AUTO_TEST_CASE(array) {
    setMod().reset();

    checkOutput(Array{1, 2, 3}, "1 2 3");
    checkOutput(Array64{1, 2, 3}, "1 2 3");
    checkOutput(Arrayf{1.1, 2.2, 3.3}, "1.1 2.2 3.3");
    checkOutput(Arrayp{{1, 2}, {3, 4}}, "1 2\n3 4");
    checkOutput(TArray<std::string>{"hello", "world"}, "hello world");
    checkOutput(TArray<const char*>{"jino", "tega"}, "jino tega");
}
