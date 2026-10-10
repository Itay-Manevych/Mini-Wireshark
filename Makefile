all:
	g++ -std=c++17 -pthread Main.cpp PacketCapture.cpp PacketDecoder.cpp EthernetPacket.cpp -o miniwireshark

clean:
	rm -f miniwireshark