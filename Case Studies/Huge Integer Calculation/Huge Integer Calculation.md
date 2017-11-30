# Huge Integer Calculation
這應該是基哥眾多作業中最令人頭痛的一個，
因為這份作業內容本來就很乏味，
重點是後續很難debug，
所以我想在這裡留下我當時寫的時候遇到的一些狀況，
還有一些的改善方式

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

基本上就是一個簡單、直覺的寫法，
但是這樣數一數還是有6個for迴圈，
所以還是值得簡化一下。

####Step 3的4個迴圈
光這個步驟就有4個迴圈
而且根本只是為了處理`addendSize`可能和`adderSize`不一樣這種小問題而寫的，

### 減法
⚠️Under Construction⚠️

### 乘法
⚠️Under Construction⚠️

### 除法
⚠️Under Construction⚠️

## Minor Optimaization
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