"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""


"""
Just a thin wrapper around a socket.
It allows us to keep some other info along with it.
"""


import socket
import threading
import logging

from ibapi.common import * # @UnusedWildImport
from ibapi.errors import * # @UnusedWildImport


#TODO: support SSL !!

logger = logging.getLogger(__name__)


class Connection:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.socket = None
        self.wrapper = None
        self.lock = threading.Lock()


    def connect(self):
        try:
            self.socket = socket.socket()
        #TODO: list the exceptions you want to catch
        except socket.error:
            if self.wrapper:
                self.wrapper.error(NO_VALID_ID, FAIL_CREATE_SOCK.code(), FAIL_CREATE_SOCK.msg())

        try:
            self.socket.connect((self.host, self.port))
        except socket.error:
            if self.wrapper:
                self.wrapper.error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg())

        self.socket.settimeout(1)   #non-blocking


    def disconnect(self):
        self.lock.acquire()
        try:
            logger.debug("disconnecting")
            self.socket.close()
            self.socket = None
            logger.debug("disconnected")
            if self.wrapper:
                self.wrapper.connectionClosed()
        finally:
            self.lock.release()


    def isConnected(self):
        #TODO: also handle when socket gets interrupted/error
        return self.socket is not None


    def sendMsg(self, msg):

        logger.debug("acquiring lock")
        self.lock.acquire()
        logger.debug("acquired lock")
        if not self.isConnected():
            logger.debug("sendMsg attempted while not connected, releasing lock")
            self.lock.release()
            return 0
        try:
            nSent = self.socket.send(msg)
        except socket.error:
            logger.debug("exception from sendMsg %s", sys.exc_info())
            raise
        finally:
            logger.debug("releasing lock")
            self.lock.release()
            logger.debug("release lock")

        logger.debug("sendMsg: sent: %d", nSent)

        return nSent


    def recvMsg(self):
        if not self.isConnected():
            logger.debug("recvMsg attempted while not connected, releasing lock")
            return b""
        try:
            buf = self._recvAllMsg()
        except socket.error:
            logger.debug("exception from recvMsg %s", sys.exc_info())
            buf = b""
        else:
            pass

        return buf


    def _recvAllMsg(self):
        cont = True
        allbuf = b""

        while cont and self.socket is not None:
            buf = self.socket.recv(4096)
            allbuf += buf
            logger.debug("len %d raw:%s|", len(buf), buf)

            if len(buf) < 4096:
                cont = False

        return allbuf

