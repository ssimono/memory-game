#! /bin/bash

#
# This script will package the program into a .deb file
#

name='memory-game'
tmp="/tmp/$name"
base_dir=$(dirname $0)/..

# Make sure no file is modified
cd $base_dir
if [ $(git status --porcelain | wc -l) != 0 ]; then
    echo 'Some files are modified or untracked. Calling script with a clean working directory is recommended'
    echo 'Proceed anyway? (yes/no): ' && read ans
    if [ $ans == no ]; then
        echo 'Packaging procedure aborted.'
        exit
    fi
fi
cd -

# Make sure the release binary exists
if [ ! -e $base_dir/$name ]; then
    echo 'Program memory-game not found. Make sure you first built it'
    exit
elif [ "$($base_dir/$name --version)" == 'debug build' ]; then
    echo 'The binary seems to be the debug build. Please do "make release"'
    exit
fi

# Create a temporary directory to build the package
if [ -e $tmp ]; then
    rm -r $tmp
fi

mkdir $tmp

# Create DEBIAN folder to store meta-information about the packge
mkdir $tmp/DEBIAN

# Write control file
echo "\
Package: $name
Version: 1.0
Section: base
Priority: optional
Architecture: all
Depends: libsdl-ttf2.0-0,libsdl1.2debian
Maintainer: Simon Alfassa <simon@sa-web.fr>
Description: A funny game to train your memory skills"\
>> $tmp/DEBIAN/control

# Fill with required files
install -D $base_dir/$name $tmp/usr/bin/$name
install -D $base_dir/data/$name.desktop $tmp/usr/share/applications/$name.desktop

cd $base_dir/share
for i in `find . -type f`
do
    install -D $i $tmp/usr/share/$name/$i --mode=644
done

# Build the debian package
dpkg-deb --build $tmp

echo 'To install your game:'
echo 'sudo dpkg -i /tmp/memory-game.deb'

# Remove temp directory
rm -r $tmp
