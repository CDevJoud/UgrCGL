#pragma once
#include <RenderTarget.hpp>
#include <Menu.hpp>
#include <Button.hpp>
namespace ugr
{
	class UGRCGL_API Panel : public RenderTarget
	{
	public:
		VOID CreatePanel(Vector2i size);
		VOID SetPosition(Vector2i pos);

		VOID SetBorderChar(CharSurface c);
		VOID SetBorderColor(Color color);

		VOID CreateMenuBar(BYTE sizex, CharSurface c, Color color);
		VOID AddMenu(LPCWSTR menutitle, Menu* attachMenuto, SHORT color);

		//DANGEROUS FUNCTION
		//VOID RenderPanel(Panel* p);

		//VOID RenderTextBox(TextBox* box);
		//VOID RenderInputBox(InputBox* box);
		VOID RenderButton(Button* btn);

		VOID SetTitle(LPCWSTR title, Color color = 0x0F);
		VOID Display();

		VOID ProcessEvents(EventProcessor* EP);
	private:
		VOID SetUpFrame(Vector2i pos, Vector2i size, Color color = 0x0F);
		class pImpl;
		pImpl* m_pImpl = NULL;

		// Pimple Getters

		Vector2i GetVecPosition() const;
		Vector2i GetVecBufferSize() const;
		Color GetBorderColor() const;
		LPCWSTR GetPanelTitle() const;
		Color GetPanelTitleColor() const;
		ScreenBuffer GetBuffer() const;
		// /Pimple Getters

		typedef struct _MenuBarPropreties
		{
			BYTE sizeX;
			SHORT surface;
			SHORT color;
		}MenuBarProp;
		typedef struct _MenuButtonPropreties
		{
			LPCWSTR menuTitle;
			Menu* RedirectMenuBox;
			SHORT MenuButtonColor;
		}MenuButtonProp;
		friend class ConsoleWindow;
	};
}