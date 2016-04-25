/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MR_ComputeNodeInterface_H
#define MR_ComputeNodeInterface_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "MR_ComputeNodeInterface_types.h"



#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class MR_ComputeNodeInterfaceIf {
 public:
  virtual ~MR_ComputeNodeInterfaceIf() {}
  virtual void Sort(const std::string& filename, const int64_t offset, const int64_t size) = 0;
  virtual void Merge(const std::vector<std::string> & sorted_inter_files, const int64_t task_number) = 0;
  virtual void wakeup() = 0;
  virtual void pingable() = 0;
  virtual void outputStats() = 0;
};

class MR_ComputeNodeInterfaceIfFactory {
 public:
  typedef MR_ComputeNodeInterfaceIf Handler;

  virtual ~MR_ComputeNodeInterfaceIfFactory() {}

  virtual MR_ComputeNodeInterfaceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(MR_ComputeNodeInterfaceIf* /* handler */) = 0;
};

class MR_ComputeNodeInterfaceIfSingletonFactory : virtual public MR_ComputeNodeInterfaceIfFactory {
 public:
  MR_ComputeNodeInterfaceIfSingletonFactory(const boost::shared_ptr<MR_ComputeNodeInterfaceIf>& iface) : iface_(iface) {}
  virtual ~MR_ComputeNodeInterfaceIfSingletonFactory() {}

  virtual MR_ComputeNodeInterfaceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(MR_ComputeNodeInterfaceIf* /* handler */) {}

 protected:
  boost::shared_ptr<MR_ComputeNodeInterfaceIf> iface_;
};

class MR_ComputeNodeInterfaceNull : virtual public MR_ComputeNodeInterfaceIf {
 public:
  virtual ~MR_ComputeNodeInterfaceNull() {}
  void Sort(const std::string& /* filename */, const int64_t /* offset */, const int64_t /* size */) {
    return;
  }
  void Merge(const std::vector<std::string> & /* sorted_inter_files */, const int64_t /* task_number */) {
    return;
  }
  void wakeup() {
    return;
  }
  void pingable() {
    return;
  }
  void outputStats() {
    return;
  }
};

typedef struct _MR_ComputeNodeInterface_Sort_args__isset {
  _MR_ComputeNodeInterface_Sort_args__isset() : filename(false), offset(false), size(false) {}
  bool filename :1;
  bool offset :1;
  bool size :1;
} _MR_ComputeNodeInterface_Sort_args__isset;

class MR_ComputeNodeInterface_Sort_args {
 public:

  MR_ComputeNodeInterface_Sort_args(const MR_ComputeNodeInterface_Sort_args&);
  MR_ComputeNodeInterface_Sort_args& operator=(const MR_ComputeNodeInterface_Sort_args&);
  MR_ComputeNodeInterface_Sort_args() : filename(), offset(0), size(0) {
  }

  virtual ~MR_ComputeNodeInterface_Sort_args() throw();
  std::string filename;
  int64_t offset;
  int64_t size;

  _MR_ComputeNodeInterface_Sort_args__isset __isset;

  void __set_filename(const std::string& val);

  void __set_offset(const int64_t val);

  void __set_size(const int64_t val);

  bool operator == (const MR_ComputeNodeInterface_Sort_args & rhs) const
  {
    if (!(filename == rhs.filename))
      return false;
    if (!(offset == rhs.offset))
      return false;
    if (!(size == rhs.size))
      return false;
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_Sort_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_Sort_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_Sort_pargs {
 public:


  virtual ~MR_ComputeNodeInterface_Sort_pargs() throw();
  const std::string* filename;
  const int64_t* offset;
  const int64_t* size;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _MR_ComputeNodeInterface_Merge_args__isset {
  _MR_ComputeNodeInterface_Merge_args__isset() : sorted_inter_files(false), task_number(false) {}
  bool sorted_inter_files :1;
  bool task_number :1;
} _MR_ComputeNodeInterface_Merge_args__isset;

class MR_ComputeNodeInterface_Merge_args {
 public:

  MR_ComputeNodeInterface_Merge_args(const MR_ComputeNodeInterface_Merge_args&);
  MR_ComputeNodeInterface_Merge_args& operator=(const MR_ComputeNodeInterface_Merge_args&);
  MR_ComputeNodeInterface_Merge_args() : task_number(0) {
  }

  virtual ~MR_ComputeNodeInterface_Merge_args() throw();
  std::vector<std::string>  sorted_inter_files;
  int64_t task_number;

  _MR_ComputeNodeInterface_Merge_args__isset __isset;

  void __set_sorted_inter_files(const std::vector<std::string> & val);

  void __set_task_number(const int64_t val);

  bool operator == (const MR_ComputeNodeInterface_Merge_args & rhs) const
  {
    if (!(sorted_inter_files == rhs.sorted_inter_files))
      return false;
    if (!(task_number == rhs.task_number))
      return false;
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_Merge_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_Merge_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_Merge_pargs {
 public:


  virtual ~MR_ComputeNodeInterface_Merge_pargs() throw();
  const std::vector<std::string> * sorted_inter_files;
  const int64_t* task_number;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_wakeup_args {
 public:

  MR_ComputeNodeInterface_wakeup_args(const MR_ComputeNodeInterface_wakeup_args&);
  MR_ComputeNodeInterface_wakeup_args& operator=(const MR_ComputeNodeInterface_wakeup_args&);
  MR_ComputeNodeInterface_wakeup_args() {
  }

  virtual ~MR_ComputeNodeInterface_wakeup_args() throw();

  bool operator == (const MR_ComputeNodeInterface_wakeup_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_wakeup_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_wakeup_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_wakeup_pargs {
 public:


  virtual ~MR_ComputeNodeInterface_wakeup_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_wakeup_result {
 public:

  MR_ComputeNodeInterface_wakeup_result(const MR_ComputeNodeInterface_wakeup_result&);
  MR_ComputeNodeInterface_wakeup_result& operator=(const MR_ComputeNodeInterface_wakeup_result&);
  MR_ComputeNodeInterface_wakeup_result() {
  }

  virtual ~MR_ComputeNodeInterface_wakeup_result() throw();

  bool operator == (const MR_ComputeNodeInterface_wakeup_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_wakeup_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_wakeup_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_wakeup_presult {
 public:


  virtual ~MR_ComputeNodeInterface_wakeup_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class MR_ComputeNodeInterface_pingable_args {
 public:

  MR_ComputeNodeInterface_pingable_args(const MR_ComputeNodeInterface_pingable_args&);
  MR_ComputeNodeInterface_pingable_args& operator=(const MR_ComputeNodeInterface_pingable_args&);
  MR_ComputeNodeInterface_pingable_args() {
  }

  virtual ~MR_ComputeNodeInterface_pingable_args() throw();

  bool operator == (const MR_ComputeNodeInterface_pingable_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_pingable_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_pingable_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_pingable_pargs {
 public:


  virtual ~MR_ComputeNodeInterface_pingable_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_pingable_result {
 public:

  MR_ComputeNodeInterface_pingable_result(const MR_ComputeNodeInterface_pingable_result&);
  MR_ComputeNodeInterface_pingable_result& operator=(const MR_ComputeNodeInterface_pingable_result&);
  MR_ComputeNodeInterface_pingable_result() {
  }

  virtual ~MR_ComputeNodeInterface_pingable_result() throw();

  bool operator == (const MR_ComputeNodeInterface_pingable_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_pingable_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_pingable_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_pingable_presult {
 public:


  virtual ~MR_ComputeNodeInterface_pingable_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class MR_ComputeNodeInterface_outputStats_args {
 public:

  MR_ComputeNodeInterface_outputStats_args(const MR_ComputeNodeInterface_outputStats_args&);
  MR_ComputeNodeInterface_outputStats_args& operator=(const MR_ComputeNodeInterface_outputStats_args&);
  MR_ComputeNodeInterface_outputStats_args() {
  }

  virtual ~MR_ComputeNodeInterface_outputStats_args() throw();

  bool operator == (const MR_ComputeNodeInterface_outputStats_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_outputStats_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_outputStats_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_outputStats_pargs {
 public:


  virtual ~MR_ComputeNodeInterface_outputStats_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_outputStats_result {
 public:

  MR_ComputeNodeInterface_outputStats_result(const MR_ComputeNodeInterface_outputStats_result&);
  MR_ComputeNodeInterface_outputStats_result& operator=(const MR_ComputeNodeInterface_outputStats_result&);
  MR_ComputeNodeInterface_outputStats_result() {
  }

  virtual ~MR_ComputeNodeInterface_outputStats_result() throw();

  bool operator == (const MR_ComputeNodeInterface_outputStats_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MR_ComputeNodeInterface_outputStats_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MR_ComputeNodeInterface_outputStats_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class MR_ComputeNodeInterface_outputStats_presult {
 public:


  virtual ~MR_ComputeNodeInterface_outputStats_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class MR_ComputeNodeInterfaceClient : virtual public MR_ComputeNodeInterfaceIf {
 public:
  MR_ComputeNodeInterfaceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MR_ComputeNodeInterfaceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void Sort(const std::string& filename, const int64_t offset, const int64_t size);
  void send_Sort(const std::string& filename, const int64_t offset, const int64_t size);
  void Merge(const std::vector<std::string> & sorted_inter_files, const int64_t task_number);
  void send_Merge(const std::vector<std::string> & sorted_inter_files, const int64_t task_number);
  void wakeup();
  void send_wakeup();
  void recv_wakeup();
  void pingable();
  void send_pingable();
  void recv_pingable();
  void outputStats();
  void send_outputStats();
  void recv_outputStats();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class MR_ComputeNodeInterfaceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<MR_ComputeNodeInterfaceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (MR_ComputeNodeInterfaceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_Sort(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Merge(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_wakeup(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_pingable(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_outputStats(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  MR_ComputeNodeInterfaceProcessor(boost::shared_ptr<MR_ComputeNodeInterfaceIf> iface) :
    iface_(iface) {
    processMap_["Sort"] = &MR_ComputeNodeInterfaceProcessor::process_Sort;
    processMap_["Merge"] = &MR_ComputeNodeInterfaceProcessor::process_Merge;
    processMap_["wakeup"] = &MR_ComputeNodeInterfaceProcessor::process_wakeup;
    processMap_["pingable"] = &MR_ComputeNodeInterfaceProcessor::process_pingable;
    processMap_["outputStats"] = &MR_ComputeNodeInterfaceProcessor::process_outputStats;
  }

  virtual ~MR_ComputeNodeInterfaceProcessor() {}
};

class MR_ComputeNodeInterfaceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  MR_ComputeNodeInterfaceProcessorFactory(const ::boost::shared_ptr< MR_ComputeNodeInterfaceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< MR_ComputeNodeInterfaceIfFactory > handlerFactory_;
};

class MR_ComputeNodeInterfaceMultiface : virtual public MR_ComputeNodeInterfaceIf {
 public:
  MR_ComputeNodeInterfaceMultiface(std::vector<boost::shared_ptr<MR_ComputeNodeInterfaceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~MR_ComputeNodeInterfaceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<MR_ComputeNodeInterfaceIf> > ifaces_;
  MR_ComputeNodeInterfaceMultiface() {}
  void add(boost::shared_ptr<MR_ComputeNodeInterfaceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void Sort(const std::string& filename, const int64_t offset, const int64_t size) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Sort(filename, offset, size);
    }
    ifaces_[i]->Sort(filename, offset, size);
  }

  void Merge(const std::vector<std::string> & sorted_inter_files, const int64_t task_number) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Merge(sorted_inter_files, task_number);
    }
    ifaces_[i]->Merge(sorted_inter_files, task_number);
  }

  void wakeup() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->wakeup();
    }
    ifaces_[i]->wakeup();
  }

  void pingable() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->pingable();
    }
    ifaces_[i]->pingable();
  }

  void outputStats() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->outputStats();
    }
    ifaces_[i]->outputStats();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class MR_ComputeNodeInterfaceConcurrentClient : virtual public MR_ComputeNodeInterfaceIf {
 public:
  MR_ComputeNodeInterfaceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MR_ComputeNodeInterfaceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void Sort(const std::string& filename, const int64_t offset, const int64_t size);
  void send_Sort(const std::string& filename, const int64_t offset, const int64_t size);
  void Merge(const std::vector<std::string> & sorted_inter_files, const int64_t task_number);
  void send_Merge(const std::vector<std::string> & sorted_inter_files, const int64_t task_number);
  void wakeup();
  int32_t send_wakeup();
  void recv_wakeup(const int32_t seqid);
  void pingable();
  int32_t send_pingable();
  void recv_pingable(const int32_t seqid);
  void outputStats();
  int32_t send_outputStats();
  void recv_outputStats(const int32_t seqid);
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