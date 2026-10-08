all:
	g++ Main.cpp PacketCapture.cpp -o miniwireshark

clean:
	rm -f miniwireshark