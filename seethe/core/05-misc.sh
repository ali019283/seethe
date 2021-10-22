# vim: set ts=4 sw=4 et:

install -m0664 -o root -g utmp /dev/null /run/utmp
halt -B  # for wtmp

if [ -z "$VIRTUALIZATION" ]; then
    echo "Initializing random seed..."
    cp /var/lib/random-seed /dev/urandom >/dev/null 2>&1 || true
fi

echo "Setting up loopback interface..."
ip link set up dev lo

[ -r /etc/hostname ] && read -r HOSTNAME < /etc/hostname
if [ -n "$HOSTNAME" ]; then
    echo "Setting up hostname to '${HOSTNAME}'..."
    printf "%s" "$HOSTNAME" > /proc/sys/kernel/hostname
else
    echo "Didn't setup a hostname!"
fi

if [ -n "$TIMEZONE" ]; then
    echo "Setting up timezone to '${TIMEZONE}'..."
    ln -sf "/usr/share/zoneinfo/$TIMEZONE" /etc/localtime
fi
