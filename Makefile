all:
	g++ -std=c++17 -pthread Main.cpp PacketCapture.cpp PacketDecoder.cpp EthernetLayer.cpp -o miniwireshark

clean:
	rm -f miniwireshark