# Mini-Wireshark

A simple packet sniffer im writing to freshen up up my skills in c++ and remind myself network protocols.
The project uses Linux raw sockets to capture Ethernet frames and decode the protocol layers inside of them. 
The goal is to gradually build something similar to Wireshark.

# Current Featuers
- Captures packets using Linux AF_PACKET raw sockets.

- Supports capturing on a specified network interface.

- Uses a separate thread for packet capturing.

- Decodes Ethernet headers (source MAC, destination MAC, EtherType).

- Decodes IPv4 headers (source/destination IP, TTL, protocol, packet length, etc.).

- Stores captured packets as objects containing their decoded protocol layers.