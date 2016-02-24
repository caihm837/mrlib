/**
 * "mr_common.h"，通用工具函数、常量及宏函数
 *
 * Version 1.0.2, 李斌，2016/02/22
 */
#ifndef MR_COMMON_H
#define MR_COMMON_H

/**
 * 字符串结尾符
 */
#define EOS '\0'

/**
 * 返回任意类型数组的长度
 */
#define ARRAY_LEN(arr) (sizeof(arr)/sizeof(arr[0]))

/**
 * 判断字符是否为引用符号，包括单引号、双引号、反引号、大中小括号、尖括号
 */
#define IS_QUOTES(ch) ((ch)=='"'||(ch)=='\''||(ch)=='`'||(ch)=='('||(ch)==')'||(ch)=='['||(ch)==']'||(ch)=='{'||(ch)=='}'||(ch)=='<'||(ch)=='>')

/**
 * 判断字符是否为句子分隔符，包括英文分号、句号、问号、感叹号和回车换行
 */
#define IS_STBRKS(ch) ((ch)=='.'||(ch)==';'||(ch)=='\n'||(ch)=='?'||(ch)=='!')

/**
 * 判断一个变量是否在两个边界数字之内（不含边界）的宏函数
 */
#define BTW(x, min, max) (((x) > (min)) && ((x) < (max)))

/**
 * 判断一个变量是否在两个边界数字之外（不含边界）的宏函数
 */
#define OUT(x, min, max) (((x) < (min)) || ((x) > (max)))

/**
 * 判断一个变量是否包含在两个边界数字之间（含边界）的宏函数
 */
#define IN(x, min, max) (((x) >= (min)) && ((x) <= (max)))

/**
 * 判断一个变量是否处于两个边界数字之外（含边界）的宏函数
 */
#define EX(x, min, max) (((x) <= (min)) || ((x) >= (max)))

/**
 * 是否需要提供线程安全，默认为1(True)
 * 提供线程安全将不可避免地降低一些性能，如果客户程序确认只运行于单线程条件下则可以通过设置__MultiThreads__为0(False)来关闭线程安全能力
 */
extern int __MultiThreads__;

/**
 * 自定义数据比较函数，NULL指针被认为比任何非NULL数据项小
 * d1:		第一个待比较的数据的指针
 * d2:		第二个待比较的数据的指针
 *
 * 返回:	如果d1==d2，返回0；如果d1 > d2，返回一个正整数；如果d1 < d2，返回一个负整数
 */
typedef int (*Comparator)(void *d1, void *d2);

/**
 * 容器类型定义，所有容器都采用一个整数(0或者正整数)作为句柄
 */
typedef int ArrayList;
typedef int LinkedList;
typedef int HashSet;
typedef int LinkedHashSet;
typedef int Stack;
typedef int Queue;
typedef int CircularQueue;
typedef int HashMap;
typedef int LinkedHashMap;
typedef int BTree;
typedef int Tree;

#endif
