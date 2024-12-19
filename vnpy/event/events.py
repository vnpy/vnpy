# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/vnpy/event
# @File     : events.py
# @Time     : 2024/12/19 22:49
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description: Define the event type string for all apps, including main engine/trader etc.


# ================================= apps =================================
# data recorder
EVENT_RECORDER_LOG = "eRecorderLog"  # tell the LogEngine to log the message

EVENT_RECORDER_UPDATE = "eRecorderUpdate"  # signal to indicate the recorder has been updated
EVENT_RECORDER_RECORD = "eRecorderRecord"  # signal to trigger the recorder to record data
EVENT_RECORDER_EXCEPTION = "eRecorderException"  # signal to indicate the recorder has an exception

# factor maker. fixme: annotations are not specified
EVENT_BAR_FACTOR = "eBarFactor."
EVENT_FACTOR = "eFactor."

EVENT_FACTORMAKER_LOG = "eFactorMakerLog"   # tell the LogEngine to log the message
EVENT_FACTORMAKER = "eFactorMaker"