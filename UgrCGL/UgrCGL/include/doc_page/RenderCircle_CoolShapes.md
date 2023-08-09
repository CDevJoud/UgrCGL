# Cool RenderCircle Shapes

# Cool RenderCircle Shapes

## Shape1
```cpp

int xx = 1;
int yy = 1;
void VertexShader(int& p, int& x, int& y)
{
    x += xx;
    y -= yy;
    p += (p <= 0) ? 4 * (x += 6) : 4 * (x += 10 - y) + 10;
}
 
class Demo : public ugr::ConsoleWindow
{
public:
    Demo()
    {
        this->InitConsoleWindow();
        this->CreateConsoleBufferWindow(ugr::Vector2i(240, 128), ugr::Vector2i(8, 8));
    }
    int run()
    {
        this->ClearScreen(0x2588, 0x06);
        while (true)
        {
            xx++;
            yy += 0.05;
            this->RenderCircle(ugr::Vector2i(120, 64), 60, 0x2588, 0x01, VertexShader);
            this->Display();
        }
        this->ShutDown();
        return 0;
    }
};
 
int main()
{
    Demo d;
    return d.run();
}

```

## Shape2

> warning this is heavy cost.
---
```cpp
#include <UgrCGL.hpp>
#include <random>

float xx = 1;
float yy = 1;

float xx1 = 1;
float yy1 = 1;

void VertexShader(int& p, int& x, int& y)
{
	x += xx;
	y -= yy;
	p += (p >= 0) ? 4 * (x += 6) : 4 * (x += 10 - y) + 10;
}

void VertexShader1(int& p, int& x, int& y)
{
	x += xx1;
	y -= yy1;
	p += (p == 0) ? 4 * (x += 6) : 4 * (x += 10 - y) + 10;
}

class Demo : public ugr::ConsoleWindow
{
public:
	Demo()
	{
		this->InitConsoleWindow();
		this->CreateConsoleBufferWindow(ugr::Vector2i(240 * 4, 128 * 4), ugr::Vector2i(2, 2));
	}
	int run()
	{
		std::random_device rd;   // Obtain a random seed from the hardware
		std::mt19937 gen(rd());  // Seed the generator

		// Define the range for the random number (0x01 to 0xFF)
		std::uniform_int_distribution<> dis(0x01, 0xFF);
		while (true)
		{
			xx++;
			yy += 0.05;
			this->RasterizeCircle(ugr::Vector2i(240 * 2, 128 * 2), 20, 0x2588, dis(gen));
			this->RenderCircle(ugr::Vector2i(240 * 2, 128 * 2), 120, 0x2588, 0x06, VertexShader);

			xx1 += 5;
			yy1 += 0.05;
			this->RenderCircle(ugr::Vector2i(240 * 2, 128 * 2), 120, 0x2588, 0x1, VertexShader1);
			this->Display();
			
		}
		return 0;
	}
};

int main()
{
	Demo d;
	return d.run();
}
```

## Shape3
> black hole
```cpp

#include <UgrCGL.hpp>
#include <random>

float xx, yy;

void StarShader(int& p, int& x, int& y)
{
    x++;
    y -= 4;
}

void VertexShader(int& p, int& x, int& y)
{
    x += xx;
    y -= yy;
    p += (p <= 0) ? 4 * (x -= 6) : 4 * (x += 10 - y) + 10;
}

class Demo : public ugr::ConsoleWindow
{
public:
    Demo()
    {
        this->InitConsoleWindow();
        this->CreateConsoleBufferWindow(ugr::Vector2i(480 * 2, 256 * 2), ugr::Vector2i(2, 2));
    }

    int run()
    {
        this->ClearScreen();
        ugr::Vector2i pos(380, 190);
        ugr::Vector2i p[3] =
        {
            ugr::Vector2i(),
            ugr::Vector2i(200, 0),
            ugr::Vector2i(100, 200)
        };
        ugr::Color CircleColor = 0x00;
        ugr::Color DustColor = 0x0A;
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define the range [0, 20] (inclusive)
        std::uniform_int_distribution<int> dis(0, 400);
        std::uniform_int_distribution<int> dis2(0, 400);
        while (true)
        {
            int rad = 220 - (r + 1);
            if (rad <= 0)
            {
                this->ClearScreen();
                CircleColor = 0x0F;
                DustColor = 0x08;
                for (int i = 0; i < 20; i++)
                {
                    this->RenderLine(ugr::Vector2i(480, 256), ugr::Vector2i(480 * 2, dis(gen)));
                    this->RenderLine(ugr::Vector2i(480, 256), ugr::Vector2i(-dis2(gen), dis2(gen)));
                }
            }
            
            for (int i = 0; i < r; i++)
            {
                xx++;
                yy += 0.25;
                this->RasterizeCircle(ugr::Vector2i(480, 256), r, 0x2588, DustColor, VertexShader);
                this->RasterizeCircle(ugr::Vector2i(480, 256), r + 1, 0x2588, CircleColor);
                this->RenderCircle(ugr::Vector2i(480, 256), 220 - r + 1, 0x2588, 0x02, StarShader);
            }
            xx = yy = 0;
            r++;
            this->Display();
        }
        return 0;
    }
    int r = 1;
};

int main(int argc, char** argv)
{
    Demo d;
    return d.run();
}

```