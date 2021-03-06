/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef DHTNode_NodeInterface_TYPES_H
#define DHTNode_NodeInterface_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




struct Flags {
  enum type {
    LOG = 1
  };
};

extern const std::map<int, const char*> _Flags_VALUES_TO_NAMES;

class UpdateDHTInfo;

class LogInfo;

class WriteFile;

class ReadFile;

class myInfo;

typedef struct _UpdateDHTInfo__isset {
  _UpdateDHTInfo__isset() : ID(false), port(false), ipAddress(false) {}
  bool ID :1;
  bool port :1;
  bool ipAddress :1;
} _UpdateDHTInfo__isset;

class UpdateDHTInfo {
 public:

  UpdateDHTInfo(const UpdateDHTInfo&);
  UpdateDHTInfo& operator=(const UpdateDHTInfo&);
  UpdateDHTInfo() : ID(0), port(0), ipAddress() {
  }

  virtual ~UpdateDHTInfo() throw();
  int64_t ID;
  int16_t port;
  std::string ipAddress;

  _UpdateDHTInfo__isset __isset;

  void __set_ID(const int64_t val);

  void __set_port(const int16_t val);

  void __set_ipAddress(const std::string& val);

  bool operator == (const UpdateDHTInfo & rhs) const
  {
    if (!(ID == rhs.ID))
      return false;
    if (!(port == rhs.port))
      return false;
    if (!(ipAddress == rhs.ipAddress))
      return false;
    return true;
  }
  bool operator != (const UpdateDHTInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const UpdateDHTInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(UpdateDHTInfo &a, UpdateDHTInfo &b);

inline std::ostream& operator<<(std::ostream& out, const UpdateDHTInfo& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _LogInfo__isset {
  _LogInfo__isset() : nodesVisited(false), fileLocation(false) {}
  bool nodesVisited :1;
  bool fileLocation :1;
} _LogInfo__isset;

class LogInfo {
 public:

  LogInfo(const LogInfo&);
  LogInfo& operator=(const LogInfo&);
  LogInfo() : fileLocation(0) {
  }

  virtual ~LogInfo() throw();
  std::vector<int64_t>  nodesVisited;
  int64_t fileLocation;

  _LogInfo__isset __isset;

  void __set_nodesVisited(const std::vector<int64_t> & val);

  void __set_fileLocation(const int64_t val);

  bool operator == (const LogInfo & rhs) const
  {
    if (!(nodesVisited == rhs.nodesVisited))
      return false;
    if (!(fileLocation == rhs.fileLocation))
      return false;
    return true;
  }
  bool operator != (const LogInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LogInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(LogInfo &a, LogInfo &b);

inline std::ostream& operator<<(std::ostream& out, const LogInfo& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _WriteFile__isset {
  _WriteFile__isset() : file(false), filesize(false), filename(false) {}
  bool file :1;
  bool filesize :1;
  bool filename :1;
} _WriteFile__isset;

class WriteFile {
 public:

  WriteFile(const WriteFile&);
  WriteFile& operator=(const WriteFile&);
  WriteFile() : file(), filesize(0), filename() {
  }

  virtual ~WriteFile() throw();
  std::string file;
  int64_t filesize;
  std::string filename;

  _WriteFile__isset __isset;

  void __set_file(const std::string& val);

  void __set_filesize(const int64_t val);

  void __set_filename(const std::string& val);

  bool operator == (const WriteFile & rhs) const
  {
    if (!(file == rhs.file))
      return false;
    if (!(filesize == rhs.filesize))
      return false;
    if (!(filename == rhs.filename))
      return false;
    return true;
  }
  bool operator != (const WriteFile &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const WriteFile & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(WriteFile &a, WriteFile &b);

inline std::ostream& operator<<(std::ostream& out, const WriteFile& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _ReadFile__isset {
  _ReadFile__isset() : error(false), errorMessage(false), file(false), filesize(false), filename(false), log(false) {}
  bool error :1;
  bool errorMessage :1;
  bool file :1;
  bool filesize :1;
  bool filename :1;
  bool log :1;
} _ReadFile__isset;

class ReadFile {
 public:

  ReadFile(const ReadFile&);
  ReadFile& operator=(const ReadFile&);
  ReadFile() : error(0), errorMessage(), file(), filesize(0), filename() {
  }

  virtual ~ReadFile() throw();
  bool error;
  std::string errorMessage;
  std::string file;
  int64_t filesize;
  std::string filename;
  LogInfo log;

  _ReadFile__isset __isset;

  void __set_error(const bool val);

  void __set_errorMessage(const std::string& val);

  void __set_file(const std::string& val);

  void __set_filesize(const int64_t val);

  void __set_filename(const std::string& val);

  void __set_log(const LogInfo& val);

  bool operator == (const ReadFile & rhs) const
  {
    if (!(error == rhs.error))
      return false;
    if (!(errorMessage == rhs.errorMessage))
      return false;
    if (!(file == rhs.file))
      return false;
    if (!(filesize == rhs.filesize))
      return false;
    if (!(filename == rhs.filename))
      return false;
    if (!(log == rhs.log))
      return false;
    return true;
  }
  bool operator != (const ReadFile &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ReadFile & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ReadFile &a, ReadFile &b);

inline std::ostream& operator<<(std::ostream& out, const ReadFile& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _myInfo__isset {
  _myInfo__isset() : ID(false), minKey(false), maxKey(false), predecessor(false), successor(false), numFiles(false), files(false), fingerTable(false) {}
  bool ID :1;
  bool minKey :1;
  bool maxKey :1;
  bool predecessor :1;
  bool successor :1;
  bool numFiles :1;
  bool files :1;
  bool fingerTable :1;
} _myInfo__isset;

class myInfo {
 public:

  myInfo(const myInfo&);
  myInfo& operator=(const myInfo&);
  myInfo() : ID(0), minKey(0), maxKey(0), predecessor(0), successor(0), numFiles(0) {
  }

  virtual ~myInfo() throw();
  int64_t ID;
  int64_t minKey;
  int64_t maxKey;
  int64_t predecessor;
  int64_t successor;
  int64_t numFiles;
  std::vector<std::string>  files;
  std::map<int64_t, UpdateDHTInfo>  fingerTable;

  _myInfo__isset __isset;

  void __set_ID(const int64_t val);

  void __set_minKey(const int64_t val);

  void __set_maxKey(const int64_t val);

  void __set_predecessor(const int64_t val);

  void __set_successor(const int64_t val);

  void __set_numFiles(const int64_t val);

  void __set_files(const std::vector<std::string> & val);

  void __set_fingerTable(const std::map<int64_t, UpdateDHTInfo> & val);

  bool operator == (const myInfo & rhs) const
  {
    if (!(ID == rhs.ID))
      return false;
    if (!(minKey == rhs.minKey))
      return false;
    if (!(maxKey == rhs.maxKey))
      return false;
    if (!(predecessor == rhs.predecessor))
      return false;
    if (!(successor == rhs.successor))
      return false;
    if (!(numFiles == rhs.numFiles))
      return false;
    if (!(files == rhs.files))
      return false;
    if (!(fingerTable == rhs.fingerTable))
      return false;
    return true;
  }
  bool operator != (const myInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const myInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(myInfo &a, myInfo &b);

inline std::ostream& operator<<(std::ostream& out, const myInfo& obj)
{
  obj.printTo(out);
  return out;
}



#endif
