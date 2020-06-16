#!/bin/bash

set -e

export NAME=satoshi
export BRANCH=dev

git -C gitian-builder checkout .
git -C ColossusCoinXT pull

echo '' >> gitian-builder/target-bin/grab-packages.sh
echo 'update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 7 ' >> gitian-builder/target-bin/grab-packages.sh
echo 'update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 7' >> gitian-builder/target-bin/grab-packages.sh
echo 'update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 8 ' >> gitian-builder/target-bin/grab-packages.sh
echo 'update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 8 ' >> gitian-builder/target-bin/grab-packages.sh

python3 gitian-build.py --docker -b -c -o l --detach-sign $NAME $BRANCH
