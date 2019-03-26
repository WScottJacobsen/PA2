#include <iostream>
#include <string>

int main(int argc, char **argv) {
	bool d = false, f = false, b = false;
	for(int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-d") {
			d = true;
		} else if (arg == "-f") {
			f = true;
		} else if (arg == "-b") {
			b = true;
		} else {
			std::cout << "Invalid option \'" << arg << "\' specified. Valid options are: -d, -f, and -b" << std::endl;
			return 1;
		}
	}

	bool found = false;
	std::string line;
	while(std::getline(std::cin, line)) {
		if ((d && line.find("directories") != std::string::npos)
		 || (f && line.find("files") != std::string::npos)
	     || (b && line.find("bytes") != std::string::npos)) {
			std::cout << line << std::endl;
			found = true;
		}
	}

	if (!found) {
		std::cout << "No matching lines were found." << std::endl;
		return 1;
	}
    return 0;
}
