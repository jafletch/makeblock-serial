#include "serial_packet.h"

void serial_packet::encode_data(char *databuffer, unsigned char datalength, char *packetbuffer, unsigned char *packetlength)
{
  packetbuffer[0] = PACKET_LIMIT_MARKER;
  packetbuffer[1] = DATA_PACKET;

  *packetlength = 2;
  for(int i = 0; i < datalength; i++)
  {
    if (databuffer[i] == PACKET_LIMIT_MARKER || databuffer[i] == PACKET_ESCAPE_MARKER)
    {
      packetbuffer[*packetlength++] = PACKET_ESCAPE_MARKER;
      packetbuffer[*packetlength++] = databuffer[i];
    }
    else
    {
      packetbuffer[*packetlength++] = databuffer[i];
    }
  }
  packetbuffer[*packetlength++] = PACKET_LIMIT_MARKER;
}

int serial_packet::decode_packet(char *packetbuffer, unsigned char packetlength, char *databuffer, unsigned char *datalength)
{
  if(packetlength < PACKET_MIN_SIZE)
  {
    char errMsg[] = "Packet too small";
    *datalength = (unsigned char)sizeof(errMsg);
    for(int i = 0; i < *datalength; i++)
    {
      databuffer[i] = errMsg[i];
    }
    return 1;
  }
}
