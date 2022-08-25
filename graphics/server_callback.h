#pragma once
#include <string>

struct ServerCallback
{

	//
	// this data pointers are managed by who calls begin(), doit(), end(), finally.
	int			cmd_;
	std::string cmd_name_;
	size_t		data_size_;
	void*		data_;
	size_t      return_data_size_;
	void*		return_data_;


	ServerCallback(): cmd_(0), data_size_(0), data_(0), 
		return_data_size_(0), return_data_(0) 
	{}

	ServerCallback(const ServerCallback& c):
		cmd_(c.cmd_), data_size_(c.data_size_), data_(c.data_), 
		return_data_size_(c.return_data_size_), return_data_(c.return_data_) 
	{}

	~ServerCallback() {}

	virtual void sys_init() {}
	virtual void begin() {}
	virtual void doit() {}
	virtual void end() {}
};
