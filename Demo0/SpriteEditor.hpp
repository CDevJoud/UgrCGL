#include <UgrCGL.hpp>
#include <vector>
//Sprite Editor

namespace ugr
{
	class SpriteEditor : ConsoleWindow
	{
	public:
		enum class EColorBrush
		{
			BLACK = 0, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE
		}ColorBrush;
		SpriteEditor(LPCWSTR fileName) : fileName(fileName)
		{
			this->InitConsoleWindow();
			this->CreateConsoleBufferWindow(Vector2i(240, 85), Vector2i(8, 12));

			this->MainPanel->CreatePanel(Vector2i(30, 83));
			this->MainPanel->SetTitle(L"{Choose Color}", 0x0C);

			this->SpritePanel->CreatePanel(Vector2i(205, 83));
			this->SpritePanel->SetPosition(Vector2i(33, 1));
			this->SpritePanel->SetTitle(L"{Sprite Editor}", 0x01);

			this->InitColorButton();
			this->InitShapeButton();

			this->SpriteCavnas = new Canvas(Vector2i(205, 83));
			this->SpriteCavnas->ClearScreen(0x2588, 0x77);

			this->spr = new Sprite;
			//this->spr->LoadSpriteFromCanvas(this->SpriteCavnas);
			if (!this->spr->LoadSpriteFromFile(this->fileName))
			{
				this->spr->LoadSpriteFromCanvas(this->SpriteCavnas);
				this->spr->SaveSpriteToFile(this->fileName);
			}
			else
				this->LoadCanvasFromSprite(this->spr);
			
		}
		~SpriteEditor()
		{
			this->ClearScreen();
			this->Display();
			this->ShutDown();
			this->spr->SaveSpriteToFile(this->fileName);
			delete this->MainPanel, this->SpritePanel, this->SpriteCavnas, this->spr;
			this->ShapeButton.clear();
			this->ShapeButton.shrink_to_fit();
			this->ColorButton.clear();
			this->ColorButton.shrink_to_fit();
		}
		void run()
		{
			while (this->m_bIsRunning)
			{
				this->ProcessEvents();
				if (FillRect)
				{
					ShapeButton[1].SetColor(0x22);
					ShapeButton[1].SetTitle(L"RasterizeQuad", 0x2F);
				}
				else
				{
					ShapeButton[1].SetColor(0x44);
					ShapeButton[1].SetTitle(L"RasterizeQuad", 0x4F);
				}
				if (DrawLine)
				{
					ShapeButton[0].SetColor(0x22);
					ShapeButton[0].SetTitle(L"RenderLine", 0x2F);
				}
				else
				{
					ShapeButton[0].SetColor(0x44);
					ShapeButton[0].SetTitle(L"RenderLine", 0x4F);
				}


				//Render a Line
				if (this->Mouse(MouseType::Left).bStrokePressed && (DrawLine || FillRect))
				{
					Vector2i TranslatedMousePos = Vector2i(this->GetMousePos().x - 33, this->GetMousePos().y - 1);
					if (this->SpritePanel->CheckInBoundaries(TranslatedMousePos, { 0, 0, 205, 83 }))
					{
						this->InitialClickedPos = TranslatedMousePos;
					}
				}
				if (this->Mouse(MouseType::Left).bStrokeReleased && (DrawLine || FillRect))
				{
					Vector2i TranslatedMousePos = Vector2i(this->GetMousePos().x - 33, this->GetMousePos().y - 1);
					if (this->SpritePanel->CheckInBoundaries(TranslatedMousePos, { 0, 0, 205, 83 }))
					{
						if (DrawLine)
							this->SpriteCavnas->RenderLine(InitialClickedPos, TranslatedMousePos, 0x2588, static_cast<int>(this->ColorBrush));
						else if (FillRect)
							this->SpriteCavnas->Fill(InitialClickedPos, { TranslatedMousePos.x + 1, TranslatedMousePos.y + 1 }, 0x2588, static_cast<int>(ColorBrush));
					}
				}

				//Sets Pixel
				if (this->Mouse(MouseType::Left).bStrokeIsHeld)
				{
					Vector2i TranslatedMousePos = Vector2i(this->GetMousePos().x - 33, this->GetMousePos().y - 1);
					if (this->SpritePanel->CheckInBoundaries(TranslatedMousePos, { 0, 0, 205, 83 }) && !DrawLine && !FillRect)
					{
						this->SpriteCavnas->SetPixel(TranslatedMousePos, 0x2588, static_cast<int>(this->ColorBrush));
					}
				}

				this->m_bIsRunning = !this->Keyboard(0x1B).bStrokeReleased;

				this->RenderMainPanel();
				this->RenderSpriteEditorPanel();

				this->ClearScreen();
				this->RenderPanel(this->MainPanel);
				this->RenderPanel(this->SpritePanel);
				this->SetPixel(this->GetMousePos(), 0x2588, static_cast<int>(this->ColorBrush));
				this->Display();
			}
		}
	private:
		void LoadCanvasFromSprite(Sprite* spr)
		{
			for(int x = 0; x < spr->GetSize().x; x++)
				for (int y = 0; y < spr->GetSize().y; y++)
				{
					CharPixel cp = spr->GetPixel(x, y);
					SpriteCavnas->SetPixel(Vector2i(x, y), cp.Char.UnicodeChar, cp.Color);
				}
		}
		void InitColorButton()
		{
			this->ColorButton.resize(10);

			this->ColorButton[0].SetColor(0x00);
			this->ColorButton[0].SetTitle(L"BLACK", 0x0F);
			this->ColorButton[0].SetPosition(Vector2i(1, 1));
			this->ColorButton[0].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::BLACK;
				});

			this->ColorButton[1].SetColor(0x01);
			this->ColorButton[1].SetTitle(L"BLUE", 0x1F);
			this->ColorButton[1].SetPosition(Vector2i(1, 3));
			this->ColorButton[1].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::BLUE;
				});

			this->ColorButton[2].SetColor(0x02);
			this->ColorButton[2].SetTitle(L"GREEN", 0x2F);
			this->ColorButton[2].SetPosition(Vector2i(1, 5));
			this->ColorButton[2].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::GREEN;
				});

			this->ColorButton[3].SetColor(0x03);
			this->ColorButton[3].SetTitle(L"AQUA", 0x3F);
			this->ColorButton[3].SetPosition(Vector2i(1, 7));
			this->ColorButton[3].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::AQUA;
				});

			this->ColorButton[4].SetColor(0x04);
			this->ColorButton[4].SetTitle(L"RED", 0x4F);
			this->ColorButton[4].SetPosition(Vector2i(1, 9));
			this->ColorButton[4].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::RED;
				});

			this->ColorButton[5].SetColor(0x05);
			this->ColorButton[5].SetTitle(L"PURPLE", 0x5F);
			this->ColorButton[5].SetPosition(Vector2i(1, 11));
			this->ColorButton[5].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::PURPLE;
				});

			this->ColorButton[6].SetColor(0x06);
			this->ColorButton[6].SetTitle(L"YELLOW", 0x6F);
			this->ColorButton[6].SetPosition(Vector2i(1, 13));
			this->ColorButton[6].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::YELLOW;
				});

			this->ColorButton[7].SetColor(0x07);
			this->ColorButton[7].SetTitle(L"WHITE", 0x7F);
			this->ColorButton[7].SetPosition(Vector2i(1, 15));
			this->ColorButton[7].OnClicked([&]()mutable -> void {
				ColorBrush = EColorBrush::WHITE;
				});
		}
		void InitShapeButton()
		{
			this->ShapeButton.resize(3);
			auto& SB0 = this->ShapeButton[0];
			SB0.SetColor(0x44);
			SB0.SetTitle(L"RenderLine", 0x4F);
			SB0.SetPosition(Vector2i(1, 70));
			SB0.OnClicked([&]()mutable -> void {
				if (FillRect)
					FillRect = !FillRect;
				DrawLine = !DrawLine;
				});
			auto& SB1 = this->ShapeButton[1];
			SB1.SetColor(0x44);
			SB1.SetTitle(L"RasterizeQuad", 0x4F);
			SB1.SetPosition(Vector2i(1, 72));
			SB1.OnClicked([&]() mutable -> void {
				FillRect = !FillRect;
				if (DrawLine)
					DrawLine = !DrawLine;

				});
		}
		void DrawColorButton()
		{
			for (auto& btn : this->ColorButton)
			{
				btn.ProcessEvents(this);
				this->MainPanel->RenderButton(&btn);
			}
		}
		void DrawShapeButton()
		{
			for (auto& btn : this->ShapeButton)
			{
				btn.ProcessEvents(this);
				this->MainPanel->RenderButton(&btn);
			}
		}
		void RenderMainPanel()
		{
			this->MainPanel->ClearScreen();

			this->DrawColorButton();
			this->DrawShapeButton();

			this->MainPanel->Display();
		}

		void RenderSpriteEditorPanel()
		{
			this->SpritePanel->ClearScreen();

			for (int x = 0; x < 205; x++)
				for (int y = 0; y < 83; y++)
				{
					CharPixel cp = this->SpriteCavnas->GetPixel(x, y);
					this->SpritePanel->SetPixel(Vector2i(x, y), cp.Char.UnicodeChar, cp.Color);
				}
			this->spr->LoadSpriteFromCanvas(this->SpriteCavnas);

			this->SpritePanel->Display();
		}
		Panel* MainPanel = new Panel;
		Panel* SpritePanel = new Panel;
		Canvas* SpriteCavnas = nullptr;
		Sprite* spr = nullptr;
		std::vector<Button> ColorButton;
		bool m_bIsRunning = true;
		Vector2i InitialClickedPos;
		std::vector<Button> ShapeButton;
		bool DrawLine = false;
		bool FillRect = false;
		LPCWSTR fileName;
	};
}