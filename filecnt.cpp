#include <iostream>
#include <experimental/filesystem>
#include "version.cpp"
namespace fs = std::experimental::filesystem;

void navigate(std::string path, long vals[]) {
	for(const auto & entry : fs::directory_iterator(path)) {
		try {
			std::string file_path = entry.path();
			fs::file_status file = fs::status(file_path);
			if (fs::is_directory(file)) {
				vals[0]++;
				navigate(file_path, vals);
			} else if (!fs::is_symlink(file)) {
				vals[1]++;
				vals[2] += fs::file_size(file_path);
			}
		} catch (fs::filesystem_error) {
			continue;
		}
	}
}

int main(int argc, char **argv) {
	displayVersion();
	if (argc <= 1) {
		std::cout << "Please enter a path to a UNIX directory" << std::endl;
		return 1;
	} else {
		std::string path = argv[1];
		long vals[] = {0, 0, 0};
		navigate(path, vals);
		std::cout << "The total number of directories in directory " << path << " is: " << vals[0] << "." << std::endl;
		std::cout << "The total number of files in directory " << path << " is: " << vals[1] << "." << std::endl;
		std::cout << "The total number of bytes occupied by all files in directory " << path << " is: " << vals[2] << "." << std::endl;
		return 0;
	}
}
