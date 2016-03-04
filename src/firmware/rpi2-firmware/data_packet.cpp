#include "data_packet.h"

data_packet data_packet::parse(char *databuffer, unsigned char datalength)
{
  data_packet dp(datalength - DATA_PACKET_OVERHEAD_SIZE);

  dp.action = databuffer[0];
  dp.device = databuffer[1];
  dp.port = databuffer[2];
  if (datalength > 3)
  {
    dp.slot = databuffer[3];
  }

  if (datalength > 4)
  {
    for(int i = 0; i < datalength; i++)
    {
      dp.data[i] = databuffer[i + 4];
    }
  }
}

