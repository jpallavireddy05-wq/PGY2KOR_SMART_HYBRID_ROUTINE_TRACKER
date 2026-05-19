#include <vector>
#include <string>

class ReminderService
{
public:
    std::vector<std::string> notifications;
    void startService();
    void stopService();
    void viewNotifications();
    void executeNotifications();
    void addCallback();
    void menu();
};
