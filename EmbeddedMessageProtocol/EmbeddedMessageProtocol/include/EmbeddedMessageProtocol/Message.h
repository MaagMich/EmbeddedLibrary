#ifndef H_EMBEDDEDMESSAGEPROTOCOL_MESSAGE
#define H_EMBEDDEDMESSAGEPROTOCOL_MESSAGE

#include <string>


namespace message_protocol
{

class Message
{
public:
	inline Message(const std::string content)
		: content_(content)
	{};

	inline auto getContent() const
	{
		return this->content_;
	};

private:
	std::string content_;

};

}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_MESSAGE
