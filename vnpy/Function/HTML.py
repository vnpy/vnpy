# encoding: utf-8

import socket
import threading
import time
import os
import datetime
import pandas as pd
import pandas.io.sql as pandas_sql
import MySQLdb
import logging
import urllib2
import StringIO
import gzip
import cookielib
import random

import urllib2

class BrowserBase(object): 

    def __init__(self):
        socket.setdefaulttimeout(20)

    @staticmethod
    def speak(name,content):
        print '[%s]%s' % (name,content)

    def openurl(self,url):
        """
        打开网页
        """
        cookie_support= urllib2.HTTPCookieProcessor(cookielib.CookieJar())
        self.opener = urllib2.build_opener(cookie_support,urllib2.HTTPHandler)
        urllib2.install_opener(self.opener)
        user_agents = [
                    'Mozilla/5.0 (Windows; U; Windows NT 5.1; it; rv:1.8.1.11) Gecko/20071127 Firefox/2.0.0.11',
                    'Opera/9.25 (Windows NT 5.1; U; en)',
                    'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)',
                    'Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.5 (like Gecko) (Kubuntu)',
                    'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.0.12) Gecko/20070731 Ubuntu/dapper-security Firefox/1.5.0.12',
                    'Lynx/2.8.5rel.1 libwww-FM/2.14 SSL-MM/1.4.1 GNUTLS/1.2.9',
                    "Mozilla/5.0 (X11; Linux i686) AppleWebKit/535.7 (KHTML, like Gecko) Ubuntu/11.04 Chromium/16.0.912.77 Chrome/16.0.912.77 Safari/535.7",
                    "Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:10.0) Gecko/20100101 Firefox/10.0 ",

                    ] 
       
        agent = random.choice(user_agents)
        self.opener.addheaders = [("User-agent",agent),("Accept","*/*"),('Referer','http://www.google.com')]
        try:
            res = self.opener.open(url)
            return res.read()
        except Exception,e:
            # BrowserBase.speak(str(e),url)
            # return self.openurl(url)
            return ""
        return ''
'''
HTML 信息类
'''
class HTML():
    @staticmethod
    def browser_html(url):
        splider = BrowserBase()
        return splider.openurl(url)

    @staticmethod
    def get_html(url,data={}):
        try:
            # print "try request"
            request = urllib2.Request(url)
            request.add_header('User-Agent','Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.155 Safari/537.36')
            request.add_header('Connection',"keep-alive")
            request.add_header('Cache-Control',"")
            request.add_header("Accept-Encoding","gzip, deflate, sdch")
            request.add_header("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8")
            request.add_header("Upgrade-Insecure-Requests","1")
            for key in data.keys():
                request.add_header(key,data[key])
            # print "try response"
            response = urllib2.urlopen(request,timeout=10)
            html = ""
            if response.info().get('Content-Encoding') == 'gzip':
                # print "try gzip read"
                buf = StringIO.StringIO(response.read())
                f = gzip.GzipFile(fileobj=buf)
                html = f.read()
            else:
                # print "try read"
                opener = urllib2.build_opener()
                html = opener.open(request).read()
            # print "finish"
            try:
                html = html.decode('utf-8')
            except Exception,ex:
                try:
                    html = html.decode('gbk')
                except Exception,ex:
                    pass
            return html
        except Exception,ex:
            print "Error in Spider.get_html"
            print ex
            if "IncompletedRead" in ex:
                print "try again spider"
                return HTML.get_html(url)
            if "HTTP Error 500" in str(ex):
                print "try again spider"
                return HTML.get_html(url)
            if "timed out" in ex:
                print "try again spider"
                return HTML.get_html(url)