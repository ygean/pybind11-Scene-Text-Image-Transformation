apt-get update
apt-get install wget

# wget -O boost_1_67_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.67.0/boost_1_67_0.tar.gz/download
# tar xzvf boost_1_67_0.tar.gz
cd boost_1_67_0/

apt-get install build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev

./bootstrap.sh --prefix=/usr/local
./b2 --with=all install 
sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/local.conf'

ldconfig