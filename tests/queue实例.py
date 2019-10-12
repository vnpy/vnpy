import queue

'''Queue是python中的标准库，可以直接import 引用，之前学习的时候有听过著名的“先吃先拉”与“后吃先吐”，其实就是这里说的队列，队列的构造的时候可以定义它的容量，别吃撑了，吃多了，就会报错,构造的时候不写或者写个小于1的数则表示无限多'''

q = queue.Queue(10)

# 向队列里面put值
q.put("yang")
q.put("guo")

# 队列里get,如果用get，则阻塞，所以这里用get_nowait,如果阻塞会抛出异常
print(q.get_nowait())
print(q.get_nowait())

