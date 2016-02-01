linux.conf.au 2016 Tutorial


1. make sure this file has the path $HOME/picotcp/README_lca2016.txt


2. follow the instructions at https://github.com/tass-belgium/picotcp/wiki/Running-picoTCP-on-Linux but use 32-bit packages

2.1 On a 32-bit distro, you are all set with the standard instructions

2.2 On a 64-bit Debian-based distro, do

    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo apt-get install libvdeplug2-dev:i386 libpcap0.8-dev:i386

2.3 ensure that `make` and `make test` work fine


3. follow the instructions at https://github.com/tass-belgium/picotcp/wiki/Examples

3.1 make sure that the first, ping-based example works for you
