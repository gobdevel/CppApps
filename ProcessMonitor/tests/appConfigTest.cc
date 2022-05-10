#include <filesystem>
#include <iostream>

#include "appConfig.h"
#include "gtest/gtest.h"

TEST(Config, simple) {
    ProcessMonitor::AppConfig app1("App1", "-I, op", true);
    ProcessMonitor::AppConfig app2("App2", "-I, op", false);

    auto app3 = app1;
    EXPECT_EQ(app3, app1);
    EXPECT_NE(app2, app1);
    EXPECT_TRUE(app2 != app1);

    auto app4(std::move(app1));
    EXPECT_NE(app4, app1);
    std::cout << "Current Dir : " << std::filesystem::current_path() << "\n";
}

TEST(Config, Parse) {
    auto apps = ProcessMonitor::AppConfigParser::parse("testConfig.txt");
    EXPECT_EQ(apps.size(), 3);

    EXPECT_EQ(apps[0].getApp(), "/bin/process1");
}
