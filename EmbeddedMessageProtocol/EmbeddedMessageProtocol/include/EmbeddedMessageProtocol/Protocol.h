#ifndef H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL
#define H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL

#include <string>
#include <memory>
#include <functional>
#include <optional>

#include "InputBuffer.h"
#include "Message.h"


namespace message_protocol
{

using receive_callback = std::function<void(std::shared_ptr<Message>)>;

class Protocol
{
public:
	inline Protocol(
		receive_callback receive_callback,
		std::unique_ptr<InputBuffer> input_buffer
	)
		: receive_callback_(receive_callback),
		input_buffer_(std::move(input_buffer)),
		message_count_(0)
		{};

	inline void pushInput(const std::string input, const bool translate = true);
	virtual void translateInput() = 0;

	virtual std::string translateMessage(const std::shared_ptr<Message> message) = 0;

	inline auto getMessageCount() const
		{ return this->message_count_; };

protected:
	virtual std::shared_ptr<Message> createMessage(const std::string message_string) = 0;

	inline bool invokeReceive(std::shared_ptr<Message> message) const;

protected:
	std::unique_ptr<InputBuffer> input_buffer_;

private:
	receive_callback receive_callback_;
	size_t message_count_;

};



inline void Protocol::pushInput(const std::string input, const bool translate)
{
	this->input_buffer_->pushInput(input);

	if (translate)
	{
		this->translateInput();
	}
}


inline bool Protocol::invokeReceive(std::shared_ptr<Message> message) const
{
	bool result = false;


	if (this->receive_callback_ && message)
	{
		this->receive_callback_(message);

		result = true;
	}

	return result;
}

}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL
