#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "UiComponent.h"
#include "Interactive.h"
#include <string>
using std::string;

namespace CursesUi
{
	class TextBox : public UiComponent, public Interactive
	{
	protected:
		string _text;

	public:
		TextBox(WINDOW* parent = 0, int height = 0, int width = 0, int y = 0, int x = 0, string text = "")
			: UiComponent(parent, height, width, y, x), _text(text)
		{
			//empty
		}

		TextBox(WINDOW* parent = 0, int y = 0, int x = 0, string text = "")
			: UiComponent(parent, 1, text.length(), y, x), _text(text)
		{
			//empty
		}

		string getText() const
		{
			return _text;
		}

		string& getText()
		{
			return _text;
		}

		void setText(const string& text)
		{
			_text = text;
		}

		virtual void render()
		{
			//empty
		}

		virtual void handleKeyboardInput(wchar_t input)
		{
			waddch(_canvas, input);
			_needs_refresh = true;
		}

		virtual void handleMouseInput(int y, int x, MouseClick click_type)
		{
			if (click_type == MouseClick::LEFT_CLICK)
			{
				wmove(_canvas, y, x);
			}
		}
	};
}


#endif // !TEXTBOX_H

