#define PACKET_LIMIT_MARKER 0x7E
#define PACKET_ESCAPE_MARKER 0x7D
#define PACKET_MIN_SIZE 3

enum serial_packet_type 
{
  ERROR_PACKET = 0,
  DATA_PACKET = 1  
};

class serial_packet
{
  public:
   
    static void encode_data(char *databuffer, unsigned char datalength, char *packetbuffer, unsigned char *packetlength);

    static int decode_packet(char *packetbuffer, unsigned char packetlength, char *databuffer, unsigned char *datalength);
};

