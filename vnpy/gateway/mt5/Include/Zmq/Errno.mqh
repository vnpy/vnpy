//+------------------------------------------------------------------+
//| Module: Errno.mqh                                                |
//| This file is part of the mql-zmq project:                        |
//|     https://github.com/dingmaotu/mql-zmq                         |
//|                                                                  |
//| Copyright 2016-2017 Li Ding <dingmaotu@hotmail.com>              |
//|                                                                  |
//| Licensed under the Apache License, Version 2.0 (the "License");  |
//| you may not use this file except in compliance with the License. |
//| You may obtain a copy of the License at                          |
//|                                                                  |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                                                  |
//| Unless required by applicable law or agreed to in writing,       |
//| software distributed under the License is distributed on an      |
//| "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,     |
//| either express or implied.                                       |
//| See the License for the specific language governing permissions  |
//| and limitations under the License.                               |
//+------------------------------------------------------------------+

// Following error codes come from Microsoft CRT header errno.h

// Error codes
#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EINTR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define EDEADLK         36
#define ENAMETOOLONG    38
#define ENOLCK          39
#define ENOSYS          40
#define ENOTEMPTY       41

// Error codes used in the Secure CRT functions
#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80

// Support EDEADLOCK for compatibility with older Microsoft C versions
#define EDEADLOCK       EDEADLK

// POSIX Supplement
#define EALREADY        103
#define EBADMSG         104
#define ECANCELED       105
#define EDESTADDRREQ    109
#define EIDRM           111
#define EISCONN         113
#define ELOOP           114
#define ENODATA         120
#define ENOLINK         121
#define ENOMSG          122
#define ENOPROTOOPT     123
#define ENOSR           124
#define ENOSTR          125
#define ENOTRECOVERABLE 127
#define EOPNOTSUPP      130
#define EOTHER          131
#define EOVERFLOW       132
#define EOWNERDEAD      133
#define EPROTO          134
#define EPROTOTYPE      136
#define ETIME           137
#define ETXTBSY         139
#define EWOULDBLOCK     140

// Following error codes come from zmq.h
// 0MQ errors
#define ZMQ_HAUSNUMERO 156384712

#define ENOTSUP (ZMQ_HAUSNUMERO + 1)
#define EPROTONOSUPPORT (ZMQ_HAUSNUMERO + 2)
#define ENOBUFS (ZMQ_HAUSNUMERO + 3)
#define ENETDOWN (ZMQ_HAUSNUMERO + 4)
#define EADDRINUSE (ZMQ_HAUSNUMERO + 5)
#define EADDRNOTAVAIL (ZMQ_HAUSNUMERO + 6)
#define ECONNREFUSED (ZMQ_HAUSNUMERO + 7)
#define EINPROGRESS (ZMQ_HAUSNUMERO + 8)
#define ENOTSOCK (ZMQ_HAUSNUMERO + 9)
#define EMSGSIZE (ZMQ_HAUSNUMERO + 10)
#define EAFNOSUPPORT (ZMQ_HAUSNUMERO + 11)
#define ENETUNREACH (ZMQ_HAUSNUMERO + 12)
#define ECONNABORTED (ZMQ_HAUSNUMERO + 13)
#define ECONNRESET (ZMQ_HAUSNUMERO + 14)
#define ENOTCONN (ZMQ_HAUSNUMERO + 15)
#define ETIMEDOUT (ZMQ_HAUSNUMERO + 16)
#define EHOSTUNREACH (ZMQ_HAUSNUMERO + 17)
#define ENETRESET (ZMQ_HAUSNUMERO + 18)

// Native 0MQ error codes
#define EFSM (ZMQ_HAUSNUMERO + 51)
#define ENOCOMPATPROTO (ZMQ_HAUSNUMERO + 52)
#define ETERM (ZMQ_HAUSNUMERO + 53)
#define EMTHREAD (ZMQ_HAUSNUMERO + 54)
//+------------------------------------------------------------------+
