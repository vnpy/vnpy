# -*- encoding: utf-8 -*-

import sys
import pickle

import selenium

from selenium.webdriver.support.ui import WebDriverWait         # available since 2.4.0
#   from selenium.common.exceptions import TimeoutException
#   from selenium.webdriver.support import expected_conditions as EC    # available since 2.26.0

def wait_condition_01(driver):
    return driver.find_element_by_id('dateList_container_pageid')

def extract_table(driver, stocklist):
    tag_table= driver.find_element_by_class_name("tablestyle")
    tabletext= tag_table.text
    stocklist.extend(tabletext.split('\n')[1:])

driver= selenium.webdriver.Firefox()
driver.get("http://www.sse.com.cn/assortment/stock/list/name/")

stocklist= []
extract_table(driver=driver, stocklist=stocklist)

tag_meta= driver.find_element_by_id("staticPagination")
attr_total= int(tag_meta.get_attribute("total"))
attr_pageCount= int(tag_meta.get_attribute("pageCount"))

# 逐页提取内容
for pagenr in range(2, attr_pageCount+1):
    id_input= 'dateList_container_pageid' if pagenr > 2 else 'xsgf_pageid'
    id_button= 'dateList_container_togo' if pagenr > 2 else 'xsgf_togo'

    tag_input= driver.find_element_by_id(id_input)
    tag_button= driver.find_element_by_id(id_button)
    tag_input.send_keys(str(pagenr))
    tag_button.click()
    WebDriverWait(driver, 10).until(wait_condition_01)

    extract_table(driver=driver, stocklist=stocklist)

# 向主调进程发送结果
data= {
    '个股总数': attr_total,
    '个股列表': stocklist,
}

driver.quit()
pdata= pickle.dumps(data, protocol=2)
sys.stdout.write( pdata + b'\n' )