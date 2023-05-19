
class Foo:
    def __init__(self) -> None:
        self.a = 69

def change(x):
    x.a += 1
    print(x.a)
    
x = Foo()
change(x)
print(x.a)