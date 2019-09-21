#include <iostream>
#include <fstream>
#include <string>
#include <vector>
	
#define OFFSET 100
#define ORIG_WIDTH 640
#define ORIG_HEIGHT 951
#define NEW_HEIGHT 640

void read_image_file_to_vector(std::string file_name, std::vector<uint8_t> *data) {
	std::fstream image_file_stream (file_name, std::ios::in | std::ios::binary);
	char bin_val;
	
	while ( image_file_stream.read( &bin_val, 1) ) {
		data->push_back(bin_val);
	}
	image_file_stream.close();
}

void create_the_offsets(std::vector<uint8_t> *data_1, std::vector<uint8_t> *data_2) {
	data_1->erase( data_1->begin() + (NEW_HEIGHT * ORIG_WIDTH), data_1->end() );
	data_2->erase( data_2->begin(), data_2->begin() + (OFFSET * ORIG_WIDTH) );
	data_2->erase( data_2->begin() + (NEW_HEIGHT * ORIG_WIDTH), data_2->end());
}
 
void write_data_vector_to_file( std::string file_name, std::vector<uint8_t> *data ) {	
	std::fstream image_file_stream (file_name, std::ios::out | std::ios::binary);
	char* bin_val = new char [ORIG_WIDTH * ORIG_HEIGHT];
	
	std::copy( data->begin(), data->end(), bin_val );
	image_file_stream.write( bin_val, data->size() );
	image_file_stream.close();
	
	delete [] bin_val;
}

int main(int argc, const char** argv) {
	std::string input_image_file_name = argv[1];
	std::vector<uint8_t> data_1;
	std::vector<uint8_t> data_2;
	read_image_file_to_vector(input_image_file_name, &data_1);
	data_2 = data_1;
	create_the_offsets(&data_1, &data_2);
	write_data_vector_to_file("output_images/image_1.dat", &data_1);
	write_data_vector_to_file("output_images/image_2.dat", &data_2);
}

