#!/bin/bash

copy_log()
{
  if [[ -e 'gitian-builder/var/build.log' ]]
  then
    mv -f gitian-builder/var/build.log gitian-builder/var/build_$1.log
  fi

  if [[ -e 'gitian-builder/var/install.log' ]]
  then
    mv -f gitian-builder/var/install.log gitian-builder/var/install_$1.log
  fi
}

chmod +x gitian_win.sh
./gitian_win.sh
copy_log "win"

chmod +x gitian_mac.sh
./gitian_mac.sh
copy_log "mac"

chmod +x gitian_linux.sh
./gitian_linux.sh
copy_log "linux"
