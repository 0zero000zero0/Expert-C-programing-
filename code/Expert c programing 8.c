#include <bits/stdc++.h>

int main()
{
    printf("%d\n", sizeof 'A'); // 由于隐式类型转换普遍存在，有的编译器会把char转化为int，此处打印结果就是4，但是在我的环境（GCC8.1）上并不会转化
    // 这种特性被叫做类型提升
    char c1 = 'a', c2 = 'b';
    char c3 = c1 + c2;
    //类型提升要求机器把两个char转化为int，相加后再剪切转化为char
    //除了char ，short，unsigned char，enum，如果int可以完整地容纳原来的数据，都会被转换为int，否则就转化为unsigned int。float会被转化为double
    //而数组会被转为对应类型的指针。
    //函数的参数也会被提升，这就是为什么printf里%d可以用于int，short，char，因为他们都被转换为int
    printf("c1=%d,c2=%d,c3=%d\n", c1, c2, c3);
/*函数原型：函数原型的出现是为了解决形参与实参的类型不匹配问题
然而，函数来接受参数时也进行了类型提升，当传给函数一个float时，函数实际收到的是double（同一的类型方便简化编译器）
如果使用了函数原型，那么实际上就不会进行类型提升，如果声明需要char，那么函数得到也是char，而不是int。
*/
//其他的现在看来好像没什么用
//END
    system("pause");
    return 0;
}