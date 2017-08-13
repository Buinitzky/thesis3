#! /bin/sh
### BEGIN INIT INFO
# Provides:          server-tesis
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Example initscript
# Description:       This file should be used to construct scripts to be
#                    placed in /etc/init.d.
### END INIT INFO

PWD=`pwd`
# Function that starts the daemon/service
#
do_start()
{
	cd /var/config-cluster/program
	./configcluster
	cd $PWD
}
#
# Function that stops the daemon/service
#
do_stop()
{
	pid=$(pidof configcluster)
	kill "$pid"
	cd $PWD
}

case "$1" in
  start)
	do_start
	;;
  stop)
	do_stop
	;;
  restart)
	do_stop
	do_start
	;;
  *)
	#echo "Usage: $SCRIPTNAME {start|stop|restart}" >&2
	echo "Usage: $SCRIPTNAME {start|stop|restart}" >&2
	exit 3
	;;
esac

:
