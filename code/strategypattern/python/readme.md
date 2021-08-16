
# Python @函数装饰器及用法
Python 内置的 3 种函数装饰器，分别是 `＠staticmethod、＠classmethod 和 @property`，其中 staticmethod()、classmethod() 和 property() 都是 Python 的内置函数。
Python内置有三大装饰器：@staticmethod(静态方法)、@classmethod(类方法)、@property(描述符)，其中静态方法就是定义在类里的函数，并没有非要定义的必要；类方法则是在调用类属性、传递类对象时使用；而@property则是一个非常好用的语法糖。@property最大的好处就是在类中把一个方法变成属性调用，起到既能检查属性，还能用属性的方式来访问该属性的作用。



那么，函数装饰器的工作原理是怎样的呢？
假设用 funA() 函数装饰器去装饰 funB() 函数，如下所示：
```python
#funA 作为装饰器函数
def funA(fn):
    #...
    fn() # 执行传入的fn参数
    #...
    return '...'
@funA
def funB():
    #...
```
实际上，上面程序完全等价于下面的程序：

```python
def funA(fn):
    #...
    fn() # 执行传入的fn参数
    #...
    return '...'
def funB():
    #...
funB = funA(funB)
```
通过比对以上 2 段程序不难发现，使用函数装饰器 A() 去装饰另一个函数 B()，其底层执行了如下 2 步操作：
将 B 作为参数传给 A() 函数；
将 A() 函数执行完成的返回值反馈回  B。

举个实例：
```python
#funA 作为装饰器函数
def funA(fn):
    print("C语言中文网")
    fn() # 执行传入的fn参数
    print("http://c.biancheng.net")
    return "装饰器函数的返回值"
@funA
def funB():
    print("学习 Python")
```
程序执行流程为：
C语言中文网
学习 Python
http://c.biancheng.net

在此基础上，如果在程序末尾添加如下语句：
print(funB)
其输出结果为：
装饰器函数的返回值

显然，被“＠函数”修饰的函数不再是原来的函数，而是被替换成一个新的东西（取决于装饰器的返回值），即如果装饰器函数的返回值为普通变量，那么被修饰的函数名就变成了变量名；同样，如果装饰器返回的是一个函数的名称，那么被修饰的函数名依然表示一个函数。
实际上，所谓函数装饰器，就是通过装饰器函数，在不修改原函数的前提下，来对函数的功能进行合理的扩充。

## 带参数的函数装饰器
在分析 funA() 函数装饰器和 funB() 函数的关系时，细心的读者可能会发现一个问题，即当 funB() 函数无参数时，可以直接将 funB 作为 funA() 的参数传入。但是，如果被修饰的函数本身带有参数，那应该如何传值呢？

比较简单的解决方法就是在函数装饰器中嵌套一个函数，该函数带有的参数个数和被装饰器修饰的函数相同。例如：
```python
def funA(fn):
    # 定义一个嵌套函数
    def say(arc):
        print("Python教程:",arc)
    return say
@funA
def funB(arc):
    print("funB():", a)

funB("http://c.biancheng.net/python")
```
程序执行结果为：
Python教程: http://c.biancheng.net/python

这里有必要给读者分析一下这个程序，其实，它和如下程序是等价的：

```python
def funA(fn):
    # 定义一个嵌套函数
    def say(arc):
        print("Python教程:",arc)
    return say
def funB(arc):
    print("funB():", a)
   
funB = funA(funB)
funB("http://c.biancheng.net/python")
```
如果运行此程序会发现，它的输出结果和上面程序相同。

显然，通过 funB() 函数被装饰器 funA() 修饰，funB 就被赋值为 say。这意味着，虽然我们在程序显式调用的是 funB() 函数，但其实执行的是装饰器嵌套的 say() 函数。

但还有一个问题需要解决，即如果当前程序中，有多个（≥ 2）函数被同一个装饰器函数修饰，这些函数带有的参数个数并不相等，怎么办呢？

最简单的解决方式是用 *args 和 **kwargs 作为装饰器内部嵌套函数的参数，*args 和 **kwargs 表示接受任意数量和类型的参数。举个例子：
def funA(fn):
    # 定义一个嵌套函数
    def say(*args,**kwargs):
        fn(*args,**kwargs)
    return say
@funA
def funB(arc):
    print("C语言中文网：",arc)
@funA
def other_funB(name,arc):
    print(name,arc)
funB("http://c.biancheng.net")
other_funB("Python教程：","http://c.biancheng.net/python")
运行结果为：
C语言中文网： http://c.biancheng.net
Python教程： http://c.biancheng.net/python

函数装饰器可以嵌套
上面示例中，都是使用一个装饰器的情况，但实际上，Python 也支持多个装饰器，比如：
@funA
@funB
@funC
def fun():
    #...
上面程序的执行顺序是里到外，所以它等效于下面这行代码：
fun = funA( funB ( funC (fun) ) )

这里不再给出具体实例，有兴趣的读者可自行编写程序进行测试。
# python @property的介绍与使用
python的@property是python的一种装饰器，是用来修饰方法的。

## 作用：
我们可以使用@property装饰器来创建只读属性，
@property装饰器会将方法转换为相同名称的只读属性,可以与所定义的属性配合使用，这样可以防止属性被修改。

## 使用场景：
1.修饰方法，是方法可以像属性一样访问。
```python
class DataSet(object):
  @property
  def method_with_property(self): ##含有@property
      return 15
  def method_without_property(self): ##不含@property
      return 15

l = DataSet()
print(l.method_with_property) # 加了@property后，可以用调用属性的形式来调用方法,后面不需要加（）。
print(l.method_without_property())  #没有加@property , 必须使用正常的调用方法的形式，即在后面加()
两个都输出为15。

class DataSet(object):
  @property
  def method_with_property(self): ##含有@property
      return 15
l = DataSet()
print(l.method_with_property（）) # 加了@property后，可以用调用属性的形式来调用方法,后面不需要加（）。
```
如果使用property进行修饰后，又在调用的时候，方法后面添加了()， 那么就会显示错误信息：TypeError: 'int' object is not callable，也就是说添加@property 后，这个方法就变成了一个属性，如果后面加入了()，那么就是当作函数来调用，而它却不是callable（可调用）的。

```python
class DataSet(object):
  def method_without_property(self): ##不含@property
      return 15
l = DataSet()
print(l.method_without_property） #没有加@property , 必须使用正常的调用方法的形式，即在后面加()
```
没有使用property修饰，它是一种方法，如果把括号去掉，不会报错输出的就会是方法存放的地址。

2.与所定义的属性配合使用，这样可以防止属性被修改。
​ 由于python进行属性的定义时，没办法设置私有属性，因此要通过@property的方法来进行设置。这样可以隐藏属性名，让用户进行使用的时候无法随意修改。

```python
class DataSet(object):
    def __init__(self):
        self._images = 1
        self._labels = 2 #定义属性的名称
    @property
    def images(self): #方法加入@property后，这个方法相当于一个属性，这个属性可以让用户进行使用，而且用户有没办法随意修改。
        return self._images 
    @property
    def labels(self):
        return self._labels
l = DataSet()
```
用户进行属性调用的时候，直接调用images即可，而不用知道属性名_images，因此用户无法更改属性，从而保护了类的属性。
print(l.images) # 加了@property后，可以用调用属性的形式来调用方法,后面不需要加（）。


## 1. 问题提出
python中用”.”操作来访问和改写类的属性成员时，会调用__get__和__set__方法，模式情况下，python会查找class.__dict__字典，对对应值进行操作。
比如C.x会调用C.__get__访问最终读取C.__dict__[x]元素。

如果需要读取时对输出结果进行修饰或者对输入进行合法化检查，
通常做法是自己写get和set函数，并通过调get和set函数进行读写类成员属性。

例子：
```python
class Timer:
 
  def __init__(self, value = 0.0):
    self.time = value
    self.unit = 's'
 
  def get_time(self):
    return str(self.time) + ' ' + self.unit
 
  def set_time(self, value):
    if(value < 0):
      raise ValueError('Time cannot be negetive.')
    self.time = value
 
t = Timer()
t.set_time(1.0)
t.get_time()
```
但是这样并不美观，那有没有美颜的办法呢？当然！

## 2. 解决方案
在变量x前面加下划线_表示为私有变量_x，并将变量名x设为用property函数返回的对象(property object)。

property函数的声明为

def property(fget = None, fset = None, fdel = None, doc = None) -> <property object>
其中fget, fset, fdel对应变量操作的读取(get)，设置(set)和删除(del)函数。 
而property对象<property object>有三个类方法，即setter, getter和delete，用于之后设置相应的函数。

## 3.实现效果
在操作类私成员的时候调用__get__和__set__方法时，不再采用默认的读取字典的方法，而使用property中fget和fset指定的方法，从而实现了方便的赋值操作。 
注意，即使在__init__函数中调用赋值语句，也使用的是fset方法。

例子：
```python
class Timer:
 
  def __init__(self, value = 0.0):
    # 1. 将变量加"_"，标志这是私有成员
    self._time = value
    self._unit = 's'
 
  def get_time(self):
    return str(self._time) + ' ' + self._unit
 
  def set_time(self, value):
    if(value < 0):
      raise ValueError('Time cannot be negetive.')
    self._time = value
 
  # 将变量名赋值为包含get和set方法的property对象
  time = property(get_time, set_time)
 
t = Timer()
t.time = 1.0
print(t.time)
```
这样的访问和设置和赋值语句一样非常自然了。

上面的例子中，如果`采用property对象`的方法而不是用property函数，那么
```python
# time = property(get_time, set_time)
# =========将变成==============>>>
time = property()
time = time.getter(get_time)
time = time.setter(set_time)
```

## 4. property装饰器
如果觉得在最后加property函数这样写类的时候还是不自然，容易忘会写错，那么装饰器可以让类的书写帅到飞起。

例子：
```python
class Timer:
 
  def __init__(self, value = 0.0):
    self._time = value
    self._unit = 's'
 
  # 使用装饰器的时候，需要注意：
  # 1. 装饰器名，函数名需要一直
  # 2. property需要先声明，再写setter，顺序不能倒过来
  @property
  def time(self):
    return str(self._time) + ' ' + self._unit
 
  @time.setter
  def time(self, value):
    if(value < 0):
      raise ValueError('Time cannot be negetive.')
    self._time = value
 
t = Timer()
t.time = 1.0
print(t.time)
```
这两个装饰器 
@property装饰器会把成员函数x转换为getter，相当于做了x = property(); x = x.getter(x_get) 
@x.setter装饰器会把成员函数x转换为setter，相当于做了x = x.seter(x_set).

可以看到我们实现了通过属性x来对私有变量_x进行操作 

@property应用
  让我们先看下@property的应用，其功能1是可定义只读属性，也就是真正意义上的私有属性(属性前双下划线的私有属性也是可以访问的，具体参照这篇文章：私有属性真的是私有的吗？)。实例需求是定义类Person，具有年龄和姓名，要求年龄必须等于18，则代码如下：

class Person(object):
    def __init__(self, name, age=18):
        self.name = name
        self.__age = 18

    @property
    def age(self):
        return self.__age
        
xm = Person('xiaoming')  #定义一个人名小明
print(xm.age)	#结果为18
xm.age = -4	#报错无法给年龄赋值
print(xm.age)
1
2
3
4
5
6
7
8
9
10
11
12
13
结果如下：

18
Traceback (most recent call last):
	xm.age = 18
AttributeError: can't set attribute
1
2
3
4
  在python中定义只读属性非@property莫属，如果细心留意大部分源码，都跑不了@property的身影。而定义只读属性也很简单：以需要定义的属性为方法名(上例age属性定义为方法)，其上装饰内置装饰器@property就ok了。
  @property真正强大的是可以限制属性的定义。往往我们定义类，希望其中的属性必须符合实际，但因为在__init__里定义的属性可以随意的修改，导致很难实现。如我想实现Person类，规定每个人(即创建的实例)的年龄必须大于18岁，正常实现的话，则必须将属性age设为只读属性，然后通过方法来赋值，代码如下：

class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.__age = 18

    @property
    def age(self):
        return self.__age

    def set_age(self, age): #定义函数来给self.__age赋值
        if age < 18:
            print('年龄必须大于18岁')
            return
        self.__age = age
        return self.__age
     
     xm = Person('xiaoming', 20)
     
print(xm.age)
print('----------')
xm.set_age(10)
print(xm.age)
print('----------')
xm.set_age(20)
print(xm.age)
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
  为了便于区分结果，增加了分隔符，结果如下：

18
----------
年龄必须大于18岁
18
----------
20
1
2
3
4
5
6
  可以看到，通过方法的确能限制输入，但是不是每个人都记得方法名，有什么简化的方法呢？@property就能很轻松办到，修改代码如下：
```python
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.__age = 18

    @property
    def age(self):
        return self.__age

    @age.setter
    def age(self, age):
        if age < 18:
            print('年龄必须大于18岁')
            return
        self.__age = age
        return self.__age

xm = Person('xiaoming', 20)
print(xm.age)
print('----------')
xm.age = 10
print(xm.age)
print('----------')
xm.age = 20
print(xm.age)
```
  结果和上图一致。两段代码变化的内容：将set_age修改为age，并且在上方加入装饰器@age.setter。这就是@property定义可访问属性的语法，即仍旧以属性名为方法名，并在方法名上增加@属性.setter就行了。

@property实现原理
  在开头说过，@property是个描述符(decorator)，实际上他本身是类，不信的话，可以将上述代码修改如下：
```
class Person(object):
    def __init__(self, name, age):
        self.name = name
        self.__age = 18

    def get_age(self): #恢复用方法名来获取以及定义
        return self.__age

    def set_age(self, age): 
        if age < 18:
            print('年龄必须大于18岁')
            return
        self.__age = age
        return self.__age

    age = property(get_age, set_age)  #增加property类
```
  上述代码的运行结果和前面一致，将@property装饰的属性方法再次修改回定义方法名，然后再类的最下方，定义：属性=property(get,set,del)，这个格式是固定的，通过源码可以知道原因，property部分源码如下：
```python
class property(object):
	def __init__(self, fget=None, fset=None, fdel=None, doc=None):
		“”“
        Property attribute.
        
          fget
            function to be used for getting an attribute value
          fset
            function to be used for setting an attribute value
          fdel
            function to be used for del'ing an attribute
		class C(object):
            @property
            def x(self):
                "I am the 'x' property."
                return self._x
            @x.setter
            def x(self, value):
                self._x = value
            @x.deleter
            def x(self):
                del self._x
  		”“”
 		pass	
     def __set__(self, *args, **kwargs): # real signature unknown
       """ Set an attribute of instance to value. """
       	pass
     def __get__(self, *args, **kwargs): # real signature unknown
	    """ Return an attribute of instance, which is of type owner. """
	    pass
     def __delete__(self, *args, **kwargs): # real signature unknown
        """ Delete an attribute of instance. """
        pass
```
  为了不让篇幅过长，同时影响到阅读效果，这边截取了部分，可以看到代码注释里写了官方的@property用法，同时如果是用类来实现的话，必须得按__init__的参数里顺序fget/fset/fdel依次填入get、set、del方法，因为都是默认参数，所以都可以省略不写。
  介绍下python的描述符，定义：如果一个类里定义了__set__、__get __ 、__delete __三个方法之一，同时给另一个类的属性赋值为实例，那么该类可以称之为描述符。因为描述符的使用目前就python，所以了解下就行了。

总结
  关于@property的介绍到此为止，@property装饰器就是一个语法糖(语法糖指那些没有给计算机语言添加新功能，而只是对人类来说更“甜蜜”的语法。 语法糖往往给程序员提供了更实用的编码方式，有益于更好的编码风格，更易读。)。
————————————————
版权声明：本文为CSDN博主「sandwu」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_42681866/article/details/83376484


# python ->的用法

->常常出现在python函数定义的函数名后面，为函数添加元数据,描述函数的返回类型，从而方便开发人员使用。比如：
通常的写法是：
def attrs(self) -> _Attrs:
    pass
这种写法通常是写在函数的函数名后面 
def add(x, y) -> int:
  return x+y
这里面，元数据表明了函数的返回值为int类型。
至于楼主问题中的，-> _Attr则表明函数返回的是一个外部可访问的类的私有变量。

# 参考文档
[abc --- python 抽象基类](https://docs.python.org/zh-cn/3/library/abc.html)
