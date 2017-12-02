# Huge Integer Calculation
這應該是基哥眾多作業中最令人頭痛的一個，因為這份作業內容本來就很乏味，重點是後續很難debug，所以我想在這裡留下我當時寫的時候遇到的一些狀況，還有一些的改善方式。

## Core Function
### 加法
大致上的流程是這樣：

1. 定義`sumSize`
2. 清空`sum` (填0)
3. 用兩個for迴圈計算`sum` (一個是處理addend、adder都有值，另一個處理只有其中一個有值的)
4. 處理進位
5. 檢查步驟一的`size`是否正確

然後我們來看看基哥給的Code (註解是我自己加的)：

```
//Step 1
sumSize = ( addendSize >= adderSize ) ? addendSize + 1 : adderSize + 1;

//Step 2
for( int i = 0; i < sumSize; i++ ) //Loop #1
   sum[ i ] = 0;

//Step 3
if( addendSize <= adderSize )
{
   for( int i = 0; i < addendSize; i++ ) //Loop #2
      sum[ i ] = addend[ i ] + adder[ i ];
   for( int i = addendSize; i < adderSize; i++ ) //Loop #3
      sum[ i ] = adder[ i ];
}
else
{
   for( int i = 0; i < adderSize; i++ ) //Loop #4
      sum[ i ] = addend[ i ] + adder[ i ];
   for( int i = adderSize; i < addendSize; i++ ) //Loop #5
      sum[ i ] = addend[ i ];
}

//Step 4
for( int i = 0; i < sumSize - 1; i++ ) //Loop #6
   if( sum[ i ] > 9 )
   {
      sum[ i ] -= 10;
      sum[ i + 1 ]++;
   }

//Step 5
if( sum[ sumSize - 1 ] == 0 )
   sumSize--;
```

基本上就是一個簡單、直覺的寫法，但是這樣數一數還是有6個for迴圈，所以還是值得簡化一下。

#### Step 3的4個迴圈
光這個步驟就有4個迴圈，而且根本只是為了處理`addendSize`可能和`adderSize`不一樣這種小問題而寫的，所以我的做法是另外命兩個變數 (`faddend`和`fadder`)根據不同的情況決定計算的數字，這樣就可以有效的把4個迴圈合併成1個。

#### 進位的迴圈
當Step 3算出某一位的值的時候，我並沒有馬上把這個值存進Array裡，而是先把它存進`Cal`這個暫時的空間裡，然後mod 10之後再存進去，同時整除10的部分就存進下一位，但這也代表我在下一位做計算的時候必須考慮到前一位進位過來的值，所以要記得`Cal`同時還要把原本位在`sum[i]`的值一併加進去做計算。

#### 位數檢查
最後是位數檢查的部分，這個步驟也被我整合進for迴圈裡，但是因為我有在條件賦值的地方加上條件，所以其實只有在迴圈的最後一次執行的時候`sumSize`才有可能會被觸發。

### 減法
⚠️Under Construction⚠️

### 乘法
⚠️Under Construction⚠️

### 除法
流程：

1. 檢查特例情形
    1. 如果`dividend`是0，直接結束
    2. 複製`dividend`到`remainder`
    3. 如果`dividend`小於`divisor`，直接結束  
2. 初始化
    1. 定義`n`：`divisor`在做第一次的除法時需位移的位數
    2. 根據`n`製作`buffer`
    3. 定義`quotientSize`
    4. 如果`dividend`小於`buffer`，`buffer`向右移一位，如果沒有，`quotientSize`加一
    5. 清空`quotient`
3. 開始做除法 (反向遍歷`quotient`)
    1. 只要`buffer`不大於`remainder`，就一位一位加上去
    2. 如果`remainder`剛好等於0，直接結束
    3. `buffer`向右移一位

原本的code太長了我就不貼了，下面直接講我簡化了哪些部分。

#### 特例情形的處理
要處理的特例情形大概有兩種：

1. 不合法的操作：這個情況只有一種，也就是除以0，但是這個問題在`Perform` call `Dividend`之前就先排除掉了，所以我們不需要特別處理。

2. 合法，但是可以用比較快的方式先處理掉：這種情況就比較多了，雖然好處理，可以用if篩出來跳掉，但是反正我們的大數也不是真的有多大，testCases也沒有很多，所以兩害相權取其輕，我選擇把這些部分都拿掉，讓code用一般的做法去處理這些看似是特例，但又不是真的那麼特別的狀況。

	比方說：
	
	1. (Step 1-1)被除數等於0 (`dividend == 0`)
	2. (Step 1-3)被除數小於除數 (`dividend <= divisor`)
	3. (Step 3-2)餘數剛好等於0 (`remainder == 0`)
	
	通通砍掉

#### 除法裡面的Substraction
我們原本就有寫好一個現成的大數減法，但是這個減法是不能用的，因為按照基哥在Assignment 4簡報裡的做法，Function的使用方法只能是：

```
hugeIntArray1 = hugeIntArray2 - hugeIntArray3
//相當於a = b - c
```
但是今天我們在除法裡的用法是：

```
hugeIntArray1 = hugeIntArray1 - hugeIntArray2
//相當於a -= b
```
直觀的解決辦法就是先開一個暫時的Array，把原本的remainder暫時複製過去，再執行減法。但是如果你不想要搞的這麼麻煩，就要修改`Substraction`的code，修改的時候要掌握一個重點：
> 當`minuend`的某一位還會再被讀取時，相對應位數的`difference`就不可以被存入

這邊我就點到為止，剩下的請參閱[減法](#減法)的部分

## Minor Optimaization Skills
### Array Filling
```
for(int i=0; i<sumSize; i++) {
	sum[i] = 0;
}
```
簡化：

```
std::fill_n(sum, sumSize, 0);
```

### If Assignment
```
if (addendSize >= adderSize) {
    SumSize = addendSize+1
}
else {
    SumSize = adderSize+1
}
```
簡化：

```
sumSize = (addendSize >= adderSize) ? addendSize+1 : adderSize+1;
```
這樣寫的好處是code會看起來比較少，
在視覺上不那麼佔空間。
缺點是如果這裡有bug會比較難de出來，
所以如果你對這個用法比較不熟悉，
我會建議先寫原本的If Statement，
等確定這個部分沒有問題，
要de其他地方的時候再把這邊簡化。