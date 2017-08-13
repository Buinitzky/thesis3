#!/bin/bash

cd ..
pwd=$(pwd)

ln -s /usr/bin/perf /bin

echo -e cpp_java$'\t'15557/tcp>>/etc/services
echo -e conf-clustdgam$'\t'18001/udp>>/etc/services
echo -e conf-cluststrm$'\t'18002/tcp>>/etc/services

mkdir /var/configcluster
mkdir /var/configcluster/init.d

ln -s "$pwd/ConfigCluster" /var/configcluster/fuente
ln -s "$pwd/ConfigCluster/service/init.d" /var/configcluster/init.d/init.d

make
ln -s

cd /var/configcluster

pwd=$(pwd)


chmod -R a+x "$pwd/fuente"

ln -s "$pwd/init.d/init.d" /etc/init.d/configcluster
chmod a+x /etc/init.d/configcluster 5 6
update-rc.d configcluster defaults 


