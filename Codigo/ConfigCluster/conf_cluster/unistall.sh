#!/bin/bash


cd /var/configcluster/init.d
rm init.d
cd ..
rm fuente
rmdir init.d
cd ..
rmdir configcluster
cd /etc/init.d
rm configcluster

echo "configcluster eliminado." 
