These are some reproduction instructions and tools to recreate the [SRCU data race problem](https://lists.gt.net/linux/kernel/3124443) identified by Denis Krien
and detailed [here](https://queenofdowntime.com/blog/inotify-release-deadlock).

#### Contents:
- `Vagrantfile` for Ubuntu Xenial with volume mount to load all contents into the VM
- `inotify-test-c` binary and `inotify-test.c` code
- `inotify-test-rust` binary and `rust-test` Cargo package
- `run-envoy.sh` script and `envoy` config directory

#### Installation:

```sh
git clone https://github.com/Callisto13/srcu-race-repro.git && cd srcu-race-repro

# on your host
vagrant up

vagrant ssh

# in vagrant VM
uname -r

# bump the kernel to 4.15
sudo su -
mkdir kern-415 && cd kern-415

wget https://kernel.ubuntu.com/~kernel-ppa/mainline/v4.15/linux-headers-4.15.0-041500_4.15.0-041500.201802011154_all.deb
wget https://kernel.ubuntu.com/~kernel-ppa/mainline/v4.15/linux-headers-4.15.0-041500-generic_4.15.0-041500.201802011154_amd64.deb
wget https://kernel.ubuntu.com/~kernel-ppa/mainline/v4.15/linux-image-4.15.0-041500-generic_4.15.0-041500.201802011154_amd64.deb

dpkg -i *.deb

reboot

# wait up to 2 minutes
vagrant ssh

# in vagrant VM
uname -r # should return '4.15.0-041500-generic'

# install Envoy
# https://www.getenvoy.io/platforms/envoy/ubuntu/
envoy --version
```

#### Running:

```sh
vagrant ssh

cd /vagrant_data
sudo su -

# envoy
./run-envoy.sh

# rust program - run as many loops as you like/your machine can manage
touch target
while : ; do ./inotify-test-rust ; done &

# c program - run as many loops as you like/your machine can manage
touch target
while : ; do ./inotify-test-c target ; done &

# in another terminal pane
vagrant ssh
sudo su -

watch -n 0.1 "ps -eLo pid,comm,state,wchan | grep -E 'inotify|envoy|kworker'"

# enjoy
```

_source code for both rust and c programs are included for editing_
