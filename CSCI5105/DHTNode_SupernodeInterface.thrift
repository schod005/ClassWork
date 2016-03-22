struct IPPort
{
  1: i16 port,
  2: string ipAddress
}

struct NodeInfo
{
  1: i64 ID,
  2: IPPort network_info
}

service DHTNode_SupernodeInterface
{
  list<NodeInfo> Join(1:IPPort ipport),
  void PostJoin(1:IPPort ipport),
  NodeInfo getNode(),
  list<NodeInfo> getNodeList()
}
