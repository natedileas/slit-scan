# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
all:
	g++ -g slit_scan.cpp -o slit_scan `pkg-config --cflags --libs opencv`