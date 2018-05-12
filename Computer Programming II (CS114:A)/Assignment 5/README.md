# Assignment 5
很多人看不懂5-1和5-2到底差在哪，還有為什麼基哥只給了一份`Vector.h`，這裡稍微解釋一下

我們來看看這兩份的Main Function

```cpp
// Assignment 5-1.cpp
HugeInteger<int> n1[numTestCases];
HugeInteger<int> n2[numTestCases];
HugeInteger<unsigned int> n3[numTestCases];
HugeInteger<unsigned int> n4[numTestCases];
HugeInteger<short int> n5[numTestCases];
HugeInteger<short int> n6[numTestCases];
HugeInteger<unsigned short int> n7[numTestCases];
HugeInteger<unsigned short int> n8[numTestCases];

// Assignment 5-2.cpp
HugeInteger<vector<int>> n1[numTestCases];
HugeInteger<vector<int>> n2[numTestCases];
HugeInteger<vector<unsigned int>> n3[numTestCases];
HugeInteger<vector<unsigned int>> n4[numTestCases];
HugeInteger<vector<short int>> n5[numTestCases];
HugeInteger<vector<short int>> n6[numTestCases];
HugeInteger<vector<unsigned short int>> n7[numTestCases];
HugeInteger<vector<unsigned short int>> n8[numTestCases];
```
沒有頭緒嗎，那再看看HugeInteger的標頭檔

```cpp
// HugeInteger - 5-1.h
private:
  vector<T> integer;
  HugeInteger(unsigned int n);

// HugeInteger - 5-2.h
private:
  T integer;
  HugeInteger(unsigned int n);
```

你可以發現在5-1的Main Function裡，在宣告`HugeInteger`的時候，我們只提供了`int`作為typname，但是在5-2中，我們寫的是`vector<int>`，首先你要搞清楚的是，這裡的`HugeInteger`只是一個架構，在5-1中，這個`HugeInteger`直接在宣告的地方決定容器要用`vector`，而5-2則是把容器的種類留到宣告的時候再讓Main Function決定。

那你一定好奇了，這樣差在哪？那大概就是基哥下次如果出了一份新作業：請把`HugeInteger`的容器換掉，那很顯然拿5-2幾乎不用什麼改就可以用了