#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define OFFSET 10
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

void create_the_offsets(std::vector<uint8_t> *orig_data, std::vector<uint8_t> *modifiable_data, int offset) {
	*modifiable_data = *orig_data;
	modifiable_data->erase( modifiable_data->begin(), modifiable_data->begin() + (offset * ORIG_WIDTH) );
	modifiable_data->erase( modifiable_data->begin() + (NEW_HEIGHT * ORIG_WIDTH), modifiable_data->end());
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
	std::vector<uint8_t> orig_data;
	std::vector<uint8_t> modifiable_data;
	std::string output_file_name;
	std::stringstream ss;

	read_image_file_to_vector(input_image_file_name, &orig_data);
	
	for (int i = 0; i < 20; i++) {
		create_the_offsets(&orig_data, &modifiable_data, OFFSET * i);
		std::cout << "finished creating image " << i << std::endl;
		std::cout << "image_" << i << " has size " << modifiable_data.size() << std::endl;
		ss << "output_images/image_" << i << ".dat";
		ss >> output_file_name;
		ss.clear();
		std::cout << output_file_name << std::endl;
		std::cout << "about to get into write_data_to_vector" << std::endl;
		write_data_vector_to_file(output_file_name, &modifiable_data);
		std::cout << "about to get out of write_data_to_vector" << std::endl;
	}
}

