#ifndef NEXUS_MOUSE_H
#define NEXUS_MOUSE_H

#include <optional>
#include <queue>

class Mouse
{
	friend class Window;

 public:
	struct RawDelta {
		int x, y;
	};

	class Event
	{
	 public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
		};

	 private:
		Type type;
		bool leftIsPressed;
		bool rightIsPressed;
		int x;
		int y;

	 public:
		Event(const Type type, const Mouse & parent) noexcept
			: type(type),
			  leftIsPressed(parent.leftIsPressed),
			  rightIsPressed(parent.rightIsPressed),
			  x(parent.x),
			  y(parent.y)
		{
		}

		[[nodiscard]] auto GetType() const noexcept -> Type
		{
			return type;
		}

		[[nodiscard]] auto GetPos() const noexcept -> std::pair<int, int>
		{
			return {x, y};
		}

		[[nodiscard]] auto GetPosX() const noexcept -> int
		{
			return x;
		}

		[[nodiscard]] auto GetPosY() const noexcept -> int
		{
			return y;
		}

		[[nodiscard]] auto LeftIsPressed() const noexcept -> bool
		{
			return leftIsPressed;
		}

		[[nodiscard]] auto RightIsPressed() const noexcept -> bool
		{
			return rightIsPressed;
		}
	};

    Mouse() = default;

    Mouse(const Mouse &) = delete;

	void Flush() noexcept;

	void EnableRaw() noexcept;

	void DisableRaw() noexcept;

	auto operator=(const Mouse &) -> Mouse & = delete;

	auto ReadRawDelta() noexcept -> std::optional<RawDelta>;

	auto Read() noexcept -> std::optional<Event>;

	[[nodiscard]] auto GetPos() const noexcept -> std::pair<int, int>;

	[[nodiscard]] auto GetPosX() const noexcept -> int;

	[[nodiscard]] auto GetPosY() const noexcept -> int;

	[[nodiscard]] auto IsInWindow() const noexcept -> bool;

	[[nodiscard]] auto LeftIsPressed() const noexcept -> bool;

	[[nodiscard]] auto RightIsPressed() const noexcept -> bool;

	[[nodiscard]] auto RawEnabled() const noexcept -> bool;

	[[nodiscard]] auto IsEmpty() const noexcept -> bool;

 private:
	int x{};

	int y{};

	bool leftIsPressed = false;

	bool rightIsPressed = false;

	bool isInWindow = false;

	int wheelDeltaCarry = 0;

	bool rawEnabled = false;

	std::queue<Event> buffer;

	std::queue<RawDelta> rawDeltaBuffer;

	void OnMouseMove(int x, int y) noexcept;

	void OnMouseLeave() noexcept;

	void OnMouseEnter() noexcept;

	void OnRawDelta(int dx, int dy) noexcept;

	void OnLeftPressed(int x, int y) noexcept;

	void OnLeftReleased(int x, int y) noexcept;

	void OnRightPressed(int x, int y) noexcept;

	void OnRightReleased(int x, int y) noexcept;

	void OnWheelUp(int x, int y) noexcept;

	void OnWheelDown(int x, int y) noexcept;

	void TrimBuffer() noexcept;

	void TrimRawInputBuffer() noexcept;

	void OnWheelDelta(int x, int y, int delta) noexcept;

	static constexpr unsigned int bufferSize = 16U;
};

#endif
