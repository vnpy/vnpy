#!/bin/bash

CONDA_HOME=~/anaconda3
source $CONDA_HOME/bin/activate py2

#BASE_PATH=$(cd `dirname $0`; pwd)
cd `dirname $0`

python $1
  