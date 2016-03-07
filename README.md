- 2016/3/8
	- Set的底层改成红黑树
	- 迭代二叉树的底层堆栈长度调整
- 2016/3/4
	- 完成Set的添加元素函数`set_add()`和搜索函数`set_search()`，由于集合中不存在重复元素，所以集合不提供反向搜索的功能
	- Set接口增加三个集合运算函数，实现交集、并集和集合减法的运算
- 2016/3/3
	- 修正了容器的种类，取消HashSet和LinkedHashSet，合并为Set，采用AVL树实现，取消HashMap和LinkedHashMap，合并为Map，增加Graph
	- 定义Stack和Set的界面
- 2016/3/2
	- 修正了ArrayList中的错误，完成LinkedList的开发和测试
	- 快速排序和插入排序的实现移到`al_arraylist.c`中实现并隐藏
	- 增加了函数指针类型`typedef void (*onRemove)(void *)`，用于容器清空时对被清除节点中元素的处理
	- 取消了ArrayList和LinkedList的`xx_clear()`函数，因为节点元素内存释放的问题，一次性清空所有节点很可能导致内存分配的问题，不安全，所以取消
	- 容器的`xx_clear()`函数改为`xx_remove(.., onremove onRemove)`，清除节点时用来进行元素处理，默认(参数为NULL)不做任何操作，最常见的可以传入标准库函数`free()`
	- LinkedList的节点位置类型`LLPos`改名为节点类型`LLNode`，以便更符合数据结构的习惯叫法
	- 增加容器的逆向搜索函数`xx_rsearch()`
- 2016/3/1
	- 在`mr_common`中增加一系列基础数据类型数据装箱函数`xx_inbox()`，没有固定地址的基础类型数据(临时变量、字面量等)在置入容器前使用对应的装箱函数进行装箱以获得一个固定的内存指针
	- 所有容器中的元素在`xx_remove()`或`xx_replace()`函数后会返回元素指针，如果指针是由客户端程序通过`malloc()`,`realloc()`,`calloc()`函数分配的或通过`xx_inbox()`函数装箱获得的，那么客户端程序必须自行释放这些指针
	- 容器库的`xx_clear()`,`xx_destroy()`函数不会释放容器中元素的内存空间，也不会返回任何元素指针，所以在调用这两个函数的时候要确保已经销毁所有元素的内存空间
	- 取消了LinkedList的所有基于索引的随机访问操作，在链表节点中增加所属链表的句柄的字段以便根据节点获取和验证所属链表，简化客户端函数界面
- 2016/2/29
	- 完成了LinkedList库的界面设计，提供根据索引值和根据位置(自定义类型LLPos)进行访问的两套访问函数
	- 完成了ArrayList库，实现线性表的CRUD和排序功能、可以用数字索引对列表进行快速地访问，支持快速排序和插入排序两种排序方式
	- 定义了容器的通用迭代器，实现了ArrayList的迭代器
	- Queue计划改为循环队列的实现，把CircularQueue改为PriorityQueue
- before 2016/2/28
	- 完成部分String库的开发，剩余字符串操作需要依赖容器操作，因此先暂停该部分，转为容器部分的开发
	- 完成了UTF-8编码字符串的解析函数，字符串基本操作函数已经完成
	- 库整体框架搭建
