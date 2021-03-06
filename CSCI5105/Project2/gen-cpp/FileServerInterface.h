/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef FileServerInterface_H
#define FileServerInterface_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "FileServerInterface_types.h"



#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class FileServerInterfaceIf {
 public:
  virtual ~FileServerInterfaceIf() {}
  virtual void Write(const WriteFile& fileInfo, const int64_t flags) = 0;
  virtual void Read(ReadFile& _return, const std::string& filename, const int64_t flags) = 0;
  virtual void getAllServers(std::vector<ServerInfo> & _return) = 0;
  virtual int64_t Register(const ServerInfo& myInfo) = 0;
  virtual int64_t getVersion(const std::string& filename) = 0;
  virtual void updateFile(WriteFile& _return, const WriteFile& appendFile, const int64_t version, const int64_t append_flag) = 0;
  virtual void getFile(ReadFile& _return, const std::string& filename) = 0;
  virtual void listFiles(std::vector<FileInfo> & _return) = 0;
};

class FileServerInterfaceIfFactory {
 public:
  typedef FileServerInterfaceIf Handler;

  virtual ~FileServerInterfaceIfFactory() {}

  virtual FileServerInterfaceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(FileServerInterfaceIf* /* handler */) = 0;
};

class FileServerInterfaceIfSingletonFactory : virtual public FileServerInterfaceIfFactory {
 public:
  FileServerInterfaceIfSingletonFactory(const boost::shared_ptr<FileServerInterfaceIf>& iface) : iface_(iface) {}
  virtual ~FileServerInterfaceIfSingletonFactory() {}

  virtual FileServerInterfaceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(FileServerInterfaceIf* /* handler */) {}

 protected:
  boost::shared_ptr<FileServerInterfaceIf> iface_;
};

class FileServerInterfaceNull : virtual public FileServerInterfaceIf {
 public:
  virtual ~FileServerInterfaceNull() {}
  void Write(const WriteFile& /* fileInfo */, const int64_t /* flags */) {
    return;
  }
  void Read(ReadFile& /* _return */, const std::string& /* filename */, const int64_t /* flags */) {
    return;
  }
  void getAllServers(std::vector<ServerInfo> & /* _return */) {
    return;
  }
  int64_t Register(const ServerInfo& /* myInfo */) {
    int64_t _return = 0;
    return _return;
  }
  int64_t getVersion(const std::string& /* filename */) {
    int64_t _return = 0;
    return _return;
  }
  void updateFile(WriteFile& /* _return */, const WriteFile& /* appendFile */, const int64_t /* version */, const int64_t /* append_flag */) {
    return;
  }
  void getFile(ReadFile& /* _return */, const std::string& /* filename */) {
    return;
  }
  void listFiles(std::vector<FileInfo> & /* _return */) {
    return;
  }
};

typedef struct _FileServerInterface_Write_args__isset {
  _FileServerInterface_Write_args__isset() : fileInfo(false), flags(false) {}
  bool fileInfo :1;
  bool flags :1;
} _FileServerInterface_Write_args__isset;

class FileServerInterface_Write_args {
 public:

  FileServerInterface_Write_args(const FileServerInterface_Write_args&);
  FileServerInterface_Write_args& operator=(const FileServerInterface_Write_args&);
  FileServerInterface_Write_args() : flags(0) {
  }

  virtual ~FileServerInterface_Write_args() throw();
  WriteFile fileInfo;
  int64_t flags;

  _FileServerInterface_Write_args__isset __isset;

  void __set_fileInfo(const WriteFile& val);

  void __set_flags(const int64_t val);

  bool operator == (const FileServerInterface_Write_args & rhs) const
  {
    if (!(fileInfo == rhs.fileInfo))
      return false;
    if (!(flags == rhs.flags))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_Write_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_Write_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_Write_pargs {
 public:


  virtual ~FileServerInterface_Write_pargs() throw();
  const WriteFile* fileInfo;
  const int64_t* flags;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_Write_result {
 public:

  FileServerInterface_Write_result(const FileServerInterface_Write_result&);
  FileServerInterface_Write_result& operator=(const FileServerInterface_Write_result&);
  FileServerInterface_Write_result() {
  }

  virtual ~FileServerInterface_Write_result() throw();

  bool operator == (const FileServerInterface_Write_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const FileServerInterface_Write_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_Write_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_Write_presult {
 public:


  virtual ~FileServerInterface_Write_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileServerInterface_Read_args__isset {
  _FileServerInterface_Read_args__isset() : filename(false), flags(false) {}
  bool filename :1;
  bool flags :1;
} _FileServerInterface_Read_args__isset;

class FileServerInterface_Read_args {
 public:

  FileServerInterface_Read_args(const FileServerInterface_Read_args&);
  FileServerInterface_Read_args& operator=(const FileServerInterface_Read_args&);
  FileServerInterface_Read_args() : filename(), flags(0) {
  }

  virtual ~FileServerInterface_Read_args() throw();
  std::string filename;
  int64_t flags;

  _FileServerInterface_Read_args__isset __isset;

  void __set_filename(const std::string& val);

  void __set_flags(const int64_t val);

  bool operator == (const FileServerInterface_Read_args & rhs) const
  {
    if (!(filename == rhs.filename))
      return false;
    if (!(flags == rhs.flags))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_Read_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_Read_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_Read_pargs {
 public:


  virtual ~FileServerInterface_Read_pargs() throw();
  const std::string* filename;
  const int64_t* flags;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_Read_result__isset {
  _FileServerInterface_Read_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_Read_result__isset;

class FileServerInterface_Read_result {
 public:

  FileServerInterface_Read_result(const FileServerInterface_Read_result&);
  FileServerInterface_Read_result& operator=(const FileServerInterface_Read_result&);
  FileServerInterface_Read_result() {
  }

  virtual ~FileServerInterface_Read_result() throw();
  ReadFile success;

  _FileServerInterface_Read_result__isset __isset;

  void __set_success(const ReadFile& val);

  bool operator == (const FileServerInterface_Read_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_Read_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_Read_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_Read_presult__isset {
  _FileServerInterface_Read_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_Read_presult__isset;

class FileServerInterface_Read_presult {
 public:


  virtual ~FileServerInterface_Read_presult() throw();
  ReadFile* success;

  _FileServerInterface_Read_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class FileServerInterface_getAllServers_args {
 public:

  FileServerInterface_getAllServers_args(const FileServerInterface_getAllServers_args&);
  FileServerInterface_getAllServers_args& operator=(const FileServerInterface_getAllServers_args&);
  FileServerInterface_getAllServers_args() {
  }

  virtual ~FileServerInterface_getAllServers_args() throw();

  bool operator == (const FileServerInterface_getAllServers_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const FileServerInterface_getAllServers_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_getAllServers_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_getAllServers_pargs {
 public:


  virtual ~FileServerInterface_getAllServers_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_getAllServers_result__isset {
  _FileServerInterface_getAllServers_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_getAllServers_result__isset;

class FileServerInterface_getAllServers_result {
 public:

  FileServerInterface_getAllServers_result(const FileServerInterface_getAllServers_result&);
  FileServerInterface_getAllServers_result& operator=(const FileServerInterface_getAllServers_result&);
  FileServerInterface_getAllServers_result() {
  }

  virtual ~FileServerInterface_getAllServers_result() throw();
  std::vector<ServerInfo>  success;

  _FileServerInterface_getAllServers_result__isset __isset;

  void __set_success(const std::vector<ServerInfo> & val);

  bool operator == (const FileServerInterface_getAllServers_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_getAllServers_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_getAllServers_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_getAllServers_presult__isset {
  _FileServerInterface_getAllServers_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_getAllServers_presult__isset;

class FileServerInterface_getAllServers_presult {
 public:


  virtual ~FileServerInterface_getAllServers_presult() throw();
  std::vector<ServerInfo> * success;

  _FileServerInterface_getAllServers_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileServerInterface_Register_args__isset {
  _FileServerInterface_Register_args__isset() : myInfo(false) {}
  bool myInfo :1;
} _FileServerInterface_Register_args__isset;

class FileServerInterface_Register_args {
 public:

  FileServerInterface_Register_args(const FileServerInterface_Register_args&);
  FileServerInterface_Register_args& operator=(const FileServerInterface_Register_args&);
  FileServerInterface_Register_args() {
  }

  virtual ~FileServerInterface_Register_args() throw();
  ServerInfo myInfo;

  _FileServerInterface_Register_args__isset __isset;

  void __set_myInfo(const ServerInfo& val);

  bool operator == (const FileServerInterface_Register_args & rhs) const
  {
    if (!(myInfo == rhs.myInfo))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_Register_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_Register_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_Register_pargs {
 public:


  virtual ~FileServerInterface_Register_pargs() throw();
  const ServerInfo* myInfo;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_Register_result__isset {
  _FileServerInterface_Register_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_Register_result__isset;

class FileServerInterface_Register_result {
 public:

  FileServerInterface_Register_result(const FileServerInterface_Register_result&);
  FileServerInterface_Register_result& operator=(const FileServerInterface_Register_result&);
  FileServerInterface_Register_result() : success(0) {
  }

  virtual ~FileServerInterface_Register_result() throw();
  int64_t success;

  _FileServerInterface_Register_result__isset __isset;

  void __set_success(const int64_t val);

  bool operator == (const FileServerInterface_Register_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_Register_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_Register_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_Register_presult__isset {
  _FileServerInterface_Register_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_Register_presult__isset;

class FileServerInterface_Register_presult {
 public:


  virtual ~FileServerInterface_Register_presult() throw();
  int64_t* success;

  _FileServerInterface_Register_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileServerInterface_getVersion_args__isset {
  _FileServerInterface_getVersion_args__isset() : filename(false) {}
  bool filename :1;
} _FileServerInterface_getVersion_args__isset;

class FileServerInterface_getVersion_args {
 public:

  FileServerInterface_getVersion_args(const FileServerInterface_getVersion_args&);
  FileServerInterface_getVersion_args& operator=(const FileServerInterface_getVersion_args&);
  FileServerInterface_getVersion_args() : filename() {
  }

  virtual ~FileServerInterface_getVersion_args() throw();
  std::string filename;

  _FileServerInterface_getVersion_args__isset __isset;

  void __set_filename(const std::string& val);

  bool operator == (const FileServerInterface_getVersion_args & rhs) const
  {
    if (!(filename == rhs.filename))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_getVersion_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_getVersion_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_getVersion_pargs {
 public:


  virtual ~FileServerInterface_getVersion_pargs() throw();
  const std::string* filename;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_getVersion_result__isset {
  _FileServerInterface_getVersion_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_getVersion_result__isset;

class FileServerInterface_getVersion_result {
 public:

  FileServerInterface_getVersion_result(const FileServerInterface_getVersion_result&);
  FileServerInterface_getVersion_result& operator=(const FileServerInterface_getVersion_result&);
  FileServerInterface_getVersion_result() : success(0) {
  }

  virtual ~FileServerInterface_getVersion_result() throw();
  int64_t success;

  _FileServerInterface_getVersion_result__isset __isset;

  void __set_success(const int64_t val);

  bool operator == (const FileServerInterface_getVersion_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_getVersion_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_getVersion_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_getVersion_presult__isset {
  _FileServerInterface_getVersion_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_getVersion_presult__isset;

class FileServerInterface_getVersion_presult {
 public:


  virtual ~FileServerInterface_getVersion_presult() throw();
  int64_t* success;

  _FileServerInterface_getVersion_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileServerInterface_updateFile_args__isset {
  _FileServerInterface_updateFile_args__isset() : appendFile(false), version(false), append_flag(false) {}
  bool appendFile :1;
  bool version :1;
  bool append_flag :1;
} _FileServerInterface_updateFile_args__isset;

class FileServerInterface_updateFile_args {
 public:

  FileServerInterface_updateFile_args(const FileServerInterface_updateFile_args&);
  FileServerInterface_updateFile_args& operator=(const FileServerInterface_updateFile_args&);
  FileServerInterface_updateFile_args() : version(0), append_flag(0) {
  }

  virtual ~FileServerInterface_updateFile_args() throw();
  WriteFile appendFile;
  int64_t version;
  int64_t append_flag;

  _FileServerInterface_updateFile_args__isset __isset;

  void __set_appendFile(const WriteFile& val);

  void __set_version(const int64_t val);

  void __set_append_flag(const int64_t val);

  bool operator == (const FileServerInterface_updateFile_args & rhs) const
  {
    if (!(appendFile == rhs.appendFile))
      return false;
    if (!(version == rhs.version))
      return false;
    if (!(append_flag == rhs.append_flag))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_updateFile_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_updateFile_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_updateFile_pargs {
 public:


  virtual ~FileServerInterface_updateFile_pargs() throw();
  const WriteFile* appendFile;
  const int64_t* version;
  const int64_t* append_flag;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_updateFile_result__isset {
  _FileServerInterface_updateFile_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_updateFile_result__isset;

class FileServerInterface_updateFile_result {
 public:

  FileServerInterface_updateFile_result(const FileServerInterface_updateFile_result&);
  FileServerInterface_updateFile_result& operator=(const FileServerInterface_updateFile_result&);
  FileServerInterface_updateFile_result() {
  }

  virtual ~FileServerInterface_updateFile_result() throw();
  WriteFile success;

  _FileServerInterface_updateFile_result__isset __isset;

  void __set_success(const WriteFile& val);

  bool operator == (const FileServerInterface_updateFile_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_updateFile_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_updateFile_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_updateFile_presult__isset {
  _FileServerInterface_updateFile_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_updateFile_presult__isset;

class FileServerInterface_updateFile_presult {
 public:


  virtual ~FileServerInterface_updateFile_presult() throw();
  WriteFile* success;

  _FileServerInterface_updateFile_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _FileServerInterface_getFile_args__isset {
  _FileServerInterface_getFile_args__isset() : filename(false) {}
  bool filename :1;
} _FileServerInterface_getFile_args__isset;

class FileServerInterface_getFile_args {
 public:

  FileServerInterface_getFile_args(const FileServerInterface_getFile_args&);
  FileServerInterface_getFile_args& operator=(const FileServerInterface_getFile_args&);
  FileServerInterface_getFile_args() : filename() {
  }

  virtual ~FileServerInterface_getFile_args() throw();
  std::string filename;

  _FileServerInterface_getFile_args__isset __isset;

  void __set_filename(const std::string& val);

  bool operator == (const FileServerInterface_getFile_args & rhs) const
  {
    if (!(filename == rhs.filename))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_getFile_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_getFile_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_getFile_pargs {
 public:


  virtual ~FileServerInterface_getFile_pargs() throw();
  const std::string* filename;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_getFile_result__isset {
  _FileServerInterface_getFile_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_getFile_result__isset;

class FileServerInterface_getFile_result {
 public:

  FileServerInterface_getFile_result(const FileServerInterface_getFile_result&);
  FileServerInterface_getFile_result& operator=(const FileServerInterface_getFile_result&);
  FileServerInterface_getFile_result() {
  }

  virtual ~FileServerInterface_getFile_result() throw();
  ReadFile success;

  _FileServerInterface_getFile_result__isset __isset;

  void __set_success(const ReadFile& val);

  bool operator == (const FileServerInterface_getFile_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_getFile_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_getFile_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_getFile_presult__isset {
  _FileServerInterface_getFile_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_getFile_presult__isset;

class FileServerInterface_getFile_presult {
 public:


  virtual ~FileServerInterface_getFile_presult() throw();
  ReadFile* success;

  _FileServerInterface_getFile_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class FileServerInterface_listFiles_args {
 public:

  FileServerInterface_listFiles_args(const FileServerInterface_listFiles_args&);
  FileServerInterface_listFiles_args& operator=(const FileServerInterface_listFiles_args&);
  FileServerInterface_listFiles_args() {
  }

  virtual ~FileServerInterface_listFiles_args() throw();

  bool operator == (const FileServerInterface_listFiles_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const FileServerInterface_listFiles_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_listFiles_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class FileServerInterface_listFiles_pargs {
 public:


  virtual ~FileServerInterface_listFiles_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_listFiles_result__isset {
  _FileServerInterface_listFiles_result__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_listFiles_result__isset;

class FileServerInterface_listFiles_result {
 public:

  FileServerInterface_listFiles_result(const FileServerInterface_listFiles_result&);
  FileServerInterface_listFiles_result& operator=(const FileServerInterface_listFiles_result&);
  FileServerInterface_listFiles_result() {
  }

  virtual ~FileServerInterface_listFiles_result() throw();
  std::vector<FileInfo>  success;

  _FileServerInterface_listFiles_result__isset __isset;

  void __set_success(const std::vector<FileInfo> & val);

  bool operator == (const FileServerInterface_listFiles_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const FileServerInterface_listFiles_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileServerInterface_listFiles_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _FileServerInterface_listFiles_presult__isset {
  _FileServerInterface_listFiles_presult__isset() : success(false) {}
  bool success :1;
} _FileServerInterface_listFiles_presult__isset;

class FileServerInterface_listFiles_presult {
 public:


  virtual ~FileServerInterface_listFiles_presult() throw();
  std::vector<FileInfo> * success;

  _FileServerInterface_listFiles_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class FileServerInterfaceClient : virtual public FileServerInterfaceIf {
 public:
  FileServerInterfaceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  FileServerInterfaceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void Write(const WriteFile& fileInfo, const int64_t flags);
  void send_Write(const WriteFile& fileInfo, const int64_t flags);
  void recv_Write();
  void Read(ReadFile& _return, const std::string& filename, const int64_t flags);
  void send_Read(const std::string& filename, const int64_t flags);
  void recv_Read(ReadFile& _return);
  void getAllServers(std::vector<ServerInfo> & _return);
  void send_getAllServers();
  void recv_getAllServers(std::vector<ServerInfo> & _return);
  int64_t Register(const ServerInfo& myInfo);
  void send_Register(const ServerInfo& myInfo);
  int64_t recv_Register();
  int64_t getVersion(const std::string& filename);
  void send_getVersion(const std::string& filename);
  int64_t recv_getVersion();
  void updateFile(WriteFile& _return, const WriteFile& appendFile, const int64_t version, const int64_t append_flag);
  void send_updateFile(const WriteFile& appendFile, const int64_t version, const int64_t append_flag);
  void recv_updateFile(WriteFile& _return);
  void getFile(ReadFile& _return, const std::string& filename);
  void send_getFile(const std::string& filename);
  void recv_getFile(ReadFile& _return);
  void listFiles(std::vector<FileInfo> & _return);
  void send_listFiles();
  void recv_listFiles(std::vector<FileInfo> & _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class FileServerInterfaceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<FileServerInterfaceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (FileServerInterfaceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_Write(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Read(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getAllServers(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Register(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getVersion(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_updateFile(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_getFile(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_listFiles(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  FileServerInterfaceProcessor(boost::shared_ptr<FileServerInterfaceIf> iface) :
    iface_(iface) {
    processMap_["Write"] = &FileServerInterfaceProcessor::process_Write;
    processMap_["Read"] = &FileServerInterfaceProcessor::process_Read;
    processMap_["getAllServers"] = &FileServerInterfaceProcessor::process_getAllServers;
    processMap_["Register"] = &FileServerInterfaceProcessor::process_Register;
    processMap_["getVersion"] = &FileServerInterfaceProcessor::process_getVersion;
    processMap_["updateFile"] = &FileServerInterfaceProcessor::process_updateFile;
    processMap_["getFile"] = &FileServerInterfaceProcessor::process_getFile;
    processMap_["listFiles"] = &FileServerInterfaceProcessor::process_listFiles;
  }

  virtual ~FileServerInterfaceProcessor() {}
};

class FileServerInterfaceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  FileServerInterfaceProcessorFactory(const ::boost::shared_ptr< FileServerInterfaceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< FileServerInterfaceIfFactory > handlerFactory_;
};

class FileServerInterfaceMultiface : virtual public FileServerInterfaceIf {
 public:
  FileServerInterfaceMultiface(std::vector<boost::shared_ptr<FileServerInterfaceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~FileServerInterfaceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<FileServerInterfaceIf> > ifaces_;
  FileServerInterfaceMultiface() {}
  void add(boost::shared_ptr<FileServerInterfaceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void Write(const WriteFile& fileInfo, const int64_t flags) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Write(fileInfo, flags);
    }
    ifaces_[i]->Write(fileInfo, flags);
  }

  void Read(ReadFile& _return, const std::string& filename, const int64_t flags) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Read(_return, filename, flags);
    }
    ifaces_[i]->Read(_return, filename, flags);
    return;
  }

  void getAllServers(std::vector<ServerInfo> & _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getAllServers(_return);
    }
    ifaces_[i]->getAllServers(_return);
    return;
  }

  int64_t Register(const ServerInfo& myInfo) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Register(myInfo);
    }
    return ifaces_[i]->Register(myInfo);
  }

  int64_t getVersion(const std::string& filename) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getVersion(filename);
    }
    return ifaces_[i]->getVersion(filename);
  }

  void updateFile(WriteFile& _return, const WriteFile& appendFile, const int64_t version, const int64_t append_flag) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->updateFile(_return, appendFile, version, append_flag);
    }
    ifaces_[i]->updateFile(_return, appendFile, version, append_flag);
    return;
  }

  void getFile(ReadFile& _return, const std::string& filename) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getFile(_return, filename);
    }
    ifaces_[i]->getFile(_return, filename);
    return;
  }

  void listFiles(std::vector<FileInfo> & _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->listFiles(_return);
    }
    ifaces_[i]->listFiles(_return);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class FileServerInterfaceConcurrentClient : virtual public FileServerInterfaceIf {
 public:
  FileServerInterfaceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  FileServerInterfaceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void Write(const WriteFile& fileInfo, const int64_t flags);
  int32_t send_Write(const WriteFile& fileInfo, const int64_t flags);
  void recv_Write(const int32_t seqid);
  void Read(ReadFile& _return, const std::string& filename, const int64_t flags);
  int32_t send_Read(const std::string& filename, const int64_t flags);
  void recv_Read(ReadFile& _return, const int32_t seqid);
  void getAllServers(std::vector<ServerInfo> & _return);
  int32_t send_getAllServers();
  void recv_getAllServers(std::vector<ServerInfo> & _return, const int32_t seqid);
  int64_t Register(const ServerInfo& myInfo);
  int32_t send_Register(const ServerInfo& myInfo);
  int64_t recv_Register(const int32_t seqid);
  int64_t getVersion(const std::string& filename);
  int32_t send_getVersion(const std::string& filename);
  int64_t recv_getVersion(const int32_t seqid);
  void updateFile(WriteFile& _return, const WriteFile& appendFile, const int64_t version, const int64_t append_flag);
  int32_t send_updateFile(const WriteFile& appendFile, const int64_t version, const int64_t append_flag);
  void recv_updateFile(WriteFile& _return, const int32_t seqid);
  void getFile(ReadFile& _return, const std::string& filename);
  int32_t send_getFile(const std::string& filename);
  void recv_getFile(ReadFile& _return, const int32_t seqid);
  void listFiles(std::vector<FileInfo> & _return);
  int32_t send_listFiles();
  void recv_listFiles(std::vector<FileInfo> & _return, const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif



#endif
