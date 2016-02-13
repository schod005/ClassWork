typedef enum 
{
  MSG_TYPE_GET,
  MSG_TYPE_GET_ERR,
  MSG_TYPE_GET_RESP,
  MSG_TYPE_GET_ACK,
  MSG_TYPE_FINISH
} msg_type_t;

#define BUF_SZ 256
struct msg_t {
  msg_type_t msg_type;      /* message type */
  int cur_seq;                   /* current seq number */
  int max_seq;                   /* max seq number */
  int payload_len;               /* length of payload */
  unsigned char payload[BUF_SZ]; /* buffer for data */
};
