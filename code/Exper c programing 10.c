#include <bits/stdc++.h>
/*虽然函数的返回值不能是一个数组，但是可以是指针，因此可以采用返回指针的方式来返回一个数组*/
int (*f1(void))[5]
{
    // f1是一个返回类型为指向5个int数组的指针的函数
    int(*test1)[5];
    test1 = (int(*)[5])calloc(5, sizeof(int));
    // 此处使用calloc（malloc）函数可以避免返回指向局部变量的指针而导致错误,因为程序员手动申请的内存在函数结束时不会被释放
    if (!test1)
        exit(0);
    return test1; // 返回该数组指针
}

// 增加元素
//  如果要调整已经申请的内存的大小，可以使用realloc函数，它可以实现重新分配
//  realloc(指向申请的内存的指针，新的内存大小)
/*步骤如下：
1 检查原有的内存是否已满
2 如果已满，使用realloc来扩展内存的大小，并检查确保realloc函数成功申请到新的内存
3 对新增加的内存继续操作
*/
/*值得注意的是:
1 realloc会把原来的整个移到新的内存区域,原有的地址不再有效,因此应该使用下标来来访问元素
2 当一个大型表被扩大时，系统运行速度可能会变慢
3 所以增加和删除操作都使用函数来进行，这样才能维持表的完整性
4 不要直接把realloc函数的返回值赋值给字符指针,如果realloc失败,那么它就会返回null,使得无法再访问现有的表
5 当缩小表时,多余的内存应该释放

*/
void add_element(char c, char *dynamic, int current_elements, int size)
{
    if (current_elements == size)
    {
        dynamic = (char *)realloc(dynamic, size + 1);
        if (!dynamic)
            perror("cannot expand the table");
    }
    current_elements++;
    size++;
    dynamic[size] = c;
}
int main()
{
    // 千万不要忘记，当你用一只手指指向别人时，你还有另外三只手指指向自己
    // 第十章：再论指针
    /*多维数组的内存排列方式是线性的，例如int a[2][2],实际上在内存中是连续的四个int排列在内存中
    计算左值a[i][j]时：首先找到a[i]的位置，然后根据偏移量j找到地址a[i][j]，之后解引用取得地址上的数据
    因此a[i][j]被编译器转化为*(*(a+i)+j)
    char a[2][2]
    char *a[2]
    char **a[2]
    char (*a)[2]
    由于编译器的转化，以上的几个都可以被看作是二维字符串数组，只不过他们的访问步骤大同小异而已
    */
    /*指针数组在声明时也要初始化，*/
    char *pea[10];
    // for (int i = 0; i < 10;i++)
    // {
    //     pea[i] = (char *)malloc(sizeof(char));
    // }
    /*
    由于二维字符数组有的时候并没有全部填满，例如char array[10][10]可能在a[2]这一行只有3个字符，其他的都有'\0'，这样会造成极大的空间浪费
    锯齿状数组：基于以上的发现，并且字符串是连续排列的。因此可以采用字符指针数组，也就是pea，这样可以节约内存空�?
    */
    char str1[] = "the first string";
    char str2[] = "the seocnd string";
    pea[0] = &str1[0];
    pea[1] = &str2[0];
    printf("str1=%s,sizeof(str1)=%d\n", pea[0], sizeof(str1));
    printf("str2=%s,sizeof(str2)=%d\n", pea[1], sizeof(str2));
    // pea[0]与pea[1]所指向的字符串长度不一样，因此pea的排列出来的样子就像锯齿一样
    // 字符串复制
    pea[2] = (char *)malloc(strlen(pea[0]) + 1);
    strcmp(pea[2], str1);
    printf("str3=%s,sizeof(str3)=%d\n", pea[2], sizeof(pea[2]));
    // 最好不要复制整个字符串，如果需要从两个不同的数据结构访问，复制一个指针要明智的多。
    /*启发：实际上在传递给函数时
    数组的数组（多维数组）会被转化为相应的数组指针
    指针数组会被转化为指针的指针（二级指针）
    数组指针（行指针）和二级指针不会改变
                   实参                所匹配的形参
    多维数组  char c[10][10]            char (*c)[10]
    指针数组  char *c[10]               char **c
    */
    /*向函数传递数组：由于数组会被转化为指针，因此向函数传递数组时，还应该加上数组的长度，这样在函数中访问时就不容易出现分段错误
    多维数组时，不仅需要一个参数来提示每一行的结束，也就是每一个有多少个元素或者是有多少列。还需要一个参数来提示有多少行，来提示行的结束
     或者是，可以使用数组array1[x+1]，数组的元素是一个指向数组array2[y]的指针。长度为x+1，多出的1用于存放'\0'或者nULL来提示行结束
     至于函数的参数，当然char a[10][10],char a[][10],char (*a)[10]都可以，但是这些就只能处理每行十个元素的数组
     因此可以采用 char *a[]或者char **a（实际上前者在接受为参数时会被转化为后者
    */

    // 调用返回数组指针的函数
    int(*result)[5];
    result = f1();
    (*result)[0] = 1; // 访问第一个元素，先解引用访问到数组，再使用下标继续访问数组中的元素
    printf("(*result)[0]=%d\n", (*result)[0]);
    free(result); // 避免内存溢出

    // 用指针和malloc来使用动态内存
    // 原理：通过malloc函数来申请出一块内存空间，再用一个指针指向这块内存，之后由于数组的下标访问可以改写为一个指针加上偏移量的解引用，因此可以采用数组的下标访问来访问元素
    int size = 0;
    int total_element = 0;
    char *dynamic; // 用于指向申请的内存的指针
    char input[10];
    printf("请输入大小：\n");
    size = atoi(fgets(input, 7, stdin)); // atoi函数把参数str指向的字符串转化为一个int的整型值
    dynamic = (char *)malloc(size + 1);  // 加一用来放'\0'
    int current_elements = 0;            // 用于表示已经使用的大小
    int i;
    for (i = 0; i < size; i++)
    {
        dynamic[i] = 'a' + i;
        current_elements++;
    }
    dynamic[i] = '\0';
    for (int j = 0; j < size; j++)
        printf("%c ", dynamic[j]);
    printf("\n");
//第十章结束
    system("pause");
    return 0;
}