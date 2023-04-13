#include "gtest/gtest.h"

#include "../EmbeddedMessageProtocol/include/EmbeddedMessageProtocol/Protocol_Header_Encapsulated.h"

#include "Mock_MessageReceiver.h"
#include "EXPECT_Message.h"



TEST(Protocol_Header_Encapsulated, translate_message_to_string)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content = "Hello World!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);
	const auto message = std::make_shared<message_protocol::Message>(content);


	const auto result = protocol.translateMessage(message);


	{
		const auto expection = std::string(header_start).append(content).append(header_stop);


		EXPECT_EQ(result, expection);
	}
}



TEST(Protocol_Header_Encapsulated, translate_input_to_message)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content = "Hello World!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);


	{
		protocol.pushInput(header_start);
		protocol.pushInput(content);
		protocol.pushInput(header_stop);
	}


	const auto result_list = receiver.getMessages();


	EXPECT_EQ(result_list.size(), 1);
	{
		const auto result = result_list.front();
		const auto expection = std::make_shared<message_protocol::Message>(content);


		EXPECT_EQ_MESSAGE(result, expection);
	}
}

TEST(Protocol_Header_Encapsulated, translate_multiple_inputs_to_messages)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content1 = "Hello World!";
	const std::string content2 = "Hello Again!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);


	{
		protocol.pushInput(header_start);
		protocol.pushInput(content1);
		protocol.pushInput(header_stop);
		protocol.pushInput(header_start);
		protocol.pushInput(content2);
		protocol.pushInput(header_stop);
	}


	const auto result_list = receiver.getMessages();


	EXPECT_EQ(result_list.size(), 2);
	{
		const auto result = result_list.front();
		const auto expection = std::make_shared<message_protocol::Message>(content1);


		EXPECT_EQ_MESSAGE(result, expection);
	}
	{
		const auto result = result_list.back();
		const auto expection = std::make_shared<message_protocol::Message>(content2);


		EXPECT_EQ_MESSAGE(result, expection);
	}
}



TEST(Protocol_Header_Encapsulated, translate_multiple_partially_incorrect_inputs_to_messages_missing_start)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content1 = "Hello World!";
	const std::string content2 = "Hello Again!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);


	{
		protocol.pushInput(header_start);
		protocol.pushInput(content1);
		protocol.pushInput(header_stop);
		protocol.pushInput(content2);
		protocol.pushInput(header_stop);
	}


	const auto result_list = receiver.getMessages();


	EXPECT_EQ(result_list.size(), 1);
	{
		const auto result = result_list.front();
		const auto expection = std::make_shared<message_protocol::Message>(content1);


		EXPECT_EQ_MESSAGE(result, expection);
	}
}

TEST(Protocol_Header_Encapsulated, translate_multiple_partially_incorrect_inputs_to_messages_missing_stop)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content1 = "Hello World!";
	const std::string content2 = "Hello Again!";
	const std::string content3 = "And Again!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);


	{
		protocol.pushInput(header_start);
		protocol.pushInput(content1);
		protocol.pushInput(header_start);
		protocol.pushInput(content2);
		protocol.pushInput(header_stop);
	}


	const auto result_list = receiver.getMessages();


	EXPECT_EQ(result_list.size(), 1);
	{
		const auto result = result_list.back();
		const auto expection = std::make_shared<message_protocol::Message>(content2);


		EXPECT_EQ_MESSAGE(result, expection);
	}
}

TEST(Protocol_Header_Encapsulated, translate_multiple_partially_incorrect_inputs_to_messages_missing_stop_and_start)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content1 = "Hello World!";
	const std::string content2 = "Hello Again!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);


	{
		protocol.pushInput(header_start);
		protocol.pushInput(content1);
		protocol.pushInput(content2);
		protocol.pushInput(header_stop);
	}


	const auto result_list = receiver.getMessages();


	EXPECT_EQ(result_list.size(), 1);
	{
		const auto result = result_list.front();
		const auto expection = std::make_shared<message_protocol::Message>(std::string(content1).append(content2));


		EXPECT_EQ_MESSAGE(result, expection);
	}
}



TEST(Protocol_Header_Encapsulated, roundtrip)
{
	const std::string header_start = "#*#*";
	const std::string header_stop = "~#~#";
	const std::string content = "Hello World!";

	Mock_MessageReceiver receiver;
	message_protocol::Protocol_Header_Encapsulated protocol(
		header_start,
		header_stop,
		receiver.getFunction()
	);
	const auto message = std::make_shared<message_protocol::Message>(content);

	
	{
		protocol.pushInput(
			protocol.translateMessage(message)
		);
	}


	const auto result_list = receiver.getMessages();


	EXPECT_EQ(result_list.size(), 1);
	{
		const auto result = result_list.front();
		const auto expection = std::make_shared<message_protocol::Message>(content);


		EXPECT_EQ_MESSAGE(result, expection);
	}
}
