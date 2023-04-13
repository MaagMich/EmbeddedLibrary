#ifndef H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_PLAIN
#define H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_PLAIN

#include "Protocol.h"
#include "InputBuffer.h"


namespace message_protocol
{

class Protocol_Plain : public Protocol
{
public:
	inline Protocol_Plain(
		receive_callback receive_callback,
		std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>()
	)
		: Protocol(receive_callback, std::move(input_buffer))
		{};

	virtual void translateInput() override;

	virtual std::string translateMessage(const std::shared_ptr<Message> message);

protected:
	inline virtual std::shared_ptr<Message> createMessage(const std::string message_string) override
		{ return std::make_shared<Message>(message_string); };

};



inline void Protocol_Plain::translateInput()
{
	if (this->input_buffer_->getSize() > 0)
	{
		this->invokeReceive(this->createMessage(this->input_buffer_->getContent()));

		this->input_buffer_->clear();
	}
}


inline std::string Protocol_Plain::translateMessage(const std::shared_ptr<Message> message)
{
	std::string result;


	if (message)
	{
		result = message->getContent();
	}

	return result;
}

}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_PLAIN
