all:
	g++ Main.cpp PacketCapture.cpp PacketDecoder.cpp -o miniwireshark

clean:
	rm -f miniwireshark