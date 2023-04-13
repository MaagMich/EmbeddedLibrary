#ifndef H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_HEADER_START
#define H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_HEADER_START

#include <stdexcept>

#include "Protocol.h"
#include "InputBuffer.h"


namespace message_protocol
{

class Protocol_Header_Start : public Protocol
{
public:
	inline Protocol_Header_Start(
		const std::string header_start,
		receive_callback receive_callback,
		std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>()
	);

	virtual void translateInput() = 0;

	virtual std::string translateMessage(const std::shared_ptr<Message> message) = 0;

protected:
	inline auto getHeaderStart() const
		{ return this->header_start_; };

	inline virtual std::shared_ptr<Message> createMessage(const std::string message_string) override
		{ return std::make_shared<Message>(message_string); };

private:
	std::string header_start_;

};



inline Protocol_Header_Start::Protocol_Header_Start(
	const std::string header_start, 
	receive_callback receive_callback, 
	std::unique_ptr<InputBuffer> input_buffer
)
	: Protocol(receive_callback, std::move(input_buffer)),
	header_start_(header_start)
{
	if (this->getHeaderStart().size() == 0)
	{
		throw std::invalid_argument("Missing Header Start-Sequence.");
	}
}

/*
inline bool Protocol_Header_Start::findMessageStart()
{
	bool result = false;
	const auto pos_start = this->input_buffer_->findString(this->getHeaderStart());


	if (pos_start == 0)
	{
		result = true;
	}
	else if (pos_start != std::string::npos)
	{
		this->input_buffer_->remove(pos_start - 1);

		result = true;
	}

	return result;
}
*/
}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_HEADER_START
