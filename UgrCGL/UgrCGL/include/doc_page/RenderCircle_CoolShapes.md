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