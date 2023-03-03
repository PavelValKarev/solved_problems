#pragma once

#include <fstream>
#include <iostream>
#include <string>

inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name) {
	using namespace std;
	//Action if file does not exist: Create new
	//Action if file already exists: Write to end
	ifstream in_file_rle(src_name, ios::in | ios::binary);
	//если файл не прочитан
	if (!in_file_rle) {
		return false;
	}
	//записываем в выходной поток
	//Action if file does not exist: Create new
	//Action if file already exists: Write to end
	ofstream out_file_decode(dst_name, ios::out | ios::binary);
	do {
		//считали кол-во байт во входном потоке
		int byte = in_file_rle.get();
		bool bit_0 = byte & (1 << 0);
		if (bit_0 == 0) {
			int size = byte >> 1;
			++size;
			char* buff = new char[size];
			in_file_rle.read(buff, size);
			out_file_decode.write(buff, in_file_rle.gcount());
		}
		if (bit_0 == 1) {
			int size = byte >> 1;
			++size;
			unsigned char byte_char = in_file_rle.get();
			char* repeat_buff = new char[size];
			for (size_t i = 0; i < size; ++i) {
				repeat_buff[i] = byte_char;
			}
			out_file_decode.write(repeat_buff, size);
		}

	} while (in_file_rle);
	in_file_rle.close();
	out_file_decode.close();
	return true;
}
