#include <Windows.h>
#include "Sprite.hpp"
#include <Register.hpp>

namespace ugr
{
	class Sprite::pImpl 
	{
	public:
		pImpl()
		{
			
		}
		~pImpl()
		{
			delete this->re.buffer;
			CloseHandle(hFile);
		}
		
		HANDLE hFile;
		RenderElements re;
		DWORD nFileSize;
		SprHeader sprheader;
	};

	Sprite::Sprite()
	{
		this->This = new pImpl;
	}

	Sprite::Sprite(LPCWSTR fileName)
	{
		this->This = new pImpl;
	}
	BOOL Sprite::LoadSpriteFromFile(LPCWSTR fileName)
	{
		if(!This->hFile)
			This->hFile = CreateFileW(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(This->hFile != INVALID_HANDLE_VALUE)
		{
			This->nFileSize = GetFileSize(This->hFile, NULL);
			DWORD read = 0;

			This->re.buffer = new CharPixel[This->nFileSize]{};
			ReadFile(This->hFile, &This->sprheader, 12, &read, NULL);
			ReadFile(This->hFile, This->re.buffer, This->nFileSize, &read, NULL);

			This->re.screen.x = This->sprheader.x;
			This->re.screen.y = This->sprheader.y;
			return TRUE;
		}
		return FALSE;
	}
	VOID Sprite::LoadSpriteFromCanvas(Canvas* c)
	{
		if (!This)
			This = new pImpl;
		This->re = c->re;
		This->sprheader.version = 0x0001;
		This->sprheader.x = c->re.screen.x;
		This->sprheader.y = c->re.screen.y;
	}
	VOID Sprite::SaveSpriteToFile(LPCWSTR fileName)
	{
		This->hFile = CreateFileW(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD written = 0;
		WriteFile(This->hFile, reinterpret_cast<void*>(&This->sprheader), sizeof(This->sprheader), &written, NULL);
		WriteFile(This->hFile, reinterpret_cast<void*>(This->re.buffer), This->re.screen.x * This->re.screen.y * sizeof(CharPixel), &written, NULL);
	}

	Vector2i Sprite::GetSize() const
	{
		return This->re.screen;
	}
	CharPixel Sprite::GetPixel(int x, int y) const
	{
		if (x >= 0 && x <= This->re.screen.x && y >= 0 && y <= This->re.screen.y)
		{
			return This->re.buffer[y * This->re.screen.x + x];
		}
	}
}
