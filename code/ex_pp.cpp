struct Sensor {
    bool isRead;
    bool isActivated;

    Sensor() {
        isRead = false;
        isActivated = false;
    }
};

void activate_sensor(Sensor* p_sensor) {
    p_sensor->isActivated = true;
    p_sensor->isRead = false;
}

void process_sensor(Sensor* p_sensor) {
    p_sensor->isActivated = false;
    p_sensor->isRead = true;
}

int main() {
    Sensor sensor;
    while (true) {
        if (sensor.isActivated && !sensor.isRead) {
            process_sensor(&sensor);
        }
    }
    return 0;
}