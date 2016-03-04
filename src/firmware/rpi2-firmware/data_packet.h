#define DATA_PACKET_OVERHEAD_SIZE 4
#define DATA_PACKET_MIN_SIZE 3

class data_packet
{
  public:
    static data_packet parse(char *databuffer, unsigned char data_length);

    data_packet(unsigned char dataLength)
    {
      if (dataLength > 0)
      {
        data_length = dataLength;
        data = new char[data_length];
      }
      else
      {
        data_length = 0;
        data = nullptr;
      }
    }
  
    char action;
  
    char device;

    char port;

    char slot;

    char *data;

    char data_length;
};

