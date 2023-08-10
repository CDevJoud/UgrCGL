#pragma once
#include <RenderTarget.hpp>
#include <Menu.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
#include <TextBox.hpp>
namespace ugr
{
    class UGRCGL_API Panel : public RenderTarget
    {
    public:
        /// <summary>
        /// Creates a panel with the specified size.
        /// </summary>
        /// <param name="size">The size of the panel.</param>
        VOID CreatePanel(Vector2i size);

        /// <summary>
        /// Sets the position of the panel.
        /// </summary>
        /// <param name="pos">The position to set.</param>
        VOID SetPosition(Vector2i pos);

        /// <summary>
        /// Sets the character used for the panel border.
        /// </summary>
        /// <param name="c">The character surface to set.</param>
        VOID SetBorderChar(CharSurface c);

        /// <summary>
        /// Sets the color of the panel border.
        /// </summary>
        /// <param name="color">The color to set.</param>
        VOID SetBorderColor(Color color);

        /// <summary>
        /// Creates a menu bar within the panel.
        /// </summary>
        /// <param name="sizex">The size of the menu bar along the X-axis.</param>
        /// <param name="c">The character surface for the menu bar.</param>
        /// <param name="color">The color of the menu bar.</param>
        VOID CreateMenuBar(BYTE sizex, CharSurface c, Color color);

        /// <summary>
        /// Adds a menu to the panel's menu bar.
        /// </summary>
        /// <param name="menutitle">The title of the menu.</param>
        /// <param name="attachMenuto">A pointer to the menu to attach.</param>
        /// <param name="color">The color of the menu button.</param>
        VOID AddMenu(LPCWSTR menutitle, Menu* attachMenuto, SHORT color);

        /// <summary>
        /// Renders a text box within the panel.
        /// </summary>
        /// <param name="box">A pointer to the text box to render.</param>
        VOID RenderTextBox(TextBox* box);

        /// <summary>
        /// Renders an input box within the panel.
        /// </summary>
        /// <param name="box">A pointer to the input box to render.</param>
        VOID RenderInputBox(InputBox* box);

        /// <summary>
        /// Renders a button within the panel.
        /// </summary>
        /// <param name="btn">A pointer to the button to render.</param>
        VOID RenderButton(Button* btn);

        /// <summary>
        /// Sets the title and title color of the panel.
        /// </summary>
        /// <param name="title">The title to set.</param>
        /// <param name="color">The color of the title.</param>
        VOID SetTitle(LPCWSTR title, Color color = 0x0F);

        /// <summary>
        /// Displays the panel content.
        /// </summary>
        VOID Display();

        /// <summary>
        /// Processes events for the panel using the provided EventProcessor.
        /// </summary>
        /// <param name="EP">The EventProcessor instance to use for event handling.</param>
        VOID ProcessEvents(EventProcessor* EP);

    private:
        /// <summary>
        /// Sets up the panel frame with the specified position, size, and color.
        /// </summary>
        /// <param name="pos">The position of the panel frame.</param>
        /// <param name="size">The size of the panel frame.</param>
        /// <param name="color">The color of the panel frame.</param>
        VOID SetUpFrame(Vector2i pos, Vector2i size, Color color = 0x0F);

        class pImpl;  // Pointer to implementation (PIMPL) idiom.
        pImpl* m_pImpl = NULL;  // PIMPL instance.

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
        } MenuBarProp;

        typedef struct _MenuButtonPropreties
        {
            LPCWSTR menuTitle;
            Menu* RedirectMenuBox;
            SHORT MenuButtonColor;
        } MenuButtonProp;

        friend class ConsoleWindow;
    };
}