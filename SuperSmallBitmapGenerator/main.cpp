#include <vector>
#include <fstream>

int main() {

	std::vector<uint8_t> a(30000, 0);

	int iterPerFrame = 11000;
	const int resolution = 100;
	int x = resolution / 2;
	int y = resolution / 2;
	int r = 0;
	unsigned int c[resolution][resolution]{ 0 };

	for (int i = 0; i < iterPerFrame; i++)
	{
		r = (r - 1 + (c[x][y] * 2)) % 4;
		c[x][y] = !c[x][y];
		x += (r % 2) * (2 - r);
		y += ((r + 1) % 2) * (-1 + ((r + 1) % 2) * r);
	}

	for (int i = 0; i < resolution*resolution; i++)
	{
			int x = (i % 100);
			int v = c[x][i/100]*255;
			reinterpret_cast<uint32_t&>(a[(3 * ((i/100) * 100 + x))]) = (v | v << 8 | v << 16 | v << 24);
	}

	uint64_t llRArray[] = { 0x0000000075664d42,0x0028000000360000,0x0064000000640000,0x0000001800010000,0x0,0x0,0x0 };
	std::ofstream of2{ "headerTest_ULL.bmp", std::ios_base::binary };
	of2.write((const char*)llRArray, 54);
	of2.write((const char*)a.data(), a.size());
	return 0;
}