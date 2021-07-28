/*************************************************************************
    > File Name: main.cpp
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      三  7/28 18:46:08 2021
    > Abstract: 
 ************************************************************************/
#include <iostream>
#include <string>
using namespace std;

//公用方法的基类，定义了被装饰函数
class Pancake 
{
public:
    string description = "Basic Pancake";
    virtual string getDescription() { return description; }
    virtual double cost() = 0;
};

class CondimentDecorator : public Pancake //装饰器基类
{
public:
    string getDescrition();
};

class MeatPancake : public Pancake //肉煎饼
{
public:
    MeatPancake() { description = "MeatPancake"; }
    double cost() { return 6; }
};
class EggPancake : public Pancake //鸡蛋煎饼
{
public:
    EggPancake() { description = "EggPancake"; }
    double cost() { return 5; }
};

class Egg : public CondimentDecorator //额外加鸡蛋
{
public:
    Pancake *base;
    string getDescription() { return base->getDescription() + ", Egg"; }
    Egg(Pancake *d) { base = d; }
    double cost() { return base->cost() + 1.5; }
};
class Potato : public CondimentDecorator //额外加土豆
{
public:
    Pancake *base;
    string getDescription() { return base->getDescription() + ", Potato"; }
    Potato(Pancake *d) { base = d; }
    double cost() { return base->cost() + 1; }
};

class Bacon : public CondimentDecorator //额外加培根
{
public:
    Bacon(Pancake *d) { base = d; }
    Pancake *base;
    string getDescription() { return base->getDescription() + ", Bacon"; }
    double cost() { return base->cost() + 2; }
};

int main()
{
    EggPancake pan1 =  EggPancake();
    Potato  pan2 = Potato(&pan1);
    Bacon pan3 = Bacon(&pan2);
    cout << pan3.getDescription() << "  $ : " << pan3.cost() << endl;
    return 0;
}
