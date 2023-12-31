#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char key_code) const noexcept
{
	return key_states[key_code];
}

std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept
{
	if (key_buffer.empty()) return {};
	Keyboard::Event e = key_buffer.front();
	key_buffer.pop();
	return e;
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return key_buffer.empty();
}

std::optional<char> Keyboard::ReadChar() noexcept
{
	if (char_buffer.empty()) return {};
	unsigned char char_code = char_buffer.front();
	char_buffer.pop();
	return char_code;
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return char_buffer.empty();
}

void Keyboard::FlushKey() noexcept
{
	key_buffer = std::queue<Event>();
}

void Keyboard::FlushChar() noexcept
{
	char_buffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutoRepeat() noexcept
{
	auto_repeat_enabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	auto_repeat_enabled = false;
}

bool Keyboard::AutoRepeatIsEnabled() const noexcept
{
	return auto_repeat_enabled;
}

void Keyboard::OnKeyPressed(unsigned char key_code) noexcept
{
	key_states[key_code] = true;
	key_buffer.emplace(Keyboard::Event::Type::Press, key_code);
	TrimBuffer(key_buffer);
}

void Keyboard::OnKeyReleased(unsigned char key_code) noexcept
{
	key_states[key_code] = false;
	key_buffer.emplace(Keyboard::Event::Type::Release, key_code);
	TrimBuffer(key_buffer);
}

void Keyboard::OnChar(char character) noexcept
{
	char_buffer.push(character);
	TrimBuffer(char_buffer);
}

void Keyboard::ClearState() noexcept
{
	key_states.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer_size < buffer.size())
	{
		buffer.pop();
	}
}