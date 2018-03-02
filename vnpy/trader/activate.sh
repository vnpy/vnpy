#!/bin/bash

CONDA_HOME=~/anaconda3
source $CONDA_HOME/bin/activate /home/tensorflow/anaconda3/envs/py35

#BASE_PATH=$(cd `dirname $0`; pwd)
cd `dirname $0`
PROGRAM_NAME=./CTP.py

nohup python $PROGRAM_NAME &