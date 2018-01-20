# korbit API wrapper for Python

You can get detail information of API in [API Reference](https://apidocs.korbit.co.kr/)


## Installation
Install from Git Repository
```sh
pip install git+https://github.com/HoonJin/korbit-python.git
```

## Basic Usage
You can use public API very easily.
```python
import korbit
korbit.ticker()
```

## If you want to use Exchange
You have to get API key in [this page](https://www.korbit.co.kr/settings/api)
```python
import korbit
api = korbit.PrivateAPI('your key', 'your secret')
api.create_token_directly('your email', 'your pa$$w0rd')

api.market_ask_order(0.01)
```


## License
The MIT License (MIT)

Copyright (c) 2016-2017 HoonJin(Daniel) Ji bwjhj1030@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
