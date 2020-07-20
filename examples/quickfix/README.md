quickfix-python-sample
======================

Sample python quickfix executor and client applications.

*Requirements: 
Install quickfix http://www.quickfixengine.org/download

TODO: add info on how to build quickfix in ubuntu

*Execution:
python executor.py executor.cfg (Executes new limit orders)
python client.py client.cfg (Interactive order placement)

1 - places order
2 - exits
d - pdb.set_trace() - to check what a mess inside a SWIG generated code

You can check what is going on in Logs folder by:
tail -f *

or using wireshark, as it has a good representation plugins for FIX



