#include <vector>
#include "Routine.h"

class RoutineManager {
public:
    std::vector<Routine> routines;

    void addRoutine();
    void viewRoutines();
    void viewPending();
    void viewCompleted();
    void markCompleted();
    void updatePriority();
    void categorizeRoutine();
    void deleteRoutine();
    void searchRoutine();
    void menu();
};
