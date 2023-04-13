#pragma once

#include <list>
#include <memory>
#include <functional>

#include "../EmbeddedMessageProtocol/include/EmbeddedMessageProtocol/Message.h"


class Mock_MessageReceiver
{
public:
	inline void receiveMessage(std::shared_ptr<message_protocol::Message> message)
		{ this->messages_.push_back(message); };

	inline std::function<void(std::shared_ptr<message_protocol::Message>)> getFunction()
		{ return std::bind(&Mock_MessageReceiver::receiveMessage, this, std::placeholders::_1); };

	inline auto getMessages() const
		{ return this->messages_; };
	
private:
	std::list<std::shared_ptr<message_protocol::Message>> messages_;

};
