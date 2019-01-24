# 生成细节

autocxxpy核心分为三部分：
 * CXXParser:负责分析C++文件，输出defines，class，function，constants之类的信息
 * PreProcessor:负责分析CXXParser的结果，对一些特别的量进行识别，比如定义成常量的define，一个类是否是纯类等等
 * Generator:负责生成代码

## 生成过程
要使用这个生成器，首先指定要分析的头文件，使用CXXParser分析。
```python
r0: CXXParseResult = CXXParser([self.md_header, self.td_header]).parse()
```
然后将结果传入预处理器
```python
r1: PreProcessorResult = PreProcessor(r0).process()
```
最后将第一步和第二部的结果一起传入Generator。  
注意：除了classes以外，所有参数都可以置空或者仅从第一步提取。
最终返回的是一组字典```Dict[str, str]```，记录着生成的文件名和对应的内容。
用户只需要江这些结果保存下来即可。
```python
options = GeneratorOptions(
    typedefs=r0.typedefs,
    constants=r0.variables & r1.const_macros,
    functions=r0.functions,
    classes=r1.classes,
    dict_classes=r1.dict_classes,
    enums=r0.enums,
)

```

## Q & A
### 为什么会有PreProcessor
理想情况下，一个cxx到pyd的生成器应该是只需要提供头文件，即可生成正确的pyd文件。    
但是cxx语法丰富，包容各种写法。虽然主流写法大体是一致的，但是我们也不能忽视大量非主流写法的存在。要包容所有的写法是一件比较困难的事情。  
这些写法虽然不会导致最终无法生成pyd，但是会导致pyd难以使用，或者使得最终生成的文件效率低下。  
例如有些人可能会用define定义常量或者内联函数。忽略掉这些东西显然会降低我们的python端的代码体验。  
所以我们使用PreProcessor将一些分析奇葩写法得到的结果转换成主流写法的结果。  
如果你觉得这些转化是多余的，你可以不使用PreProcessor的结果。

