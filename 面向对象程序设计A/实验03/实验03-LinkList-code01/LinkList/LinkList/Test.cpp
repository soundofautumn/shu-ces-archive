// Test.cpp
#include "LinkList.h"
#include <cstring>

#ifdef _MSC_VER
#include <conio.h>
#else
#define getch() cin.get()
#endif

int Pause(const char *prompt = "按任意键继续……") {
    cout << prompt;
    return getch();
}

void test1()                // 测试类模板LinkList的 构造函数、输出运算符（包括文件I/O）、析构函数，链表的链表测试等
{
    int n, iArray[] = {900, 800, 500};                    // 准备好int型数组
    int iN = sizeof(iArray) / sizeof(*iArray);

    LinkList<int> iLink0, iLink1(2), iLink2(iN, iArray), iLArray[] = {iLink0, iLink1, iLink2};
    // 创建3条链表（结点数分别为0, 2, 3），以及一个链表数组（元素个数为3，即三条链表组成的数组）
    int nLL = sizeof(iLArray) / sizeof(*iLArray);
    LinkList<LinkList<int> > iLLink(nLL, iLArray);
    // 创建链表的链表，即以链表作为数据域数据

    cout << "\n\n(1.1) 输出链表（第一种格式）" << endl;
    cout << "\tcout << iLink0 << endl;" << endl;
    cout << iLink0 << endl;
    cout << "\tcout << iLink1 << endl;" << endl;
    cout << iLink0 << endl;
    cout << "\tcout << iLink2 << endl;" << endl;
    cout << iLink0 << endl;
    Pause();

    cout << "\n\n(1.2) 输出链表数组元素" << endl;
    for (int i = 0; i < nLL; i++)
        cout << iLArray[i] << endl;
    Pause();

    cout << "\n\n(1.3) 输出链表（另一种格式）" << endl;
    cout << "\tiLink0.ShowList();" << endl;
    iLink0.ShowList();
    cout << "\tiLink1.ShowList();" << endl;
    iLink1.ShowList();
    cout << "\tiLink2.ShowList();" << endl;
    iLink2.ShowList();
    Pause();

    cout << "\n\n(1.4) 输出链表的链表（两种格式）" << endl;
    cout << "\tcout << iLLink << endl;" << endl;
    cout << iLLink << endl;
    cout << "\tiLLink.ShowList();" << endl;
    iLLink.ShowList();
    Pause();

    cout << "\n\n(1.5) 链表的链表存盘" << endl;
    cout << "\tn = iLLink.Save(\"LLink.txt\");" << endl;
    n = iLLink.Save("LLink.txt");
    cout << "\t" << n << " 个结点数据写入文件 \"LLink.txt\" 中" << endl;
    Pause();

    cout << "\n\n(1.6) 从文件中读取数据时构造链表。先释放链表中的所有结点" << endl;
    cout << "\tiLLink.FreeList(); iLLink.ShowList();" << endl;
    iLLink.FreeList();
    iLLink.ShowList();
    cout << "\tn = iLLink.Load(\"LLink.txt\");" << endl;
    n = iLLink.Load("LLink.txt");
    cout << "\t读取 " << n << " 个结点数据，构造链表。读取结果如下" << endl;
    cout << iLLink << endl;
    Pause();

    double dArray[] = {1.414, 2.718, 3.142};                    // 准备好double型数组
    int dN = sizeof(dArray) / sizeof(*dArray);
    LinkList<double> dLink0, dLink1(2), dLink2(dN, dArray);        // 创建3条链表（结点数分别为0, 2, 3）

    cout << "\n\n(1.7) 数据域为double型数据测试" << endl;
    dLink0.ShowList();
    cout << dLink0 << endl;
    dLink1.ShowList();
    cout << dLink1 << endl;
    dLink2.ShowList();
    cout << dLink2 << endl;
    Pause();

    n = dLink2.Save("dLink.txt");
    cout << "\n\n(1.8) 将链表数据（共 " << n << " 个结点数据写入文件 \"dLink.txt\" 中" << endl;
}

void test2()    // 测试插入，查找/继续查找，修改（替换）数据，倒置、排序等成员函数
{
    int iArray[] = {1, 2, 3, 3, 5, 6, 7, 8, 8, 3};
    int n = sizeof(iArray) / sizeof(*iArray);
    LinkList<int> iLink(n, iArray);

    cout << "\n原始链表" << endl;
    iLink.ShowList();
    cout << "\n\n(2.1) 将 0 插入到链首结点前，成为新的链首结点" << endl;
    iLink.Insert(0);
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.2) 将 100 插入到链尾结点后，成为新的链尾结点" << endl;
    iLink.Append(100);
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.3) 将当前结点移至第3个结点（从0开始）";
    iLink.Go(3);
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.4) 在当前结点前插入 30" << endl;
    iLink.InsertBefore(30);
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.5) 在当前结点后插入 40" << endl;
    iLink.InsertAfter(40);
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.6) 将链表各结点倒置" << endl;
    iLink.Reverse();
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.7) 链表排序（升序）" << endl;
    iLink.Sort(int(0));
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.8) 链表排序（降序）" << endl;
    iLink.Sort(int(0), false);
    iLink.ShowList();
    Pause();

    cout << "\n\n(2.9) 测试异常。链表中当前结点绝对定位成员函数Go(n)，序号n可能超出结点数" << endl;
    for (int i = iLink.NumNodes() + 1; i > -2; i--) {
        cout << "Go(" << i << "): ";
        iLink.Go(i);        // 可能使cur_node为NULL
        try {
            cout << iLink.CurData() << endl;
        }
        catch (int) {
            cout << "\t捕捉到异常：超出结点数范围" << endl;
        }
    }
    Pause();

    int x;
    cout << "\n\n(2.10) 在链表中查找并修改（替换）数据，请输入要查询的数据: ";
    cin >> x;
    Node<int> *p;
    p = iLink.Locate(x, true);
    n = 0;
    while (p != NULL) {
        cout << "找到第 " << iLink.CurPos() << " 结点(编号从0开始)：\t" << iLink.CurData() << endl;
        cout << "修改为: ";
        cin >> iLink.CurData();                // 函数调用表达式 iLink.CurData() 做左值，上面曾做右值
        n++;
        p = iLink.Locate(x);
    }
    cout << "\t共找到 " << n << " 个结点满足条件" << (n > 0 ? "，并进行了修改。" : "。") << endl;
    cout << "\n将当前结点设置为首结点" << endl;
    iLink.GoTop();
    iLink.ShowList();
}

void test3()                                // 测试当前结点绝对定位、相对定位，删除当前结点函数
{
    int n, interval, k = 0, m;
    cout << "\n约瑟夫(Josephus)问题" << endl;
    cout << "有n个小孩(编号1~n)围成一圈，从第1个小孩开始按顺时针方向从1~m循环报数，报到m的小孩出圈。"
         << "最后剩下的小孩为胜利者。" << endl;
    cout << "请输入小孩人数 间隔数(如 10 3 ): ";
    cin >> n >> interval;

    if (interval <= 1) {
        cout << "间隔数应该大于1，现调整为2。" << endl;
        interval = 2;
    }
    LinkList<int> link;
    for (int i = 1; i <= n; i++)
        link.Append(i);
    link.GoTop();
    cout << "初始态\t";
    link.ShowList();
    while (link.NumNodes() > 1) {
        if (++k == interval) {
            m = link.DeleteCurNode();
            cout << m << " 出圈\t";
            if (link.CurNode() == NULL)
                link.GoTop();
            k = 1;
            Pause("");
        } else
            cout << "\t";
        link.Skip();
        if (link.CurNode() == NULL)
            link.GoTop();
        link.ShowList();
    }
    cout << "胜利者: " << link.CurData() << " 号。" << endl;
}
