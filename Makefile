all:
	g++ Main.cpp PacketCapture.cpp PacketDecoder.cpp EthernetPacket.cpp -o miniwireshark

clean:
	rm -f miniwireshark