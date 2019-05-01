#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iosfwd>

extern "C"
{
	void huffman_compress(std::istream& in, std::ostream& out);
	void huffman_decompress(std::istream& in, std::ostream& out);
};


#endif //HUFFMAN_H