#include <iostream>
using namespace std;
void print(char* str)
{
    cout<<"├───────────────────────────────"<<endl<<"│"<<str<<":"<<endl;
}
/*
* 定义抽象的方法类
* 是装饰器中扩展的方法的定义
*/
class absTable
{
public:
virtual void putTable() = 0;
};



/**  定义底层的操作方法* */
class BaseTable:public absTable
{
public:
    virtual void putTable()
    {
        print("姓名");
        print("性别");
        print("学历");
        print("年龄");
        cout<<"└───────────────────────────────"<<endl;
    }
};
/*
*   定义数据对象基类，包含“方法对象”的私有变量
*   装饰器的基类，起了承上启下的作用， 
*   里面的方法实现上，调用被装饰者的方法
*
* */
class Decorator:public absTable
{
public:
    //构造函数中传入对象
    Decorator(absTable* concrateTb):mpAbsTable(concrateTb){}

    virtual void putTable()
    {
        mpAbsTable->putTable();
    }
private:
    absTable* mpAbsTable;
};

class EnglishDcrt:public Decorator
{
public:
    /*构造函数中传入，底层的实现方法*/
    EnglishDcrt(absTable* pTb):Decorator(pTb){}

    virtual void putTable()
    {
        //添加新的实现方法
        print("英语等级");
        //调用底层的实现分方法
        Decorator::putTable();
    }
};

class CurWage:public Decorator
{
public:
    CurWage(absTable* pTb):Decorator(pTb){}

    virtual void putTable()
    {
        print("当前薪水");
        Decorator::putTable();
    }
};

//继承 装饰器虚拟类
class Experience:public Decorator
{
public:
    //装饰器的构造函数，
    Experience(absTable* pTb):Decorator(pTb){}

    virtual void putTable()
    {
        //添加新的方法
        print("项目经验");
        Decorator::putTable();
    }
};


int main()
{
    BaseTable pro1;
    cout<<"初始表格："<<endl<<endl;
    pro1.putTable();

    cout<<"新表格1："<<endl<<endl;
    EnglishDcrt eng(&pro1);
    eng.putTable();

    cout<<"新表格2："<<endl<<endl;
    CurWage wg(&eng);
    wg.putTable();

    cout<<"新表格3："<<endl<<endl;
    Experience ex(&wg);
    ex.putTable();
    return 0;
}
