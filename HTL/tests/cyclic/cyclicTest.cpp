
#include <iostream>
#include "cyclic.h"


using namespace std;

const int BUFFER_SIZE = 6;

static int failCount = 0;

cyclic<string> ringStr(BUFFER_SIZE);
cyclic<int> ringInt{ 42, 1881, 1453, 1977, 622, 314 };

const string initStr[BUFFER_SIZE]{ "", "", "", "", "", "" };
const int initInt[BUFFER_SIZE]{ 42, 1881, 1453, 1977, 622, 314 };
const int push_1938[BUFFER_SIZE]{ 1938, 1881, 1453, 1977, 622, 314 };

const string abcdef[BUFFER_SIZE]{ "a", "b", "c", "d", "e", "f" };
const string ghcdef[BUFFER_SIZE]{ "g", "h", "c", "d", "e", "f" };
const string mnojkl[BUFFER_SIZE]{ "m", "n", "o", "j", "k", "l" };

template<class T>
string checkBufferContent(cyclic<T>& buffer, const T* expected) {
    string result = "Pass";
    int i = 0;
    for (auto item : buffer) {
        if (item != expected[i]) {
            result = "Fail";
            break;
        }
        ++i;
    }
    return result;
}

void runTestPrintResult(string testName, string Result) {
    cout.fill('.');
    cout.setf(ios::left);
    cout.width(55);
    cout << testName << flush;
    cout << Result << endl;
    failCount = (Result == "Pass") ? failCount : failCount++;
}

void runTestPrintResult(string testName, bool Result) {
    cout.fill('.');
    cout.setf(ios::left);
    cout.width(55);
    cout << testName << flush;
    cout << (Result ? "Pass" : "Fail") << endl;
    failCount = Result ? failCount : failCount++;
}



int main()
{
    //check initial conditions
    runTestPrintResult("Constructor and initial content test", checkBufferContent(ringStr, initStr));
    runTestPrintResult("Initializer list test", checkBufferContent(ringInt, initInt));
    runTestPrintResult("Size measurement empty buffer test", ringStr.size() == 0);
    runTestPrintResult("Size measurement full buffer test", ringInt.size() == 6);
    runTestPrintResult("check data loss reporting at init", ringInt.datalost() == false);
    runTestPrintResult("check data loss count reporting at init", ringInt.lostDataCount() == 0);

    // push on empty buffer
    ringStr.push("a");
    runTestPrintResult("Size measurement for one item in buffer", ringStr.size() == 1);
    ringStr.push("b");
    ringStr.push("c");
    ringStr.push("d");
    ringStr.push("e");
    ringStr.push("f");
    runTestPrintResult("Size measurement for one item in buffer", ringStr.size() == 6);
    runTestPrintResult("Successive pull operations test", checkBufferContent(ringStr, abcdef));

    //iterator Test
    int i = 0;
    for (cyclic<string>::iterator it = ringStr.begin(); it != ringStr.end(); it++) {
        runTestPrintResult("Iterator end() method and postfix ++ operator test", *it == abcdef[i]);
        ++i;
    }

    cyclic<string>::iterator it = ringStr.begin();
    runTestPrintResult("iterator begin method", *it == abcdef[0]);
    ++it;
    runTestPrintResult("iterator prefix ++ overload", *it == abcdef[1]);


    // push on full buffer
    ringStr.push("g");
    runTestPrintResult("check data loss reporting after first loss", ringStr.datalost());
    runTestPrintResult("check data loss counter after first loss", ringStr.lostDataCount() == 1);
    runTestPrintResult("Size measurement for overwritten buffer", ringStr.size() == 6);

    ringStr.push("h");
    runTestPrintResult("check data loss counter increment", ringStr.lostDataCount() == 2);
    runTestPrintResult("check buffer after push full buffer", checkBufferContent(ringStr, ghcdef));

    ringStr.push("i");
    ringStr.push("j");
    ringStr.push("k");
    ringStr.push("l");
    ringStr.push("m");
    runTestPrintResult("check data loss counter increment", ringStr.lostDataCount() == 7);
    ringStr.clearlostDataCounter();
    runTestPrintResult("check data loss counter increment", ringStr.lostDataCount() == 0);

    //pull operations
    runTestPrintResult("check pull after double owerwrite", ringStr.pull() == "h");
    runTestPrintResult("Size decrement after pull", ringStr.size() == 5);
    runTestPrintResult("check pull after double owerwrite", ringStr.pull() == "i");
    runTestPrintResult("Size decrement after pull", ringStr.size() == 4);
    runTestPrintResult("check pull", ringStr.pull() == "j");
    runTestPrintResult("check pull", ringStr.pull() == "k");
    ringStr.push("n");  //should overwite "l"
    ringStr.push("o");  //should overwite "m"

    runTestPrintResult("Check buffer after push pull test", checkBufferContent(ringStr, mnojkl));

    runTestPrintResult("check pull", ringStr.pull() == "l");
    runTestPrintResult("check pull", ringStr.pull() == "m");
    runTestPrintResult("check pull", ringStr.pull() == "n");
    runTestPrintResult("check pull", ringStr.pull() == "o");
    runTestPrintResult("Size reach 0 after pull", ringStr.size() == 0);
    cout << failCount << " Failed tests" << endl;


}