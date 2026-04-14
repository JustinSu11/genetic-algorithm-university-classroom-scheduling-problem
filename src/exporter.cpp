#include "organizer.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

// Decodes 7-bit days bitmask -> "Mon/Wed/Fri" style string
// Bit 6=Mon, Bit 5=Tue, Bit 4=Wed, Bit 3=Thu, Bit 2=Fri, Bit 1=Sat, Bit 0=Sun
static std::string decodeDays(unsigned int days) {
    const char* names[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    std::string result;
    for (int d = 0; d < 7; d++) {
        if (days & (1u << (6 - d))) {
            if (!result.empty()) result += "/";
            result += names[d];
        }
    }
    return result.empty() ? "None" : result;
}

// Finds the best chromosome in the final generation and writes a decoded
// class schedule to schedule_output.csv
void exportSchedule(const std::vector<std::vector<ChromosomeStruct>>& GenerationalRun,
                    const std::vector<Class>& classes,
                    const std::vector<Room>& rooms) {
    const std::vector<ChromosomeStruct>& lastGen = GenerationalRun.back();
    auto bestIt = std::max_element(lastGen.begin(), lastGen.end(),
        [](const ChromosomeStruct& a, const ChromosomeStruct& b) {
            return a.fitness < b.fitness;
        });
    const ChromosomeStruct& best = *bestIt;
    std::ostringstream oss;
    oss << std::setprecision(14) << best.fitness;
    std::string fitnessStr = oss.str();
    oss.str("");
    oss.clear();
    oss << std::setprecision(14) << best.H;
    std::string HStr = oss.str();

    std::ofstream file("schedule_output.csv");
    file << "ClassID,Enrollment,Days,StartSlot,Length,RoomID,Building,RoomCapacity,CapacityMet,Fitness, H\n";

    for (int i = 0; i < (int)best.chromosome.size(); i++) {
        int roomIdx = best.chromosome[i];
        const Class& c = classes[i];
        const Room& r = rooms[roomIdx];

        file << c.classId << ","
             << c.enrollment << ","
             << decodeDays(c.days) << ","
             << c.startSlot << ","
             << c.length << ","
             << r.roomId << ","
             << "\"" << r.building << "\"" << ","
             << r.capacity << ","
             << (r.capacity >= c.enrollment ? "Yes" : "No") << ","
             << (i == 0 ? fitnessStr : "") << ","
             << (i == 0 ? HStr : "") << "\n";
    }
    file.close();
    std::cout << "Exported schedule_output.csv (" << best.chromosome.size() << " classes, fitness=" << best.fitness << ")\n";
}

// Writes best and average fitness per generation to convergence.csv
void exportConvergence(const std::vector<std::vector<ChromosomeStruct>>& GenerationalRun) {
    std::ofstream file("convergence.csv");
    file << "Generation,BestFitness,AvgFitness\n";

    for (int g = 0; g < (int)GenerationalRun.size(); g++) {
        double best = 0.0, sum = 0.0;
        for (const auto& c : GenerationalRun[g]) {
            sum += c.fitness;
            if (c.fitness > best) best = c.fitness;
        }
        double avg = sum / GenerationalRun[g].size();
        file << g + 1 << "," << best << "," << avg << "\n";
    }
    file.close();
    std::cout << "Exported convergence.csv (" << GenerationalRun.size() << " generations)\n";
}
