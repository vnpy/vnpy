#include <cstdio>
#include "gtest/gtest.h"

#include <wrapper_helper.h>
#include <future>
#include <random>


class MokerClass
{
public:
    void sum(int val, int *val2)
    {
        int _sum = val + *val2;
        p.set_value(_sum);
    }

    void sum_delay(int val, int *val2, std::chrono::seconds delay)
    {
        std::this_thread::sleep_for(delay);
        int _sum = val + *val2;
        p.set_value(_sum);
    }
public:
    std::promise<int> p;
};

// The fixture for testing class Foo.
class callback_wrapper_test : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    callback_wrapper_test() {
        // You can do set-up work for each test here.
    }

    ~callback_wrapper_test() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        dispatcher::instance().start();
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
        printf("ask dispatcher to stop ...\n");
        dispatcher::instance().stop();
        dispatcher::instance().join();
        printf("dispatcher stopped!\n");
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    MokerClass m;
    MokerClass *instance = &m;
    std::random_device rd;
    std::mt19937 mt = std::mt19937(rd());
    std::uniform_int_distribution<int> dis;
};

// tests:

// * function is really called
TEST_F(callback_wrapper_test, async) {
    int val1 = dis(mt);
    int *val2 = new int(dis(mt));
    int excepted_sum = val1 + *val2;
    callback_wrapper<&MokerClass::sum>::async(instance, "", val1, val2);

    auto result = m.p.get_future().get();
    EXPECT_EQ(excepted_sum, result);
}

TEST_F(callback_wrapper_test, sync) {
    int val1 = dis(mt);
    int *val2 = new int(dis(mt));
    int excepted_sum = val1 + *val2;
    callback_wrapper<&MokerClass::sum>::sync(instance, "", val1, val2);

    auto result = m.p.get_future().get();
    EXPECT_EQ(excepted_sum, result);
}

// * after pointer is deleted, that method should be still called because value is always copied in async call
TEST_F(callback_wrapper_test, async_pointer) {
    int val1 = dis(mt);
    int *val2 = new int(dis(mt));
    int excepted_sum = val1 + *val2;
    callback_wrapper<&MokerClass::sum_delay>::async(instance, "", val1, val2, std::chrono::seconds(1));
    delete val2;

    auto result = m.p.get_future().get();
    EXPECT_EQ(excepted_sum, result);
}

// * after pointer is deleted, that method should be still called because value is always copied in async call
// * this is also a stress test
TEST_F(callback_wrapper_test, async_sequential) {
    int n = 1000000;
    std::vector<int> val1s;
    std::vector<int> val2s;
    std::vector<int> excepted_results;
    excepted_results.reserve(n);
    std::vector<MokerClass> ms;
    ms.reserve(n);
    printf("generating tasks\n");
    for (int i=0; i< n; i++)
    {
        int val1 = dis(mt);
        int val2 = dis(mt);
        int excepted_sum = val1 + val2;

        val1s.push_back(val1);
        val2s.push_back(val2);
        excepted_results.push_back(excepted_sum);
        ms.emplace_back();
    }
    printf("pushing tasks\n");
    for (int i = 0; i < n; i++)
    {
        auto &val1 = val1s.at(i);
        auto &val2 = val2s.at(i);
        auto &m = ms.at(i);
        callback_wrapper<&MokerClass::sum>::async(&m, "", val1, &val2);
    }
    printf("tasks generated and pushed!\n");

    for (int i = 0; i < n; i++)
    {
        int excepted_sum = excepted_results.at(i);
        int result = ms.at(i).p.get_future().get();
        EXPECT_EQ(excepted_sum, result);
    }
    printf("task checked!\n");
}

#ifdef ARDUINO
void setup() {
    // Since Arduino doesn't have a command line, fake out the argc/argv arguments
    int argc = 1;
    const auto arg0 = "PlatformIO";
    char* argv0 = const_cast<char*>(arg0);
    char** argv = &argv0;

    testing::InitGoogleTest(&argc, argv);
}

void loop() { RUN_ALL_TESTS(); }

#else

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
