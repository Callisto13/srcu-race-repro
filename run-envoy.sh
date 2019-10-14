#!/bin/bash

if ! [ "$(command -v envoy)" ] ; then
  echo "Envoy not installed: https://www.getenvoy.io/platforms/envoy/ubuntu/"
fi

while : ; do
  for k in {0..100} ; do
    # each instance needs to run on a different port, this is a lazy way to do that
    sed -i -e "15s/.*/        port_value: 610$k/g" /vagrant_data/envoy/envoy.yaml
    sed -i -e "6s/.*/      port_value: 150$k/g" /vagrant_data/envoy/envoy.yaml
    envoy -c /vagrant_data/envoy/envoy.yaml --base-id "0$k" &>/dev/null &
  done
  killall envoy
done
