service MR_ComputeNodeInterface {
	oneway void Sort(1:string filename, 2:i64 offset, 3:i64 size),
  	oneway void Merge(1:list<string> sorted_inter_files, 2:i64 task_number),
	void wakeup(),
	void pingable(),
  void outputStats(),
}
