#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <vector>

#define WIDTH 640
#define HEIGHT 951
#define BETA 1
#define SIGMA 10 
#define VARIANCE_THRESHOLD 20

void icm (std::vector<uint8_t> *data) {
	for (int i = 2; i < HEIGHT - 2; i++) {
		for (int j = 2; j < WIDTH - 2; j++) {
			int min_energy_value = INT_MAX;
			int optimum_pixel_value;
			for (int test_value = 0; test_value < 255; test_value++) {
				int data_term = pow( data->at( i * WIDTH + j ) - test_value, 2 );
				int smoothness_term = pow( data->at( (i - 1) * WIDTH + j ) - test_value, 2 ) + 
						      pow( data->at( (i + 1) * WIDTH + j ) - test_value, 2 ) + 
						      pow( data->at( i * WIDTH + j - 1 ) - test_value, 2 ) + 
						      pow( data->at( i * WIDTH + j + 1 ) - test_value, 2 );
				int energy = data_term * SIGMA + smoothness_term * BETA;
				if (energy < min_energy_value) {
					min_energy_value = energy;
					optimum_pixel_value = test_value;
				}
			}
			data->at(i * WIDTH + j) = optimum_pixel_value;
		}
	}
}

void add_Gaussian_noise (std::vector<uint8_t> *data) {
	std::random_device rd;   //ensures new set of numbers every time
	std::default_random_engine generator (rd());
	std::uniform_int_distribution<int> distribution(1,10);
	char bin_val;

	for (uint8_t &i: *data) {
		if (distribution(generator) > 9) {
			bin_val = 0;
		} else {
			bin_val = i;
		}
		i = bin_val;
	}
}			

void generic_smooth (std::vector<uint8_t> *data) {
	for (int i = 2; i < HEIGHT - 2; i++) {
		for (int j = 2; j < WIDTH - 2; j++) {
			data->at( i * WIDTH + j ) = ( data->at( (i - 1) * WIDTH + j) +
						      data->at( (i + 1) * WIDTH + j) +
						      data->at( i * WIDTH + j - 1 ) +
						      data->at( i * WIDTH + j + 1 ) ) / 4;
		}
	}
}

void get_specific_solution_assuming_only_black_pepper_noise (std::vector<uint8_t> *data) {
	for (int i = 2; i < HEIGHT - 2; i++) {
		for (int j = 2; j < WIDTH - 2; j++) {
			if ( data->at( i * WIDTH + j) == 0 ) {
				data->at( i * WIDTH + j ) = ( data->at( (i - 1) * WIDTH + j) +
						      	      data->at( (i + 1) * WIDTH + j) +
						      	      data->at( i * WIDTH + j - 1 ) +
							      data->at( i * WIDTH + j + 1 ) ) / 4;
			}
		}
	}

	for (int i = 2; i < HEIGHT - 2; i++) {
		for (int j = 2; j < WIDTH - 2; j++) {
			uint8_t avg = ( data->at( (i - 1) * WIDTH + j) +
					data->at( (i + 1) * WIDTH + j) +
					data->at( i * WIDTH + j - 1 ) +
					data->at( i * WIDTH + j + 1 ) ) / 4;
			if ( abs(data->at( i * WIDTH + j ) - avg ) > VARIANCE_THRESHOLD) {
				data->at( i * WIDTH + j ) = avg;
			}
		}
	}
}

void write_data_bytes_to_file (std::vector<uint8_t> data, std::fstream *image_file_stream ) {
	char binary_value;

	for (uint8_t i: data) {
		binary_value = i;
		image_file_stream->write(&binary_value, 1);
	}
}

int main(int argc, const char** argv) {
	std::fstream image_file_stream ("/Users/matthewalanlarkins/Desktop/ICM/field_mouse_grey_backup.dat", std::ios::in | std::ios::out | std::ios::binary);
	std::vector<uint8_t> data;
	char bin_val;

	while ( image_file_stream.read( &bin_val, 1 ) ) {
		data.push_back(bin_val);
	}	
	
	image_file_stream.close();
	
	add_Gaussian_noise (&data);
	
	image_file_stream.open("field_mouse_grey_noisy.dat", std::ios::out | std::ios::binary);
	write_data_bytes_to_file (data, &image_file_stream);
	image_file_stream.close();

	get_specific_solution_assuming_only_black_pepper_noise (&data);
	
	image_file_stream.open("field_mouse_grey_specific_solved.dat", std::ios::out | std::ios::binary);
	write_data_bytes_to_file (data, &image_file_stream);
	image_file_stream.close();

// 	generic_smooth (&data);
// 	
// 	image_file_stream.open("field_mouse_grey_smoothed.dat", std::ios::out | std::ios::binary);
// 	write_data_bytes_to_file (data, &image_file_stream);
// 	image_file_stream.close();
	
// 	std::string file_name_base = "field_mouse_grey_denoised_";
// 	std::string file_extension = ".dat";
// 	std::string file_name;
// 	std::stringstream ss;
// 	for (int i = 0; i < 10; i++) {
// 		std::cout << "Beginning iteration " << i + 1 << " of ICM..." << std::endl;
// 		icm (&data);
// 		ss << file_name_base << i + 1 << file_extension;
// 		ss >> file_name;
// 		ss.clear();
// 		std::cout << file_name << std::endl;		
// 		image_file_stream.open (file_name, std::ios::out | std::ios::binary);
// 	
// 		for (uint8_t i: data) {
// 			bin_val = i;
// 			image_file_stream.write(&bin_val, 1);
// 		}
// 		image_file_stream.close();
// 	}

	image_file_stream.close();
}
