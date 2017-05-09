# 使用说明

### 使用步骤
1. 在当前文件夹下打开cmd窗口
2. 输入ipython notebook运行
3. 打开Python Performance笔记本，使用Shift+回车逐个Cell运行

### 编译Cython
打开cmd，输入运行：
> python setup.py build_ext --inplace

### 文件说明
* Python Performance.ipynb：Jupyter Notebook笔记本
* test.pyx：Cython模块的源代码
* test_setup.py：编译test.pyx所需的配置文件
* test.pyd：编译好的Cython模块，可以在Python里直接import
