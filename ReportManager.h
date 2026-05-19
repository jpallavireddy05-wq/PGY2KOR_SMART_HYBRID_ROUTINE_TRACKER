#pragma once
#include <vector>
#include "Routine.h"   

class ReportManager {
public:
    std::vector<Routine> routines;

    void totalRoutines();
    void completedRoutines();
    void pendingRoutines();
    void completionPercentage();
    void categoryReport();
    void priorityReport();
    void menu();
};
