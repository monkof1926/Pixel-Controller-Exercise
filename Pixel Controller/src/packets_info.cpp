#include <Arduino.h>
#include  "WiFi.h"
#include "AsyncUDP.h"
#include "main.cpp"

int receivingPort = 7000;
DatagramSocket receivingPort = new;
DatagramSocket(receivingPort);


byte[] bytes = new byte[255];
DatagramPacket packetToReceive = new DatagramPacket(bytes, bytes.length);

receivingSocket.receive(packetToReceive);


String message = new String(packetToReceive.getData());
System.out.println(message);

// create socket
int sendingPort = 7007;
DatagramSocket sendingSocket = new DatagramSocket();
// create packet
DatagramPacket packetToSend = new DatagramPacket("hello world".getBytes(), 0, 11, InetAddress.getByName("127.0.0.1"), sendingPort);

sendingSocket.send(packetToSend);
