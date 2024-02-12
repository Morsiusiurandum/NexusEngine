#include "Mouse.h"
#include "NexusMacro.h"

auto Mouse::GetPos() const noexcept -> std::pair<int, int>
{
	return {x, y};
}

auto Mouse::ReadRawDelta() noexcept -> std::optional<RawDelta>
{
	if (rawDeltaBuffer.empty())
	{
		return std::nullopt;
	}
	const RawDelta d = rawDeltaBuffer.front();
	rawDeltaBuffer.pop();
	return d;
}

auto Mouse::GetPosX() const noexcept -> int
{
	return x;
}

auto Mouse::GetPosY() const noexcept -> int
{
	return y;
}

auto Mouse::IsInWindow() const noexcept -> bool
{
	return isInWindow;
}

auto Mouse::LeftIsPressed() const noexcept -> bool
{
	return leftIsPressed;
}

auto Mouse::RightIsPressed() const noexcept -> bool
{
	return rightIsPressed;
}

auto Mouse::Read() noexcept -> std::optional<Event>
{
	if (!buffer.empty())
	{
		Event e = buffer.front();
		buffer.pop();
		return e;
	}
	return {};
}

auto Mouse::IsEmpty() const noexcept -> bool
{
	return buffer.empty();
}

auto Mouse::RawEnabled() const noexcept -> bool
{
	return rawEnabled;
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::EnableRaw() noexcept
{
	rawEnabled = true;
}

void Mouse::DisableRaw() noexcept
{
	rawEnabled = false;
}


void Mouse::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;

	buffer.emplace(Event::Type::Move, *this);
	TrimBuffer();
}

void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.emplace(Event::Type::Leave, *this);
	TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.emplace(Event::Type::Enter, *this);
	TrimBuffer();
}

void Mouse::OnRawDelta(int dx, int dy) noexcept
{
	rawDeltaBuffer.push({dx, dy});
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;

	buffer.emplace(Event::Type::LPress, *this);
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;

	buffer.emplace(Event::Type::LRelease, *this);
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;

	buffer.emplace(Event::Type::RPress, *this);
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;

	buffer.emplace(Event::Type::RRelease, *this);
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	buffer.emplace(Event::Type::WheelUp, *this);
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	buffer.emplace(Event::Type::WheelDown, *this);
	TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}

void Mouse::TrimRawInputBuffer() noexcept
{
	while (rawDeltaBuffer.size() > bufferSize)
	{
		rawDeltaBuffer.pop();
	}
}

void Mouse::OnWheelDelta(const int x, const int y, const int delta) noexcept
{
	wheelDeltaCarry += delta;
	// generate events for every 120
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}