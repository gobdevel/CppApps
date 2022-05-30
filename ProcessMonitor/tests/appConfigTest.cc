#include "appConfig.h"
#include "gtest/gtest.h"

using namespace ProcessMonitor;

TEST(AppConfig, ArgsParser) {
    Arg  arg("-I help");
    Args expected{"-I", "help"};
    EXPECT_EQ(AppConfigParser::parseArgs(arg), expected);

    arg      = "";
    expected = {};
    EXPECT_EQ(AppConfigParser::parseArgs(arg), expected);

    arg      = "-I in -O out -D";
    expected = {"-I", "in", "-O", "out", "-D"};
    EXPECT_EQ(AppConfigParser::parseArgs(arg), expected);
}

TEST(AppConfig, LineParser) {
    std::string line = "/usr/sbin/app1;-I in -O out;1";
    Args        args = {"-I", "in", "-O", "out"};
    AppConfig   expected("/usr/sbin/app1", args, true);
    EXPECT_EQ(AppConfigParser::parseLine(line), expected);
}

TEST(AppConfig, AppConfig) {
    AppConfig app1("App1", {"-I", "op"}, true);
    AppConfig app2("App2", {"-I", "op"}, false);

    auto app3 = app1;
    EXPECT_EQ(app3, app1);
    EXPECT_NE(app2, app1);
    EXPECT_TRUE(app2 != app1);

    auto app4(std::move(app1));
    EXPECT_NE(app4, app1);

    auto apps = ProcessMonitor::AppConfigParser::parse("testConfig.txt");
    for (const auto& app : apps) {
        std::cout << app << "\n";
    }
}
