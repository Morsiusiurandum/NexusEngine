#include "keyboard.h"

bool keyboard::KeyIsPressed(unsigned char key_code) const noexcept
{
	return key_states[key_code];
}

std::optional<keyboard::Event> keyboard::ReadKey() noexcept
{
	if (key_buffer.empty()) return {};
    keyboard::Event e = key_buffer.front();
	key_buffer.pop();
	return e;
}

bool keyboard::KeyIsEmpty() const noexcept
{
	return key_buffer.empty();
}

std::optional<char> keyboard::ReadChar() noexcept
{
	if (char_buffer.empty()) return {};
	unsigned char char_code = char_buffer.front();
	char_buffer.pop();
	return char_code;
}

bool keyboard::CharIsEmpty() const noexcept
{
	return char_buffer.empty();
}

void keyboard::FlushKey() noexcept
{
	key_buffer = std::queue<Event>();
}

void keyboard::FlushChar() noexcept
{
	char_buffer = std::queue<char>();
}

void keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void keyboard::EnableAutoRepeat() noexcept
{
	auto_repeat_enabled = true;
}

void keyboard::DisableAutoRepeat() noexcept
{
	auto_repeat_enabled = false;
}

bool keyboard::AutoRepeatIsEnabled() const noexcept
{
	return auto_repeat_enabled;
}

void keyboard::OnKeyPressed(unsigned char key_code) noexcept
{
	key_states[key_code] = true;
	key_buffer.emplace(keyboard::Event::Type::Press, key_code);
	TrimBuffer(key_buffer);
}

void keyboard::OnKeyReleased(unsigned char key_code) noexcept
{
	key_states[key_code] = false;
	key_buffer.emplace(keyboard::Event::Type::Release, key_code);
	TrimBuffer(key_buffer);
}

void keyboard::OnChar(char character) noexcept
{
	char_buffer.push(character);
	TrimBuffer(char_buffer);
}

void keyboard::ClearState() noexcept
{
	key_states.reset();
}

template<typename T>
void keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer_size < buffer.size())
	{
		buffer.pop();
	}
}