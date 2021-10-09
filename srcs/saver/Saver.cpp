#include "Saver.hpp"

Saver::Saver(){}

Saver::~Saver(){}

void Saver::saveToPng(int width, int height)
{
    
    std::ofstream outfile("test12.png", std::ios::binary | std::ios::out);
    writePngHeader(&outfile);
    writePngChunkIHDR(&outfile, width, height);

    outfile.close();
}

void Saver::writePngHeader(std::ofstream *outfile)
{
    std::string header = "89504e470d0a1a0a";
    outputHex(outfile, header);
}

void Saver::writePngChunkIHDR(std::ofstream *outfile, int width, int height)
{
    std::string chunk_size = itohex(13);
    std::string chunk_type = "IHDR";

    outputHex(outfile, chunk_size); // length
    output(outfile, chunk_type); // type
    outputHex(outfile, itohex(width));
    outputHex(outfile, itohex(height));
    outputHex(outfile, itohex(16)); // bit depth (1 byte, values 1, 2, 4, 8, or 16)
    outputHex(outfile, itohex(3)); // color type (1 byte, values 0, 2, 3, 4, or 6)
    outputHex(outfile, itohex(0)); // compression method (1 byte, value 0)
    outputHex(outfile, itohex(0)); // filter method (1 byte, value 0)
    outputHex(outfile, itohex(0)); // interlace method (1 byte, values 0 "no interlace" or 1 "Adam7 interlace")

    outputHex(outfile, itohex(0)); // CRC
}