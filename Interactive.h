#pragma once
#ifndef INTERACTIVE_H
#define INTERACTIVE_H

enum class MouseClick
{
	LEFT_CLICK,
	RIGHT_CLICK
};

class Interactive
{
public:
	virtual void handleKeyboardInput(wchar_t input) = 0;
	virtual void handleMouseInput(int y, int x, MouseClick click_type) = 0;
};

#endif // !INTERACTIVE_H

