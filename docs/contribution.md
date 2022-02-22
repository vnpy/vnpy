# 贡献代码

---
## 创建PR
我们欢迎任何人贡献代码到VeighNa。  

如果希望贡献代码请使用Github的PR(Pull Request)的流程。

PR流程大致如下：

---
1. [创建 Issue][CreateIssue] - 对于较大的改动(如新功能，大型重构等)最好先开issue讨论一下， 较小的improvement(如文档改进，bugfix等)直接发PR即可

2. Fork [VeighNa][#GithubVnpy] - 点击右上角**Fork**按钮

3. Clone你自己的fork: ```git clone https://github.com/$userid/vnpy.git```
	
	> 如果你的fork已经过时，需要手动[sync][GithubDocForSync]
	
4. 从**dev**创建你自己的branch: ```git checkout -b $my_feature_branch dev```

5. 在$my_feature_branch上修改并将修改push到你Fork之后的仓库上

6. 创建从你的fork的$my_feature_branch分支到主项目的**dev**分支的[Pull Request]:  
 [点开这里][CreatePR] ，再点击**compare across forks**，选择需要的fork和branch创建PR

---

创建完PR之后请耐心等待：我们一旦有空就会检查PR，一旦你的代码有用且[符合要求](#代码风格)，就会被合并！


---
## 代码风格
在为VeighNa写代码的时候，需要遵循一些基本的规则，否则你的代码可能无法被merge。
这些规则包括：
- [贡献代码](#贡献代码)
  - [创建PR](#创建pr)
  - [代码风格](#代码风格)
    - [命名规则](#命名规则)
    - [代码格式](#代码格式)
    - [代码质量检查](#代码质量检查)


### 命名规则
我们的代码的命名规则如下：

* 类属性、类方法、参数和变量使用小写加下划线的形式
* 类名使用驼峰式命名
* 常量使用大写加下划线的形式

例如：
```python 3
DEFAULT_PATH = "/tmp/VeighNa/"
class ClassA:
    def __init__(self, arg_one: int, arg_two: str):
        if arg_two is None:
            arg_two = DEFAULT_PATH
        self.property_one = arg_one
        variable_one = "some string"
```


### 代码格式
我们对代码格式没有特别严格的要求，但是至少要符合pep8标准，并且额外要在类和所有函数下面带上docstring(就是一段"""""")。

要让代码符合pep8标准，写完代码之后使用[autopep8](https://github.com/hhatto/autopep8)格式化你的代码就可以了:  
```bash
autopep8 --in-place --recursive . 
```

### 代码质量检查
使用[flake8](https://pypi.org/project/flake8/)检查你的代码，确保没有error和warning。
在项目根目录下运行```flake8```就可以检查出代码中书写不严谨的地方了。如果检查出error或者warning，说明你的代码需要进行一些修改以提升质量。

[GithubVnpy]:https://github.com/vnpy/vnpy
[GithubDocForSync]:https://help.github.com/articles/syncing-a-fork/
[CreateIssue]:https://github.com/vnpy/vnpy/issues/new
[CreatePR]:https://github.com/vnpy/vnpy/compare?expand=1

