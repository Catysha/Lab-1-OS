#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
struct employee {
    int num;        // идентификационный номер сотрудника
    char name[10];  // имя сотрудника
    double hours;   // количество отработанных часов
};


int maincreator(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: Creator <filename> <number_of_records>\n";
        return 1;
    }

    const char* filename = argv[1];
    int numberOfRecords = std::stoi(argv[2]);
    std::ofstream ofs(filename, std::ios::binary);

    if (!ofs) {
        std::cerr << "Error opening file: " << filename << "\n";
        return 1;
    }

    for (int i = 0; i < numberOfRecords; ++i) {
        employee emp;
        std::cout << "Enter employee ID, name and hours for record " << (i + 1) << ":\n";
        std::cin >> emp.num >> emp.name >> emp.hours;
        ofs.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }

    ofs.close();
    return 0;
}