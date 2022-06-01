#ifndef __UTILS_H__
#define __UTILS_H__

#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <type_traits>
#include <vector>

namespace Utils {
template <typename T>
using remove_cv_ref_t = typename std::remove_cv_t<std::remove_reference_t<T>>;

template <typename Container>
void printThis(const Container& c) {
    for (const auto& i : c) {
        std::cout << i << ", ";
    }
    std::cout << "\n";
}

template <typename T, typename Container = std::vector<T>>
Container getSampleData(std::size_t count) {
    Container          c;
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(1, count * 10);

    for (std::size_t i = 0; i < count; ++i) {
        c.push_back(distrib(gen));
    }
    return c;
}

/**
 * Get local time as string.
 */
inline std::string getLocalTimeString(
    const std::chrono::system_clock::time_point& timePoint) {
    auto    time  = std::chrono::system_clock::to_time_t(timePoint);
    std::tm tmBuf = {};
    localtime_r(&time, &tmBuf);

    std::ostringstream oss;
    oss << std::put_time(&tmBuf, "%F %T") << "." << std::setfill('0')
        << std::setw(6)
        << std::chrono::duration_cast<std::chrono::microseconds>(
               timePoint.time_since_epoch())
                   .count() %
               1000000;

    return oss.str();
}

/**
 * Get current local time as string.
 */
inline std::string getCurrentTime() {
    return getLocalTimeString(std::chrono::system_clock::now());
}

}  // namespace Utils

#endif
