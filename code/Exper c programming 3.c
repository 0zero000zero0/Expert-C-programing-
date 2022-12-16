#include <bits/stdc++.h>
/*关于结构 */
struct name // 名字可选（可有可无）  
{
    int data;
    // 各种数据
    // unsigned int inactive : 1;
    // unsigned int : 1;
    // unsigned int refcount : 6;
    // unsigned int : 0;
    // 结构体中可以存在位段，无名字段和填充字段，这些被称为”深入逻辑元件的编程“
    int a[10];
}; // 这个创建的结构体变量test1可选
// 为了可读性，最好把结构体（类型）声明和变量声明分开

// 结构体还能作为函数的参数和返回值
struct name test_function(struct name s) // 用结构体指针更快
{
    for (int i = 0; i < 10; i++)
        s.a[i] = 2;
    s.data = 1;
    return s;
}

// 联合体：用于存储一些不能同时出现的数据，可以节省空间。
union creature
{
    char has_backbone;
    char has_fur;
    short num_of_legs_in_excess_of_4;
}; // 由于动物脊椎的状态只有 yes和no两种，而只有脊椎动物才有皮毛,无脊椎动物才可能有四条以上的腿
// 此外，联合体还能把同一个数据解释为两个不同的东西。
union bits32_tag
{
    int whole; // 一个32字节的值
    struct Byte
    {
        /* data */
        char co, c1, c2, c3;
    } byte; // 4个8位的字节
};

/*
    关于typedef
    typedef:typedef只是为一个变量取其他的名字，例如typedef struct Students{int id;int score;}stu;这样struct Students就可以被stu代替
    typedef并没有新建变量，只是改个名字而已，因此可以对任何类型进行typedef声明。
*/
// 但是1：不要把typedef放在几个声明中，例如
typedef int *ptr, (*fun)(), arr[5]; // ptr是一个int*，fun是返回值为int的函数的指针，arr是长度为5的int型数组
// 但是2：不要把typedef嵌入到声明的中间部分
// unsigned const long typedef int volatitle *kumquat;//直接报错
// 宏与typedef区别
// 1宏只是简单的文本替换，而typedef是一种彻底的类型封装，在他声明后不能增加其他标识符 （例如const）
#define peach int
unsigned peach i; // 没问题
typedef int banana;
// unsigned banana i;//报错
// 2在连续声明变量中typedf能保证变量类型一致而宏不一定
#define int_ptr int *
int_ptr chalk, cheese; // 经过替换后int * chalk,cheese chalk是整型指针但是cheese是整型
typedef char *char_ptr;
char_ptr Bentley, Rolls_Royce; // 两个都是char*

// 名字空间：名字空间有很多，例如标签名，成员名等。在同一名字空间中任何名字必须唯一，但是在不同的名字空间下名字可以一样
// 由于每一个结构，联合或者枚举都有自己的名字空间，那么就会出现下面这个
typedef struct baz
{
    int baz;
} baz;
struct baz variable_1;//使用结构 *标签* baz
baz varoiable_2;//使用结构 *类型* baz
//太多的baz，一般换成更加清楚的声明
typedef struct my_tag{
    int i;
} my_type;
/*
启示：不要为了方便而对结构体使用typedef，虽然这样可以不用写struct，但是struct可以提示一些信息。
typedef应该用在以下几个方面：
1：数字，结构，指针以及函数的组合类型
2：可移植类型：在移植程序时只需要加上typedef就可以把short，int，等转换成其他平台的类型
3：typedef可以为强制类型转换提供一个简单的名字，例如typedef int (*ptr_to_int_fun)(void)
char *p;
···=(*ptr_to_int_fun)p;//把p转换为指向int为返回类型的指针
//这第三个我也不知道有什么用。这种启示确实很奇怪
当可能混淆结构标签与类型时，用_tag来表示标签会使得程序可读性更高
*/
int main()
{
    // 第三章 分析C语言声明
    /*前言：由于C语言的声明中存在很多优先级的问题，程序员需要记住很多优先级才能搞懂大部分的声明
    例如int *p[2]就要知道[]优先级高于*，因此它是一个元素为指向int的指针的数组。
    有意思的是到现在一个比较好的声明方法是int&p，表示p是一个整型数据的地址，该语法已被c++采用，但是C语言没有配备
    C语言声明的最大问题是无法用人们习惯的从左到右的自然方式来解读一个声明，尤其是有const之后
    例如const int *p和int *const p。前者是一个常量指针（指针所指向的对象是只读的），也就是它的指向可以改变，但是不能通过解引用来改变他所指向的地址上的值
    后者是一个指针常量（指针是只读的），可以通过解引用来改变它所指向的地址上的值，但是不能改变它的指向（数组名就是一个指针常量）
    */

    /*类型说明符：void ,char ,int ,shor,long,float,double,unsigned
    存储类型：struct,enum,union
    类型限定：extern,static,register,auto,typedef,const,volatitle
    */
    // volatitle：易变的，可以说是直接存取原始内存地址。该关键字可以告诉编译器不需要优化该变量，直接从变量内存地址上读取数据，从而提供对特殊地址的稳定访问

    // 不合法的声明：函数返回值不能是一个函数和数组。数组的元素不能是函数
    /*
     合法的声明:1:函数返回值可以是函数指针.int( *fun(void) ) ()
    2:函数返回值可以是一个指向数组的指针。 int(*function(void))[2]
    3:数组的元素可以是函数指针或者是数组：int (*f[])(),int matrix[][]
    */

    struct name test1, test2;
    test1 = test_function(test1);
    test2 = test1; // 可以直接对结构体赋值
    printf("test1.a[0]=%d,test1.data=%d\n", test1.a[0], test1.data);
    printf("test2.a[0]=%d,test2.data=%d\n", test2.a[0], test2.data);
    // 联合体：用于存储一些不能同时出现的数据，可以节省空间。
    union creature
    {
        char has_backbone;
        char has_fur;
        short num_of_legs_in_excess_of_4;
    }; // 由于动物脊椎的状态只有 yes和no两种，而只有脊椎动物才有皮毛,无脊椎动物才可能有四条以上的腿
    // 此外，联合体还能把同一个数据解释为两个不同的东西。
    union bits32_tag
    {
        int whole; // 一个32字节的值
        struct Byte
        {
            /* data */
            char co, c1, c2, c3;
        } byte; // 4个8位的字节
    };

    // 理解C语言声明
    /*
    优先级规则：
    A:声明从名字开始读取，然后按照优先级顺序依次读取
    B:优先级从高到低依次是：B1:被括号括起来的部分->B2:后缀操作符(例如函数的( )，数组的[])，B3:前缀操作符指针的*
    C:如果const，volatitle关键字的后面紧跟类型说明符，那么它就作用于类型说明符。其他情况下作用于左边紧邻的指针*
    */

    /*
    例如const char *(*next)(int a);
    首先找到名字next，然后根据B1，next是一个指针，出括号后根据B2得出next是一个函数指针,函数参数为int，在根据B3得出这个函数的返回类型也是一个指针，之后根据C得出函数返回的指针指向一个cosnt char
    综上得出，next是一个指向返回类型为指向常量字符的指针的,参数为int的函数的指针。或者说next是一个函数指针，函数的参数为int，返回类型是一个指向常量字符的指针。
    */
//end
    system("pause");
    return 0;
}