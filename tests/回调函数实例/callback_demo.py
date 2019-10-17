from .even import *


# 中间函数
# 接受一个生成偶数的函数作为参数
# 返回一个奇数
def getOddNumber(k, getEvenNumber):
    return 1 + getEvenNumber(k)


# 起始函数，这里是程序的主函数
def main():
    k = 1
    # 当需要生成一个2k+1形式的奇数时
    i = getOddNumber(k, double)
    print(i)
    # 当需要一个4k+1形式的奇数时
    i = getOddNumber(k, quadruple)
    print(i)
    # 当需要一个8k+1形式的奇数时
    i = getOddNumber(k, lambda x: x * 8)
    print(i)


if __name__ == "__main__":
    main()