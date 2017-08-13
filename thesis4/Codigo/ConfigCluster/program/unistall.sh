#!/bin/bash


cd /var/config-cluster/init.d
rm init.d
cd ..
rm program
rmdir init.d
cd ..
rmdir config-cluster
cd /etc/init.d
rm config-cluster

echo "config-cluster eliminado." 
