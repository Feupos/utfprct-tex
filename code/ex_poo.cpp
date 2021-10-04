class Sensor {
public:
    bool isRead{false};
    bool isActivated{false};

    void Activate() {
        isActivated = true;
        isRead = false;
    }
    void Process() {
        isActivated = false;
        isRead = true;
    }
};

int main() {
    Sensor sensor;
    while (true) {
        if (sensor.isActivated && !sensor.isRead) {
            sensor.Process();
        }
    }
    return 0;
}