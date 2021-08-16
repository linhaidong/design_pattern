from abc import abstractmethod, ABCMeta

#State：定义 Handle() 抽象方法的接口。
#需要通过 ConcreteState 类实现
class State(metaclass=ABCMeta):
    @abstractmethod
    def handle(self):
        pass


# ConcreteState：实现 Handle() 方法，
#可以根据状态变化定义执行的实际操作
class ConcreteStateB(State):
    def handle(self):
        print("ConcreteStateB")


class ConcreteStateA(State):
    def handle(self):
        print("ConcreteStateA")

#Context：接收客户端请求，
#维护着对象当前状态的引用，以根据请求调用具体的行为
class Context(State):
    def __init__(self):
        self.state = None

    def getState(self):
        return self.state

    def setState(self, state):
        self.state = state

    def handle(self):
        self.state.handle()


context = Context()
stateA = ConcreteStateA()
stateB = ConcreteStateB()

context.setState(stateA)
context.handle()
# => ConcreteStateA
