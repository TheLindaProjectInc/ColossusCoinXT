#!/bin/bash

set -e

export NAME=satoshi
export BRANCH=dev

if [[ ! -e 'gitian-builder/inputs/MacOSX10.11.sdk.tar.gz' ]]
then
    echo 'Downloading MacOS sdk...'
    mkdir -p gitian-builder/inputs
    wget -N -P gitian-builder/inputs https://github.com/phracker/MacOSX-SDKs/releases/download/10.13/MacOSX10.11.sdk.tar.xz
    mv gitian-builder/inputs/MacOSX10.11.sdk.tar.xz gitian-builder/inputs/MacOSX10.11.sdk.tar.gz
else
    echo 'MacOS SDK is up to date.'
fi

git -C gitian-builder checkout .
python3 gitian-build.py --docker -b -c -o m --detach-sign $NAME $BRANCH
