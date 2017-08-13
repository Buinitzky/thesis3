#!/bin/bash

cd ..
pwd=$(pwd)

ln -s /usr/bin/perf /bin

mkdir /var/config-cluster
mkdir /var/config-cluster/init.d

echo -e config-cluster\\t18001/udp>>/etc/services

ln -s "$pwd/program" /var/config-cluster/program
ln -s "$pwd/program/service/init.d" /var/config-cluster/init.d/init.d

cd /var/config-cluster

pwd=$(pwd)


chmod -R a+x "$pwd/program"

ln -s "$pwd/init.d/init.d" /etc/init.d/config-cluster
chmod a+x /etc/init.d/config-cluster
update-rc.d config-cluster defaults 
