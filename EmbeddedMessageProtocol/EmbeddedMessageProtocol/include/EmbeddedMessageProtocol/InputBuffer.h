#ifndef H_EMBEDDEDMESSAGEPROTOCOL_INPUTBUFFER
#define H_EMBEDDEDMESSAGEPROTOCOL_INPUTBUFFER

#include <string>


namespace message_protocol
{

class InputBuffer
{
public:
	inline void pushInput(const std::string input)
		{ this->input_buffer_.append(input); };

	inline auto findString_First(const std::string search_string)
		{ return this->input_buffer_.find(search_string); };
	inline auto findString_Last(const std::string search_string, const size_t pos_end)
		{ return this->input_buffer_.find_last_of(search_string, pos_end); };

	inline void clear()
		{ this->input_buffer_.clear(); };
	inline std::string remove(const size_t position);


	inline auto getContent() const
		{ return this->input_buffer_; };
	inline auto getSize() const
		{ return this->input_buffer_.size(); };

protected:
	std::string input_buffer_;

};



inline std::string InputBuffer::remove(const size_t position)
{
	std::string result;


	if (position > 0 && position != std::string::npos)
	{
		if (position > this->getSize())
		{
			result = this->input_buffer_;

			this->input_buffer_.clear();
		}
		else
		{
			result = this->input_buffer_.substr(0, position);

			this->input_buffer_.erase(0, position);
		}
	}

	return result;
}

}	// namespace message_protocol

#endif	// H_EMBEDDEDMESSAGEPROTOCOL_INPUTBUFFER
