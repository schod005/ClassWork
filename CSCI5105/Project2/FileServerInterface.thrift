struct WriteFile
{
  1: binary file,
  2: string filename
}

struct ReadFile
{
  1: bool error,
  2: string errorMessage,
  3: binary file,
  4: string filename,
  5: i64 version
}

struct ServerInfo
{
  1: i16 port,
  2: string ipAddress
}

struct FileInfo
{
  1: string filename,
  2: i64 version
}

service FileServerInterface
{
  void Write(1:WriteFile fileInfo, 2:i64 flags),
  ReadFile Read(1:string filename, 2:i64 flags),
  list<ServerInfo> getAllServers(),
  i64 Register(1:ServerInfo myInfo),
  i64 getVersion(1:string filename),
  WriteFile updateFile(1:WriteFile appendFile, 2:i64 version, 3:i64 append_flag),
  ReadFile getFile(1:string filename),
  list<FileInfo> listFiles()
}
