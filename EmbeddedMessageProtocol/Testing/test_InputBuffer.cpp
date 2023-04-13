#include "gtest/gtest.h"

#include "../EmbeddedMessageProtocol/include/EmbeddedMessageProtocol/InputBuffer.h"

using namespace message_protocol;





TEST(InputBuffer, check_buffer_content_single_push)
{
	const std::string buffer_content = "Hello World!";

	InputBuffer buffer;
	{
		buffer.pushInput(buffer_content);
	}


	const auto result = buffer.getContent();


	EXPECT_EQ(result, buffer_content);
}

TEST(InputBuffer, check_buffer_content_multiple_push)
{
	const std::string buffer_content1 = "Hello";
	const std::string buffer_content2 = " World!";

	InputBuffer buffer;
	{
		buffer.pushInput(buffer_content1);
		buffer.pushInput(buffer_content2);
	}


	const auto result = buffer.getContent();


	EXPECT_EQ(result, std::string(buffer_content1).append(buffer_content2));
}


TEST(InputBuffer, erase_something_from_empty_buffer)
{
	InputBuffer buffer;


	const auto result = buffer.remove(1);


	EXPECT_EQ(result, "");
}

TEST(InputBuffer, erase_nothing_from_buffer)
{
	InputBuffer buffer;


	const auto result = buffer.remove(0);


	EXPECT_EQ(result, "");
}

TEST(InputBuffer, erase_something_from_buffer)
{
	const std::string buffer_content1 = "Hello";
	const std::string buffer_content2 = " World!";

	InputBuffer buffer;
	{
		buffer.pushInput(buffer_content1);
		buffer.pushInput(buffer_content2);
	}


	const auto result_erased = buffer.remove(buffer_content1.size());
	const auto result_buffer = buffer.getContent();


	EXPECT_EQ(result_erased, buffer_content1);
	EXPECT_EQ(result_buffer, buffer_content2);
}

TEST(InputBuffer, erase_everything_from_buffer)
{
	const std::string buffer_content = "Hello World!";

	InputBuffer buffer;
	{
		buffer.pushInput(buffer_content);
	}


	const auto result = buffer.remove(buffer.getSize());


	EXPECT_EQ(result, buffer_content);
	EXPECT_EQ(buffer.getSize(), 0);
}