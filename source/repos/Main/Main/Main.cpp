#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
struct employee {
    int num;        // идентификационный номер сотрудника
    char name[10];  // имя сотрудника
    double hours;   // количество отработанных часов
};

int main() {
    char binaryFile[100], reportFile[100];
    int recordCount;
    double hourlyRate;

    std::cout << "Enter binary file name: ";
    std::cin >> binaryFile;
    std::cout << "Enter number of records: ";
    std::cin >> recordCount;

    // Запуск утилиты Creator
    char creatorCommand[150];
    sprintf(creatorCommand, "C://Users//vikto//source//repos//Main//x64//Debug//Creator.exe %s %d", binaryFile, recordCount);
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (!CreateProcessA(NULL, creatorCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to start Creator: " << GetLastError() << "\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Вывод содержимого файла
    std::cout << "Contents of the binary file:\n";
    std::ifstream ifs(binaryFile, std::ios::binary);
    employee emp;
    while (ifs.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << emp.num << " " << emp.name << " " << emp.hours << "\n";
    }
    ifs.close();

    std::cout << "Enter report file name: ";
    std::cin >> reportFile;
    std::cout << "Enter hourly rate: ";
    std::cin >> hourlyRate;

    // Запуск утилиты Reporter
    char reporterCommand[150];
    sprintf(reporterCommand, "C://Users//vikto//source//repos//Main//x64//Debug//Reporter.exe %s %s %.2f", binaryFile, reportFile, hourlyRate);

    if (!CreateProcessA(NULL, reporterCommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to start Reporter\n";
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Вывод отчета
    std::cout << "Report generated:\n";
    std::ifstream reportStream(reportFile);
    std::string line;
    while (std::getline(reportStream, line)) {
        std::cout << line << "\n";
    }
    reportStream.close();

    return 0;
}
