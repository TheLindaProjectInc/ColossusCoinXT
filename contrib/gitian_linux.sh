#!/bin/bash

set -e

export NAME=satoshi
export BRANCH=dev
python3 gitian-build.py --docker -b -c -o l --detach-sign $NAME $BRANCH
