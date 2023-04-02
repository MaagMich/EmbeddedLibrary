#ifndef H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL
#define H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL

#include <string>
#include <list>
#include <memory>
#include <functional>

#include "Message.h"


namespace message_protocol
{

using receive_callback = std::function<void(std::shared_ptr<Message>)>;

class Protocol
{
public:
	inline Protocol(receive_callback receive_callback)
		: receive_callback_(receive_callback)
		{};

	inline void pushInput(const std::list<char> input, const bool translate = true);
	virtual void translateInput() = 0;

	virtual std::string translateMessage(const std::shared_ptr<Message> message) = 0;

private:
	std::string header_start_;
	std::string header_end_;
	std::list<char> input_buffer_;
	receive_callback receive_callback_;

};



inline void Protocol::pushInput(const std::list<char> input, const bool translate)
{
	this->input_buffer_.insert(this->input_buffer_.end(), input.begin(), input.end());

	if (translate)
	{
		this->translateInput();
	}
}




}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL
