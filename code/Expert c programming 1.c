#include <bits/stdc++.h>

int main()
{
    // 前言部分
    time_t max_time_t = 0x7FFFFFFF; // time_t是long的typedef形式
    // time_t的尽头
    printf("max_time_t=%s \n", ctime(&max_time_t)); /*显示time_t中最大的时间,并将其传递给
     ctime函数，该函数只是转换时间，与c没有关系*/
    // 该方法显示的结果有误，只是把这个时间转化为当地时间，不是世界统一时间（UTC)

    /*下面是用gmtime函数来取得最大时间，但是该函数返回值不是一个可以打印的字符�?
    因此需要asctime函数来转化获取这个字符串*/
    printf("max time t=%s\n", asctime(gmtime(&max_time_t)));

    // 第一章
    /*关于相容性问题
    如果两个变量可以赋值（相容）
    那么左边的变量应该包含右边的变量的全部限定操作符，包括指向的类型的操作符
    */
    char a = 'a';
    char *pa = &a;
    char **ppa = &pa; // 一个指向char*类型的指针?
    const char b = 'b';
    const char *pb = &b;
    const char **ppb = &pb; // 一个指向const char *类型的指针?
    // pa = pb;//该语句报错，因为pa指向的类型是char（无限定符），而pb指向的是const char，左边不包括右边
    pb = pa;
    // 该两个语句会报错，因为虽然ppa与ppb类型都是指针（*），但是他们指向的类型不一样
    // ppb = ppa;
    // ppa = ppb;
    // ppa指向的是char *，ppb指向的是const char *，二者不能相容，因此不能相互赋值（不相容）
    // 类型相同不代表可以赋值，他们指向的内容的操作符不相容

    /*
    算术转换（隐式转换）
    在一些计算，比较情况时，编译器会进行算术转换
    short,char->int  float->double
    此外，在双目运算符中，如果有一个操作数为double（long double），
    例如 1.0/3中，1.0是double而3是int，那么3会被转化为double，其结果也是double类型。
    long int，unsigned int，另一个如果是比它低（也就是表示范围比它少，精度比它低）的类型，那么该类型就会被转换为对应的高类型
    总之，算术转换总是朝着浮点精度更高，长度更长的方向转换，如果转换为signed 不会有精度丢失，那么就转换为signed，否则转换为unsigned

    但是有一个bug是：不同的编译器对于-1转换的结果不一样
    在if（ （sizeof（a）-2） > -1)判断时，if在signed int与unsigned int（sizeof返回类型为unsigned int）之间测试大小，此时-1（signed int）会被升级为（unsigned int）
    在ANSI C中，-1转换为unsigned后会成为一个很大的整数4294967295
    而在K&RC中，如果也进行unsigned int -1，会得到相同的结果
    */
    printf("-1 in unsigned int is %u\n", (unsigned int)-1);
    // 解决方案 采用int强制类型转换 if( (int)sizeof(a)-2 > -1)
    /*
    启发：在代码中尽量不要使用unsigned类型，以避免不要必要的隐式转换带来的bug，尤其是不要因为年龄，国债等无负数数据就使用unsigned来表示
    而是使用int等有符号类型，这样在涉及到复杂的混合或者隐式转换等细节时，就可以不用考虑到边界值（例如-1的unsigned int是4294967295）
    在位段和二进制时才建议使用unsigned，而且所有的表达式应该都有显示类型转换（强制类型转换）来确保所有的类型都是unsigned或者signed
    */
    //技巧 #define NUMBER_ELEMTENTS  (sizeof(array)of/sizeof(array[0]))而不是(sizeof(array)/sizeof(int))前者无需改变宏即可实现数组类型的变化（int->char）
    //第一章大部分在讲C的历史和C的各种版本的标准，有用的就这些
    //第一章结束
    system("pause");
    return 0;
}