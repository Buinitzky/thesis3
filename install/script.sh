#!/bin/bash

APT_PACKAGES="libdw1\
				libelf-dev\
				libunwind8\
				linux-tools-generic"	
				
apt-get install -y $APT_PACKAGES

cd ..
pwd=$(pwd)

ln -s /usr/bin/perf /bin
echo -e cpp_java$'\t'15557/tcp>>/etc/services
echo -e conf-clustdgam$'\t'18001/udp>>/etc/services
echo -e conf-cluststrm$'\t'18002/tcp>>/etc/services

mkdir /var/configcluster
mkdir /var/configcluster/init.d
mkdir /var/tesis-doctoral
mkdir /var/tesis-doctoral/init.d

ln -s "$pwd/ProyectoFinal" /var/configcluster/fuente
ln -s "$pwd/install/service/init.d" /var/configcluster/init.d/init.d

ln -s "$pwd/ProyectoFinal" /var/tesis-doctoral/Ejecutables
cp "$pwd/install/servers.d" /etc/init.d

cd /var/configcluster
pwd=$(pwd)
chmod -R a+x "$pwd/fuente"
ln -s "$pwd/init.d/init.d" /etc/init.d/configcluster
chmod a+x /etc/init.d/configcluster
update-rc.d configcluster defaults 5 6
chmod a+x /etc/init.d/servers.d
update-rc.d servers.d defaults 5 6

cd /var/tesis-doctoral
pwd=$(pwd)

chmod -R a+x "$pwd/Ejecutables" 
