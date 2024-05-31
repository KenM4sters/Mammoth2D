add_test([=[ExampleTest.Test]=]  /Users/samuelbrookman/Desktop/unitTesting/build/Tests/UnitTests/ExampleTest [==[--gtest_filter=ExampleTest.Test]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExampleTest.Test]=]  PROPERTIES WORKING_DIRECTORY /Users/samuelbrookman/Desktop/unitTesting/build/Tests/UnitTests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  ExampleTest_TESTS ExampleTest.Test)
