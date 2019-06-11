#BMPColorHeader
#   uint32_t red_mask{ 0x00ff0000 };         // Bit mask for the red channel
#   uint32_t green_mask{ 0x0000ff00 };       // Bit mask for the green channel
#   uint32_t blue_mask{ 0x000000ff };        // Bit mask for the blue channel
#   uint32_t alpha_mask{ 0xff000000 };       // Bit mask for the alpha channel
#   uint32_t color_space_type{ 0x73524742 }; // Default "sRGB" (0x73524742)
#   uint32_t unused[16]{ 0 };                // Unused data for sRGB color space*/

red_mask            = b"\x00\xff\x00\x00"
green_mask          = b"\x00\x00\xff\x00"
blue_mask           = b"\x00\x00\x00\xff"
alpha_mask          = b"\xff\x00\x00\x00"
color_space_type    = b"sRGB"
unused              = bytes(16)

#BMPInfoHeader
#   uint32_t size{ 0 };                      // Size of this header (in bytes)
#   int32_t width{ 0 };                      // width of bitmap in pixels
#   int32_t height{ 0 };                     // width of bitmap in pixels
#                                             //       (if positive, bottom-up, with origin in lower left corner)
#                                             //       (if negative, top-down, with origin in upper left corner)
#   uint16_t planes{ 1 };                    // No. of planes for the target device, this is always 1
#   uint16_t bit_count{ 0 };                 // No. of bits per pixel
#   uint32_t compression{ 0 };               // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
#   uint32_t size_image{ 0 };                // 0 - for uncompressed images
#   int32_t x_pixels_per_meter{ 0 };
#   int32_t y_pixels_per_meter{ 0 };
#   uint32_t colors_used{ 0 };               // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
#   uint32_t colors_important{ 0 };          // No. of colors used for displaying the bitmap. If 0 all colors are required

size                = b"\x00\x00\x00\x00"
width               = b"\x00\x00\x00\x00"
height              = b"\x00\x00\x00\x00"
planes              = b"\x00\x01"[::-1]
bit_count           = b"\x00\x00"
compression         = b"\x00\x00\x00\x00"
size_image          = b"\x00\x00\x00\x00"
x_pixels_per_meter  = b"\x00\x00\x00\x00"
y_pixels_per_meter  = b"\x00\x00\x00\x00"
colors_used         = b"\x00\x00\x00\x00"
colors_important    = b"\x00\x00\x00\x00"

import struct
size        = struct.pack('<I', 40)
bit_count   = struct.pack('<H', 24)

#BMPFileHeader
#    uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42
#    uint32_t file_size{ 0 };               // Size of the file (in bytes)
#    uint16_t reserved1{ 0 };               // Reserved, always 0
#    uint16_t reserved2{ 0 };               // Reserved, always 0
#    uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)

file_type   = b"BM"
file_size   = b"\x00\x00\x00\x00"
reserved1   = b"\x00\x00"
reserved2   = b"\x00\x00"
offset_data = b"\x00\x00\x00\x00"

offset_data = struct.pack("<I", 54)
#print(offset_data.hex())
img_width   = 100
img_height  = 100
row_stride  = img_width * 3
data_size   = row_stride * img_height

print(data_size)

new_stride = row_stride
while new_stride % 4 != 0:
    new_stride+=1

file_size = struct.pack("<I", 54 + data_size + img_height * (new_stride - row_stride))

width  = struct.pack('<I', img_width)
height = struct.pack('<I', img_height)

BMPFileHeader = file_type + file_size + reserved1 + reserved2 + offset_data

BMPInfoHeader = size + width + height + planes + bit_count + compression + size_image + x_pixels_per_meter + y_pixels_per_meter + colors_used + colors_important 

BMPColorHeader = red_mask + green_mask + blue_mask + alpha_mask + color_space_type + unused


final_header = BMPFileHeader + BMPInfoHeader

def chunks(l, n):
    for i in range(0, len(l), n):
        yield l[i:i + n]

final_header = final_header.hex()
final_header_hex = [''.join(list(chunks(n, 2))[::-1]) for n in list(chunks(final_header, 16))] #oof
final_header_string = '\\x' + '\\x'.join(final_header_hex)
print(''.join(['0x' + h + ',' for h in final_header_hex]))
print()




'''
#to test validity

data = [0]*data_size

for y in range(20, 220):
    for x in range(50, 150):
        data[3 * (y * img_width + x) + 0] = 0
        data[3 * (y * img_width + x) + 1] = 0
        data[3 * (y * img_width + x) + 2] = 255

with open('bmp_test.bmp', 'wb') as f:
    f.write(BMPFileHeader)
    f.write(BMPInfoHeader)
    #f.write(BMPColorHeader)
    f.write(bytes(data))
'''