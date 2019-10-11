#pragma once
#ifndef LABELS_H
#define LABELS_H
#include "UiComponent.h"
#include <string>
using std::string;

namespace CursesUi
{
	class Label : public UiComponent
	{
	protected:
		string _text;

	public:
		Label(WINDOW* parent = 0, int height = 0, int width = 0, int y = 0, int x = 0, string text = "")
			: UiComponent(parent, height, width, y, x), _text(text)
		{
			//empty
		}

		Label(WINDOW* parent = 0, int y = 0, int x = 0, string text = "")
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
			if (_canvas != nullptr)
			{
				wmove(_canvas, 0, 0);
				waddstr(_canvas, _text.c_str());
			}
		}
	};
}

#endif // !LABELS_H

