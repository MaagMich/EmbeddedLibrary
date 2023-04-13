#ifndef H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_HEADER_ENCAPSULATED
#define H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_HEADER_ENCAPSULATED

#include "Protocol_Header_Start.h"
#include "InputBuffer.h"


namespace message_protocol
{

class Protocol_Header_Encapsulated final : public Protocol_Header_Start
{
public:
	inline Protocol_Header_Encapsulated(
		const std::string header_start,
		const std::string header_end,
		receive_callback receive_callback,
		std::unique_ptr<InputBuffer> input_buffer = std::make_unique<InputBuffer>()
	);

	virtual void translateInput() override;

	virtual std::string translateMessage(const std::shared_ptr<Message> message) override;

protected:
	inline auto getHeaderEnd() const
		{ return this->header_end_; };

private:
	std::string header_end_;

};



inline Protocol_Header_Encapsulated::Protocol_Header_Encapsulated(
	const std::string header_start, 
	const std::string header_end, 
	receive_callback receive_callback, 
	std::unique_ptr<InputBuffer> input_buffer
)
	: Protocol_Header_Start(header_start, receive_callback, std::move(input_buffer)),
	header_end_(header_end)
{
	if (this->getHeaderEnd().size() == 0)
	{
		throw std::invalid_argument("Missing Header Stop-Sequence.");
	}
}


inline void Protocol_Header_Encapsulated::translateInput()
{
	const auto pos_end = this->input_buffer_->findString_First(this->getHeaderEnd());


	if (pos_end != std::string::npos)
	{
		const auto content_stop = this->input_buffer_->remove(pos_end);
		const auto pos_start = content_stop.find_last_of(this->getHeaderStart(), pos_end);


		this->input_buffer_->remove(this->getHeaderEnd().size());

		if (pos_start != std::string::npos)
		{
			const auto message = this->createMessage(
				content_stop.substr(pos_start + 1)
			);


			if (this->invokeReceive(message))
			{
				this->translateInput();
			}
		}
	}
}


inline std::string Protocol_Header_Encapsulated::translateMessage(const std::shared_ptr<Message> message)
{
	std::string result;


	if (message)
	{
		result = this->getHeaderStart()
			.append(message->getContent())
			.append(this->getHeaderEnd());
	}

	return result;
}

/*
inline std::optional<std::string> Protocol_Header_Encapsulated::getMessageContent()
{
	std::optional<std::string> result;
	const auto pos_end = this->input_buffer_->findString(this->getHeaderEnd());


	if (pos_end != std::string::npos)
	{
		const auto start_size = this->getHeaderStart().size();
		const auto end_size = this->getHeaderEnd().size();
		auto message_string = this->input_buffer_->remove(
			pos_end + end_size
		);


		if (message_string.size() > start_size + end_size)
		{
			message_string.erase(0, start_size);
			message_string.erase(message_string.size() - end_size, end_size);

			result = message_string;
		}
	}

	return result;
}
*/
}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_PROTOCOL_HEADER_ENCAPSULATED
