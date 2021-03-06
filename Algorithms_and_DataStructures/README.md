# [C/C++] Alogrithms_and_DataStructures
算法与数据结构的一些实验代码, 来源包括但不限于《算法导论》、hankerrank、leecode, etc.   


## Read & Run
仅在linux下进行了实验, 都是通用代码, 理论上平台无关. 顺便熟练下`vim`的使用.    
- `Linux`: `CentOS7 64bit`   
			- `Kernel 3.10.0-229.el7.x86_64`   
			- `gcc 4.8.5 20150623`   
			- `VIM - Vi IMproved 7.4 (2013 Aug 10, compiled Jun 10 2014 06:55:55)`    

	- 编译与运行   
		```
		g++ -std=c++11 xxx.cc    
		(OR gcc xxx.c)    
		./a.out   
		```   

## 实验说明   
  
### [C] matching_machine_hankerrank.c   

### [C++] sparse_arrays_hankerrank.cc   

### [C++] dynamic_array_hankerrank.cc   

### [C++] tree_preorder_traversal_hankerrank.cc   
hankerrank上的"Tree: Preorder Traversal" challenge. 本程序在此处仅编译, 无运行相关代码. 因为需要构造树, 故仅在Hankerrank上进行运行测试.   

- `preOrder`   
普通的非递归实现, 不允许用STL的`set`, 逻辑有点复杂.   

- `preOrder2`   
递归实现, 简洁明了.    


### [C++] myAtoi_leecode.cc 
leecode上的 String to Integer (atoi).   

### [C++] reversewords_leecode.cc 
leecode上的 Reverse Words in a String.   

### [C++] divide_two_integers.cc   
leecode上的 Divide Two Integers, 要求不用已带的除、乘、模操作来实现十进制的除法. 

- 我的实现方法1:   
	本是直接用十进制循环减法来做, 但数字较大时计算很慢, 超出了leecode的Time Limit;   
- 我的实现方法2:   
	改进方法是转为二进制后, 用二进制减法来替代. 二进制的移位操作大大减少了原十进制的循环次, 从而提高了效率;   

## Reference Links
- https://www.hackerrank.com/   
- https://leetcode.com/   


### Contacts
Author's Email: wangyoucao577@gmail.com.
