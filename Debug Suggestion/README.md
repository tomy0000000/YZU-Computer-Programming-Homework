# Debug Suggestion
這裡專門收集幾個常見Bug以及解決辦法，歡迎於Issue中建議新內容

* 如果是使用 Visual Studio 在寫`Template`相關的程式時，可以先嘗試修改專案的設定：   
專案(P) ->  Project 屬性(P) -> C/C++ -> 語言 -> 一致性模式：否
![](https://raw.githubusercontent.com/tomy0000000/YZU-Computer-Programming-Homework/master/Debug%20Suggestion/bin/VS%20Project.png)
Visual Studio 的 Compiler 對某些程式碼有容忍的空間，就是就算你寫的不是符合標準的寫法 (a.k.a. 基哥的寫法)，它是會算過的，但是當你把這個選項打開時，他就會依照C++的標準去檢查你的程式碼，這個時候你的某些寫法可能就會出現問題，更多詳細的細節可以參考[這裡](https://docs.microsoft.com/zh-tw/cpp/build/reference/permissive-standards-conformance)