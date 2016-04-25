service MR_ServerInterface {
  i64 Register(1:string ipAddress, 2:i16 port),
  void sendHeartbeat(1:string ipAddress, 2:i16 port),
  bool sendFilename(1:string filename, 2:string ipAddress, 3:i16 port, 4:i64 offset, 5:i64 size),
  bool callback_merge(1:string filename, 2:string ipAddress, 3:i16 port, 4:i64 merge_task_number),
  string getSorted(1:string input_filename),
}
