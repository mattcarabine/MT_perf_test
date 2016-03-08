#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

extern "C" double gethrtime(void)
{
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
}

void to_xml(double result) {
    std::string test_name = "no_op.xml";
    std::ofstream file(test_name);
    file << "<testsuites timestamp=\"2016-02-29T15:44:08\">\n";
    file << "  <testsuite name=\"no_op\">\n";
    file << "    <testcase name=\"no_op" << "\" time=\"" << result/1e3 << "\" classname=\"no_op\"/>\n";
    file << "  </testsuite>\n";
    file << "</testsuites>\n";
}

int main() {
    std::mt19937 generator (123);
    std::vector<double> timings;
    for (int i = 0; i < 1000000; i++) {
        double start = gethrtime();
        std::vector<double> numbers;
        for (int j = 0; j < 100; j++) {
            numbers.push_back(generator());
        }
        double end = gethrtime();
        timings.push_back(end - start);
    }
    sort(timings.begin(), timings.end());
    auto vector_size = timings.size();
    double median = 0;
    if (vector_size % 2 == 0) {
        median = timings[vector_size / 2];
    } else {
        median = timings[(vector_size - 1) / 2];
    }
    to_xml(median);

    return 0;
}



