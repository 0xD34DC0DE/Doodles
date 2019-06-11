/*BITMAPFILEHEADER    bmfh;
BITMAPINFOHEADER    bmih;
RGBQUAD             aColors[];
BYTE                aBitmapBits[];*/
#include <cinttypes>
#include <vector>
#include <fstream>

#pragma pack(push, 1)
struct BMPFileHeader {
	uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42
	uint32_t file_size{ 0 };               // Size of the file (in bytes)
	uint16_t reserved1{ 0 };               // Reserved, always 0
	uint16_t reserved2{ 0 };               // Reserved, always 0
	uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader {
	uint32_t size{ 0 };                      // Size of this header (in bytes)
	int32_t width{ 0 };                      // width of bitmap in pixels
	int32_t height{ 0 };                     // width of bitmap in pixels
											 //       (if positive, bottom-up, with origin in lower left corner)
											 //       (if negative, top-down, with origin in upper left corner)
	uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
	uint16_t bit_count{ 0 };                 // No. of bits per pixel
	uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
	uint32_t size_image{ 0 };                // 0 - for uncompressed images
	int32_t x_pixels_per_meter{ 0 };
	int32_t y_pixels_per_meter{ 0 };
	uint32_t colors_used{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
	uint32_t colors_important{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPColorHeader {
	uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
	uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
	uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
	uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
	uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
	uint32_t unused[16]{ 0 };                // Unused data for sRGB color space
};
#pragma pack(pop)

struct BMP {
	BMPFileHeader file_header;
	BMPInfoHeader bmp_info_header;
	BMPColorHeader bmp_color_header;
	std::vector<uint8_t> data;

	BMP(int32_t width, int32_t height, bool has_alpha = true) {
		if (width <= 0 || height <= 0) {
			throw std::runtime_error("The image width and height must be positive numbers.");
		}

		bmp_info_header.width = width;
		bmp_info_header.height = height;
		if (has_alpha) {
			bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
			file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);

			bmp_info_header.bit_count = 32;
			bmp_info_header.compression = 3;
			row_stride = width * 4;
			data.resize(row_stride * height);
			file_header.file_size = file_header.offset_data + data.size();
		}
		else {
			bmp_info_header.size = sizeof(BMPInfoHeader);
			file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

			bmp_info_header.bit_count = 24;
			bmp_info_header.compression = 0;
			row_stride = width * 3;
			data.resize(row_stride * height);

			uint32_t new_stride = make_stride_aligned(4);
			file_header.file_size = file_header.offset_data + data.size() + bmp_info_header.height * (new_stride - row_stride);
		}
	}

	void write(const char *fname) {
		std::ofstream of{ fname, std::ios_base::binary };
		if (of) {
			if (bmp_info_header.bit_count == 32) {
				write_headers_and_data(of);
			}
			else if (bmp_info_header.bit_count == 24) {
				if (bmp_info_header.width % 4 == 0) {
					write_headers_and_data(of);
				}
				else {
					uint32_t new_stride = make_stride_aligned(4);
					std::vector<uint8_t> padding_row(new_stride - row_stride);

					write_headers(of);

					for (int y = 0; y < bmp_info_header.height; ++y) {
						of.write((const char*)(data.data() + row_stride * y), row_stride);
						of.write((const char*)padding_row.data(), padding_row.size());
					}
				}
			}
			else {
				throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
			}
		}
		else {
			throw std::runtime_error("Unable to open the output image file.");
		}
	}

private:
	uint32_t row_stride{ 0 };

	void write_headers(std::ofstream &of) {
		of.write((const char*)&file_header, sizeof(file_header));
		of.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
		if (bmp_info_header.bit_count == 32) {
			of.write((const char*)&bmp_color_header, sizeof(bmp_color_header));
		}
	}

	void write_headers_and_data(std::ofstream &of) {
		write_headers(of);
		of.write((const char*)data.data(), data.size());
	}

	// Add 1 to the row_stride until it is divisible with align_stride
	uint32_t make_stride_aligned(uint32_t align_stride) {
		uint32_t new_stride = row_stride;
		while (new_stride % align_stride != 0) {
			new_stride++;
		}
		return new_stride;
	}

	// ...
};
int main()
{
	BMP bmp2(800, 600, false);
	//uint32_t a = 0xff << (8+8);
	/*uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
	uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
	uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
	uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
	uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
	uint32_t unused[16]{ 0 };                // Unused data for sRGB color space*/

	char BMPColorHeaderString[] = "\x42\x4d\x36\xf9\x15\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00\x00\x00\x20\x03\x00\x00\x58\x02\x00\x00\x01\x00\x18\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";


	uint32_t b = *reinterpret_cast<uint32_t*>(BMPColorHeaderString);
	auto addr = &bmp2.file_header;
	auto addrStr = &BMPColorHeaderString;
	int a = memcmp(addrStr, addr, sizeof(BMPFileHeader));

	int channels = bmp2.bmp_info_header.bit_count / 8;
	for (int y = 20; y < 220; ++y) {
		for (int x = 50; x < 150; ++x) {
			bmp2.data[channels * (y * bmp2.bmp_info_header.width + x) + 0] = 0;   // B
			bmp2.data[channels * (y * bmp2.bmp_info_header.width + x) + 1] = 0;   // G
			bmp2.data[channels * (y * bmp2.bmp_info_header.width + x) + 2] = 255; // R
			if (channels == 4) {
				bmp2.data[channels * (y * bmp2.bmp_info_header.width + x) + 3] = 255; // A

			}

		}

	}

	bmp2.write("test.bmp");
	std::ofstream of{ "headerTest.bin", std::ios_base::binary };
	of.write((const char*)BMPColorHeaderString, sizeof(BMPColorHeaderString));
	unsigned long long llArray[] =  { 0x424D36F915000000u ,0x0000360000002800u, 0x0000200300005802u, 0x0000010018000000u, 0x0u, 0x0u, 0x0u };
	
	std::vector<uint8_t> bmpData(bmp2.data.size(), 0);
	for (int y = 20; y < 220; ++y)
		for (int x = 50; x < 150; ++x)
			bmpData[3 * (y * 800 + x)] = 255;   // B

	uint64_t llRArray[] = { 0x00000015f9364d42u ,0x0028000000360000u, 0x0258000003200000u, 0x0000001800010000u, 0x0u, 0x0u, 0x0u };
	std::ofstream of2{ "headerTest_ULL.bmp", std::ios_base::binary };
	of2.write((const char*)llRArray, sizeof(BMPFileHeader) + sizeof(BMPInfoHeader));
	of2.write((const char*)bmpData.data(), bmpData.size());
	
	return 0;
}