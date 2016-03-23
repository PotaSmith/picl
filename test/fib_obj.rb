class MyInt
    def initialize(a)
        @value = a
    end
    def add(a)
        MyInt.new(@value + a.value)
    end
    def sub(a)
        MyInt.new(@value - a.value)
    end

    def value
        @value
    end

    def returnable?
        @value < 2
    end

    def to_s
        @value.to_s
    end

end

def fib(n)
    if (n.returnable?) then n else return fib(n.sub(MyInt.new(2))).add(fib(n.sub(MyInt.new(1)))) end
end

puts fib(MyInt.new(30)).to_s

