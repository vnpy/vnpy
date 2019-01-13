vnpy 2.0 

## 贡献代码
---

如果你遇到了任何BUG，欢迎[创建 Issue]。

我们热烈欢迎任何人为我们的项目贡献代码。无论是多么细小的改工，都可以[提交PR]，我们会认真对待每一个PR。

在提交代码的时候，请遵守以下规则，以提高代码质量：

  * 使用[yapf]（目前必须使用github上的最新代码：```pip install https://github.com/google/yapf/archive/master.zip```）格式化你的代码。对你的每一个文件运行```yapf -i --style .style.yapf <file>```即可。
  * 使用[pylint]检查你的代码，确保没有error和warning。我们使用的pylint规则在项目根目录下。运行```pylint --rcfile=.pylintrc vnpy```即可。
  
  [yapf]:https://github.com/google/yapf
  [pylint]:https://github.com/PyCQA/pylint
  [提交PR]:https://help.github.com/articles/creating-a-pull-request/
  [创建 Issue]:http://pylint.pycqa.org/en/latest/tutorial.html



