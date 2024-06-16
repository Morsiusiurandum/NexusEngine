#ifndef NEXUS_KEYBOARD_H
#define NEXUS_KEYBOARD_H

#include <bitset>
#include <optional>
#include <queue>

class keyboard
{
	friend class Window;

 public:
	class Event
	{
	 public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};

	 private:
		Type type;
		unsigned char code;

	 public:
		Event(Type type, unsigned char code) noexcept
			: type(type), code(code)
		{
		}
		[[nodiscard]] bool IsPress() const noexcept
		{
			return type == Type::Press;
		}
		[[nodiscard]] bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}
		[[nodiscard]] unsigned char GetCode() const noexcept
		{
			return code;
		}
	};

 public:
     keyboard() = default;

     keyboard(const keyboard &) = delete;

     keyboard & operator=(const keyboard &) = delete;

	// key event stuff
	[[nodiscard]] auto KeyIsPressed(unsigned char key_code) const noexcept -> bool;

	std::optional<Event> ReadKey() noexcept;

	[[nodiscard]] bool KeyIsEmpty() const noexcept;

	void FlushKey() noexcept;

	// char event stuff
	std::optional<char> ReadChar() noexcept;

	[[nodiscard]] bool CharIsEmpty() const noexcept;

	void FlushChar() noexcept;

	void Flush() noexcept;

	// auto repeat control
	void EnableAutoRepeat() noexcept;

	void DisableAutoRepeat() noexcept;

	[[nodiscard]] bool AutoRepeatIsEnabled() const noexcept;

 private:
	void OnKeyPressed(unsigned char key_code) noexcept;

	void OnKeyReleased(unsigned char key_code) noexcept;

	void OnChar(char character) noexcept;

	void ClearState() noexcept;

	template<typename T>

	static void TrimBuffer(std::queue<T>& buffer) noexcept;

 private:
	static constexpr unsigned int keys = 256u;

	static constexpr unsigned int buffer_size = 16u;

	bool auto_repeat_enabled = false;

	std::bitset<keys> key_states;

	std::queue<Event> key_buffer;
	
	std::queue<char> char_buffer;
};

#endif//NEXUS_KEYBOARD_H
