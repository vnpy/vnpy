# vn.ctp

### ���
CTP��̨API�ӿڵ�Python��װ������pyscriptĿ¼�µĽű��Զ�����ͷ�ļ����ɷ�װ����ģ�飬�ṩԭ��C++ API�е�ȫ�����ܡ�


### Ŀ¼˵��
* vnctpmd: ����API
* vnctptd: ����API
* pyscript: �Զ���װ�ű�
* ctpapi��C++ API�ļ�

### ʹ��CMake����

**Windows 7**

��������:

* Anaconda��Boost�İ�װ��ʽ��ο�www.vnpy.org�ϵĽ̳̣�����ʹ��32λ

* cmake:��װ���°汾��cmake,�������ñ��뻷��

* ���û���������BOOST_ROOT = C:\boost_1_57_0

* ���빤�ߣ�Visual Studio 2013


�������:

* ��vn.ctpĿ¼���½��ļ��У�������Ϊbuild, ����������ʱ�ļ������ļ�

* �������й������룺cmake-gui .. ���cmake���ý���

* ���configure��

* ���generate�����û�д��������óɹ�

* ����buildĿ¼��˫��vn_ctp_api.sln�򿪽������

* ������밴ť,�������release��


**Linux (Debian jessie, Ubuntu 16.04,)**

�������ã�

* �ο�[����](http://www.continuum.io/downloads)�Ľ̳����ز���װAnaconda��Linux 64λ�汾

* ʹ��apt-get��װ������صĹ��ߣ�ע��ĳЩ�ϵ�Ubuntu����ָ��ʹ��boost 1.58.0�汾��

    - apt-get install build-essential

    - apt-get install libboost-all-dev

    - apt-get install python-dev

    - apt-get install cmake

* ����ӹ��������µ�ctp api tar��������v6.3.5_20150803_tradeapi_linux64.tar����Ҫ������ctp api so�ļ�����������Ժ��Ըò��裩��

    - thostmduserapi.so --> libthostmduserapi.so

    - thosttraderapi.so --> libthosttraderapi.so

  centos
  see root/readme

������̣�

* ��ǰĿ¼����build.sh����ɱ���

### API�汾
���ڣ�2015-08-04

���ƣ�fsopt_traderapi

������������ȨAPI  

���ӣ�[http://www.sfit.com.cn/5_2_DocumentDown.htm](http://www.sfit.com.cn/5_2_DocumentDown.htm)

˵����ctpapi�ļ����µ���Windows��32λ�汾�������ļ���x64_linux�е���Linux��64λ�汾
