#pragma once

#include "gtest/gtest.h"

#include <memory>

#include "../EmbeddedMessageProtocol/include/EmbeddedMessageProtocol/Message.h"



void EXPECT_EQ_MESSAGE(
	const std::shared_ptr<message_protocol::Message> message1, 
	const std::shared_ptr<message_protocol::Message> message2
)
{
	EXPECT_TRUE(message1 ? true : false);
	EXPECT_TRUE(message2 ? true : false);

	EXPECT_EQ(message1->getContent(), message2->getContent());
}







