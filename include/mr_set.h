/**
 * "mr_set.h"，集合数据结构
 *
 * mr_set库提供一种基于红黑树构造的线性堆栈，用于实现有序集合。
 * 向集合中添加新元素时根据cmpfunc比较的结果构造二叉查找树，默认的cmpfunc在比较自定义对象时使用对象的地址进行比较，因此如果自定义对象使用默认比较函数时将无法保证迭代时的顺序
 * Set不提供按索引位置随机访问的功能，而是提供基于cmpfunc的有序迭代访问，因此Set不提供排序的功能
 * Set不支持重复的元素，元素是否重复根据cmpfunc确定，默认情况下数值和字符串根据内容判断，自定义对象根据地址判断，插入重复元素将不予保存；Set不接受NULL元素
 * 注意：集合运算的结果集中所有元素都是直接从原集合中引用的，所以销毁原集合中的元素会同时销毁结果集中的元素，反之亦然
 *
 * Version 1.0.0, 李斌，2016/03/08
 */
#ifndef MR_SET_H
#define MR_SET_H

#include "mr_common.h"

/**
 * 集合迭代器类型
 */
typedef void *SetIterator;

/**
 * 创建一个Set，返回句柄
 * type:	元素的类型
 * cmpfunc:	元素比较函数，传入NULL表示采用mr_common.h中定义的与type对应的默认比较函数
 *
 * 返回:	新创建的Set的句柄(一个大于等于0的正整数)，创建失败返回-1
 */
extern Set set_create(ElementType type, CmpFunc cmpfunc);

/**
 * 销毁一个Set，释放列表的空间，但不会销毁其中的元素
 * s:		Set句柄
 *
 * 返回:	销毁完成返回0，销毁失败或无效Set句柄返回-1
 */
extern int set_destroy(Set s);

/**
 * 判断一个Set是否为空
 * s:		Set句柄
 *
 * 返回:	为空返回1，不为空返回0，无效句柄返回-1
 */
extern int set_isempty(Set s);

/**
 * 获取一个Set中的元素数量
 * s:		Set句柄
 *
 * 返回:	元素数量，空集合或无效句柄返回0
 */
extern size_t set_size(Set s);

/**
 * 在集合中搜索一个元素
 * s:		Set句柄
 * ele:		要搜索的元素
 *
 * 返回:	搜索到集合中存在与ele相同的元素时返回集合中的元素，搜索不到或搜索出错返回NULL
 */
extern Element set_search(Set s, Element ele);

/**
 * 添加一个元素，重复元素将不予添加
 * s:		Set句柄
 * ele:		待添加的元素
 *
 * 返回:	添加成功返回0，添加失败或元素重复返回-1
 */
extern int set_add(Set s, Element ele);

/**
 * 删除一个元素，根据参数ele查找集合中与之相同的元素，删除该节点，返回集合中的元素
 * s:		Set句柄
 * ele:		待删除的元素
 *
 * 返回:	删除成功返回集合中的元素，删除失败或未找到返回NULL
 */
extern Element set_remove(Set s, Element ele);

/**
 * 删除Set中所有的元素，被清除的元素用onremove函数进行后续处理
 * s:		Set句柄
 * onremove:	元素后续处理函数，NULL表示不做任何处理，典型的可以传入标准库函数free
 *
 */
extern void set_removeall(Set s, onRemove onremove);

/**
 * 获取一个集合的递增顺序迭代器
 * s:		Set句柄
 * 
 * 返回:	集合迭代器，Set为空返回NULL
 */
extern SetIterator set_iterator(Set s);

/**
 * 获取一个集合的递减反序迭代器
 * s:		Set句柄
 * 
 * 返回:	集合迭代器，Set为空返回NULL
 */
extern SetIterator set_riterator(Set s);

/**
 * 迭代访问一个迭代器中的下一个元素
 * it:		集合迭代器的指针
 *
 * 返回:	迭代中的下一个元素，迭代器无效或已经迭代完成时返回NULL并销毁迭代器，设置迭代器指针为NULL
 */
extern Element set_next(SetIterator *it);

/**
 * 求两个集合的交集，如果两个集合的元素数据类型不一致则返回空集合
 * 如果两个集合的元素比较函数不同则使用s1的cmpfunc进行元素比较，并且结果集合也采用s1的cmpfunc为其元素比较函数
 * 注意：集合运算的结果集中所有元素都是直接从原集合中引用的，所以销毁原集合中的元素会同时销毁结果集中的元素，反之亦然
 * s1,s2:	两个集合的句柄
 *
 * 返回:	s1和s2的交集的句柄，是一个新建的集合，如果s1和s2中有至少一个无效，则返回-1
 */
extern Set set_intersection(Set s1, Set s2);

/**
 * 求两个集合的并集，如果两个集合的元素数据类型不一致则返回空集合
 * 如果两个集合的元素比较函数不同则使用s1的cmpfunc进行元素比较，并且结果集合也采用s1的cmpfunc为其元素比较函数
 * 注意：集合运算的结果集中所有元素都是直接从原集合中引用的，所以销毁原集合中的元素会同时销毁结果集中的元素，反之亦然
 * s1,s2:	两个集合的句柄
 *
 * 返回:	s1和s2的并集的句柄，是一个新建的集合，如果s1和s2中有至少一个无效，则返回-1
 */
extern Set set_union(Set s1, Set s2);

/**
 * 求两个集合的减集，即s1-s2，从s1中删除所有存在于s2中的元素，如果两个集合的元素数据类型不一致则结果集与s1的元素相同
 * 如果两个集合的元素比较函数不同则使用s1的cmpfunc进行元素比较，并且结果集合也采用s1的cmpfunc为其元素比较函数
 * 注意：集合运算的结果集中所有元素都是直接从原集合中引用的，所以销毁原集合中的元素会同时销毁结果集中的元素，反之亦然
 * s1,s2:	两个集合的句柄
 *
 * 返回:	集合s1-s2的句柄，是一个新建的集合，如果s1和s2中有至少一个无效，则返回-1
 */
extern Set set_minus(Set s1, Set s2);

#endif
