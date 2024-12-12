#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
struct employee {
    int num;        // идентификационный номер сотрудника
    char name[10];  // имя сотрудника
    double hours;   // количество отработанных часов
};


int mainreporter(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: Reporter <inputfile> <reportfile> <hourly_rate>\n";
        return 1;
    }

    const char* inputFile = argv[1];
    const char* reportFile = argv[2];
    double hourlyRate = std::stod(argv[3]);

    std::ifstream ifs(inputFile, std::ios::binary);
    std::ofstream ofs(reportFile);

    if (!ifs || !ofs) {
        std::cerr << "Error opening files.\n";
        return 1;
    }

    std::vector<employee> employees;
    employee emp;

    while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        employees.push_back(emp);
    }

    ofs << "Отчет по файлу \"" << inputFile << "\"\n";
    ofs << "Номер сотрудника\tИмя сотрудника\tЧасы\tЗарплата\n";

    for (const auto& e : employees) {
        double salary = e.hours * hourlyRate;
        ofs << e.num << "\t" << e.name << "\t" << e.hours << "\t" << std::fixed << std::setprecision(2) << salary << "\n";
    }

    ifs.close();
    ofs.close();
    return 0;
}