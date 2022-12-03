#!/bin/sh
set -e

Help()
{
   # Display Help
   echo "Building the quick-os project."
   echo
   echo "Options:"
   echo "-g                 print the GPL license notification."
   echo "-h, -help          print this help."
   echo "-v                 print software version and exit."
   echo "-j                 the number of jobs"
}

GPL()
{
    echo -e "Copyright (C) 2022 sekvanto.\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law."
}

if [ -z "$VERSION" ] # version not set, executing config
then
    . ./config.sh
fi

# make options
JOBS=1

while getopts "gh(help)vj:" option; do
   case $option in
    g) # gpl license notification
        GPL
        exit;;
    h|help) # display Help
        Help
        exit;;
    v) # version
        echo "QuickOS $NAME v$VERSION.$PATCHLEVEL.$SUBLEVEL"
        exit;;
    j) # jobs
        JOBS=$OPTARG;;
   esac
done

#####################################################################

echo "Build configuration:"
echo -e "Jobs: $JOBS\n"

#####################################################################

. ./headers.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE -j$JOBS install)
done
