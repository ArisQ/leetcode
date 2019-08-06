#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> canonicalPath;
        path += '/';
        size_t start = 0;
        size_t end;
        string subStr;
        while ((end = path.find('/', start)) != string::npos) {
            if (start != end) {
                subStr = path.substr(start, end - start);
                if (subStr == "..") {
                    if (!canonicalPath.empty())
                        canonicalPath.pop_back();
                } else if (subStr != ".")
                    canonicalPath.push_back(subStr);
            }
            start = end + 1;
        }
        if (canonicalPath.empty())
            return "/";
        string result;
        result.reserve(path.size());
        for (auto &dir:canonicalPath) {
            result += '/';
            result += dir;
        }
        return result;
    }
};

TEST_CASE("Simplify Path") {
    REQUIRE(Solution().simplifyPath("/home/") == "/home");
    REQUIRE(Solution().simplifyPath("/../") == "/");
    REQUIRE(Solution().simplifyPath("/home//foo/") == "/home/foo");
    REQUIRE(Solution().simplifyPath("/a/./b/../../c/") == "/c");
    REQUIRE(Solution().simplifyPath("/a/../../b/../c//.//") == "/c");
    REQUIRE(Solution().simplifyPath("/a//b////c/d//././/..") == "/a/b/c");
}
