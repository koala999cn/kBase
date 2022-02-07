#include <iostream>
#include "KuPathUtil.h"


static void test_splitRoot()
{
    std::string filenames[] = {
        "C:\\Documents\\Newsletters\\Summer2018.pdf",
        "\\Program Files\\Custom Utilities\\StringFinder.exe",
        "2018\\January.xlsx",
        "..\\Publications\\TravelBrochure.pdf",
        "C:Projects\\apilibrary\\apilibrary.sln",
        "\\\\127.0.0.1\\c$\\temp\\test-file.txt",
        "\\\\LOCALHOST\\c$\\temp\\test-file.txt",
        "\\\\.\\c:\\temp\\test-file.txt",
        "\\\\?\\c:\\temp\\test-file.txt",
        "\\\\.\\UNC\\LOCALHOST\\c$\\temp\\test-file.txt"
    };

    std::string  roots[] = {
        "C:\\",
        "\\",
        "",
        "",
        "C:",
        "\\\\127.0.0.1\\c$\\",
        "\\\\LOCALHOST\\c$\\",
        "\\\\.\\c:\\",
        "\\\\?\\c:\\",
        "\\\\.\\UNC\\LOCALHOST\\c$\\"
    };

    for (auto i = 1u; i < sizeof(filenames) / sizeof(std::string); i++)
        if (KuPathUtil::splitRoot(filenames[i]) != roots[i]) {
            std::cout << " failed(" << filenames[i] << "), " << "expect '" << roots[i] 
                << "', but get'" << KuPathUtil::splitRoot(filenames[i]) << "'\n";
            exit(1);
        }
}


static void test_rooted()
{
    std::string filenames[] = {
        "C:\\Documents\\Newsletters\\Summer2018.pdf",
        "\\Program Files\\Custom Utilities\\StringFinder.exe",
        "2018\\January.xlsx",
        "..\\Publications\\TravelBrochure.pdf",
        "C:\\Projects\\apilibrary\\apilibrary.sln",
        "C:Projects\\apilibrary\\apilibrary.sln"
    };

    bool rooted[] = {
        true,
        true,
        false,
        false,
        true,
        true
    };

    for (auto i = 1u; i < sizeof(filenames) / sizeof(std::string); i++)
        if (KuPathUtil::isRooted(filenames[i]) != rooted[i]) {
            std::cout << " failed(" << filenames[i] << ")\n";
            exit(1);
        }
}


static void test_abspath()
{
    std::string filenames[] = {
        "C:\\Documents\\Newsletters\\Summer2018.pdf",
        "\\Program Files\\Custom Utilities\\StringFinder.exe",
        "2018\\January.xlsx",
        "..\\Publications\\TravelBrochure.pdf",
        "C:\\Projects\\apilibrary\\apilibrary.sln",
        "C:Projects\\apilibrary\\apilibrary.sln" 
    };

    bool absPath[] = {
        true,
        false,
        false,
        false,
        true,
        false
    };

    for (auto i = 1u; i < sizeof(filenames) / sizeof(std::string); i++)
        if (KuPathUtil::isAbsPath(filenames[i]) != absPath[i]) {
            std::cout << " failed(" << filenames[i] << ")\n";
            exit(1);
        }
}


static void test_rootsame()
{
    std::string filenames[] = {
        "c:\\temp\\test-file.txt",
        "\\\\127.0.0.1\\c$\\temp\\test-file.txt",
        "\\\\LOCALHOST\\c$\\temp\\test-file.txt",
        "\\\\.\\c:\\temp\\test-file.txt",
        "\\\\?\\c:\\temp\\test-file.txt",
        "\\\\.\\UNC\\LOCALHOST\\c$\\temp\\test-file.txt"
    };

    for (auto i = 1u; i < sizeof(filenames) / sizeof(std::string); i++)
        if (!KuPathUtil::isSameRoot(
                KuPathUtil::splitRoot(filenames[0]),
                KuPathUtil::splitRoot(filenames[i]) )) {
            std::cout << " failed(" << filenames[0] << " vs. " << filenames[i] << ")\n";
            exit(1);
        }
}


void pathutil_test()
{
    std::cout << "test KuPathUtil...\n";

    std::cout << "  splitRoot...";
    test_splitRoot();
    std::cout << " passed\n";

    std::cout << "  isRooted...";
    test_rooted();
    std::cout << " passed\n";

    std::cout << "  isAbsPath...";
    test_abspath();
    std::cout << " passed\n";

    std::cout << "  isSameRoot...";
    test_rootsame();
    std::cout << " passed\n";
}