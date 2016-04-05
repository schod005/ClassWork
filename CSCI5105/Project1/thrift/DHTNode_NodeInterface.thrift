enum Flags
{
  LOG = 1
}

struct UpdateDHTInfo
{
  1: i64 ID,
  2: i16 port,
  3: string ipAddress
}

struct LogInfo
{
  1: list<i64> nodesVisited,
  2: i64 fileLocation
}

struct WriteFile
{
  1: binary file,
  2: i64 filesize,
  3: string filename
}

struct ReadFile
{
  1: bool error,
  2: string errorMessage,
  3: binary file,
  4: i64 filesize,
  5: string filename,
  6: LogInfo log
}

struct myInfo
{
  1: i64 ID,
  2: i64 minKey,
  3: i64 maxKey,
  4: i64 predecessor,
  5: i64 successor,
  6: i64 numFiles,
  7: list<string> files,
  8: map<i64, UpdateDHTInfo> fingerTable
}

service DHTNode_NodeInterface
{
  LogInfo Write(1:WriteFile fileInfo, 2:i64 flags),
  ReadFile Read(1:string filename, 2:i64 flags),
  void UpdateDHT(1:list<UpdateDHTInfo> NodesList),
	myInfo getInfo()
}
